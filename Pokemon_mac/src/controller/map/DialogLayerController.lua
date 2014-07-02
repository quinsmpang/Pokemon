--[[
	Description: dialogue layer controller
	Author: M.Wan
	Date: 06/07/2014
]]

class("DialogLayerController", psViewController)

require "src/controller/map/ActionController"

DialogLayerController.resources = {
}

-- ui
DialogLayerController.root = nil		-- root layer(pf.GameLayer)
DialogLayerController.dialogWindow = nil	-- dialog window
DialogLayerController.dialogLabel = nil		-- dialog text
DialogLayerController.dialogIndice = nil	-- indice for continuing talking

-- logic 
DialogLayerController.touchEventListener = nil
DialogLayerController.currentDialogId = nil		-- current dialog id
DialogLayerController.currentDialogModel = nil
DialogLayerController.isDialogInProcess = nil	-- whether the dialog is in progress

-- const values
DialogLayerController.DIALOG_WINDOW_SIZE = CCSizeMake(780, 100)
DialogLayerController.DIALOG_WINDOW_POSITION = ccp(400, 50)
DialogLayerController.DIALOG_TEXT_FONT_SIZE = 18
DialogLayerController.DIALOG_TEXT_DIMENSION = CCSizeMake(700, 60)
DialogLayerController.DIALOG_TEXT_POSITION = ccp(60, 80)
DialogLayerController.DIALOG_TEXT_COLOR = ccc3(0, 0, 0)
DialogLayerController.DIALOG_TEXT_DURATION = 0.05
DialogLayerController.DIALOG_INDICE_POSITION = ccp(750, 10)

function DialogLayerController:load()
	log("DialogLayerController:load")
	self:loadResources()
	self:addObservers()
	MapStateController:setCurrentState(Enumerations.MAP_STATE.DIALOG)

	self:renderView()
end

function DialogLayerController:unload()
	log("DialogLayerController:unload")
	self:cleanResources()
	self:removeObservers()
	self.root:getEventDispatcher():removeEventListener(self.touchEventListener)
	self.root:removeFromParent()
end

function DialogLayerController:loadResources()
	log("DialogLayerController:loadResources")
	LoadSpriteFrames(self.resources)
end

function DialogLayerController:cleanResources()
	log("DialogLayerController:cleanResources")
	RemoveSpriteFrames(self.resources)
end

function DialogLayerController:addObservers()
	log("DialogLayerController:addObservers")
	Notifier:addObserver(NotifyEvents.MapView.ActionEnded, self, self.onActionEnded)
	Notifier:addObserver(NotifyEvents.MapView.DialogKeyboardResponse, self, self.onKeyboardEvent)
end

function DialogLayerController:removeObservers()
	log("DialogLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionEnded, self)
	Notifier:removeObserver(NotifyEvents.MapView.DialogKeyboardResponse, self)
end

function DialogLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	self.root = cc.Layer:create()
	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(MakeScriptHandler(self, self.onLayerTouch), cc.Handler.EVENT_TOUCH_BEGAN)
	self.root:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self.root)
	self.touchEventListener = listener

	-- dialog window initialization
	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	dialogWindow:setPreferredSize(self.DIALOG_WINDOW_SIZE)
	dialogWindow:setPosition(self.DIALOG_WINDOW_POSITION)

	self.dialogWindow = dialogWindow
	self.root:addChild(dialogWindow)

	-- dialog label initialization
	local dialogLabel = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, self.DIALOG_TEXT_FONT_SIZE, self.DIALOG_TEXT_DIMENSION)
	dialogLabel:setAnchorPoint(ccp(0, 1))
	dialogLabel:setPosition(self.DIALOG_TEXT_POSITION)
	dialogLabel:setColor(self.DIALOG_TEXT_COLOR)

	self.dialogLabel = dialogLabel
	self.root:addChild(dialogLabel)

	-- dialog indice
	local dialogIndice = cc.Sprite:createWithSpriteFrameName("images/map/dialog_indice.png")
	dialogIndice:setAnchorPoint(ccp(0, 0))
	dialogIndice:setPosition(self.DIALOG_INDICE_POSITION)
	dialogIndice:setVisible(false)
	-- run blink action
	local indiceAction = cc.Sequence:create(
			cc.FadeOut:create(0.2),
			cc.FadeIn:create(0.2)
		)
	dialogIndice:runAction(cc.RepeatForever:create(indiceAction))

	self.dialogIndice = dialogIndice
	self.root:addChild(dialogIndice)

	self.isDialogInProcess = false
	self.currentDialogId = self.currentDialogId or 0

	--coreLayer:pushLayer(self.root)
	self:getScene():addChild(self.root)

	self:generateNextDialog()
	--CallFunctionAsync(self, self.generateNextDialog, 2.5)
end

function DialogLayerController:onLayerTouch(touch, event)
	if ActionController.isUnderAction then
		return
	end
	log("DialogLayerController:onLayerTouch")
	self:handleDialogDisplay()
end

function DialogLayerController:onKeyboardEvent(keyCode, eventType)
	if ActionController.isUnderAction then
		return
	end
	log("DialogLayerController:onKeyboardEvent, eventType: [" .. eventType .. "]")
	if eventType == Enumerations.KEYBOARD_STATE.PRESSED then
		if keyCode == GameSettings.confirmKey or keyCode == GameSettings.cancelKey then
			self:handleDialogDisplay()
		end
	end
end

function DialogLayerController:handleDialogDisplay()
	if self.isDialogInProcess then
		self.isDialogInProcess = false
		self.root:stopAllActions()
		self.dialogLabel:setString(self.currentDialogModel.speaker .. ": " .. self.currentDialogModel:getCorrectDialog())
		self.dialogIndice:setVisible(true)
	else
		GameVolumeHelper:playBtnClickSound()
		self:generateNextDialog()
	end
end

function DialogLayerController:generateNextDialog()
	log("DialogLayerController:generateNextDialog")
	log("current dialog id: " .. self.currentDialogId)
	-- 执行action处理 如果有的话
	if self.currentDialogModel and not ActionController.isUnderAction then
		if self.currentDialogModel.actionId ~= DBNULL then
			-- 如果action是-1，则进入自由活动
			if tonumber(self.currentDialogModel.actionId) == -1 then
				DataCenter.currentPlayerData:enterFreedom()
				DataCenter.currentPlayerData.lastDialogId = self.currentDialogId
				MapStateController:setCurrentState(Enumerations.MAP_STATE.FREEDOM)
				self:getScene():unloadViewController(self)
				return
			else
				local actionModel = ActionInfo:create(self.currentDialogModel.actionId)
				ActionController.isUnderAction = true
				self.root:setVisible(false)
				ActionController:processAction(actionModel)
				return
			end
		end
	else
		ActionController.isUnderAction = false
		self.root:setVisible(true)
	end

	self.dialogIndice:setVisible(false)
	self.currentDialogId = self.currentDialogId + 1
	local currentDialog = Dialog:create(self.currentDialogId)
	local substrings = GenerateAllUTF8Substrings(currentDialog:getCorrectDialog())
	self.currentDialogModel = currentDialog
	DataCenter.currentPlayerData.step = currentDialog.relatedStep

	self.isDialogInProcess = true
	self:showTextOneByOne(substrings, 1)
end

function DialogLayerController:showTextOneByOne(substrings, index)
	if not self.isDialogInProcess then
		return
	end
	-- jump out of recursive
	if index > #substrings then
		self.dialogIndice:setVisible(true)
		self.isDialogInProcess = false
		return
	end
	self.dialogLabel:setString(self.currentDialogModel.speaker .. ": " .. substrings[index])
	--[[ there is an issue, cc.CallFunc passes an default parameter which is the caller to the callback function
	so use callfunc here would cause error!]]
	-- local action = cc.Sequence:create(
	-- 		cc.DelayTime:create(self.DIALOG_TEXT_DURATION),
	-- 		cc.CallFunc:create(MakeScriptHandler(self, self.showTextOneByOne, substrings, index + 1))
	-- 	)
	-- self.root:runAction(action)
	CallFunctionAsync(self, self.showTextOneByOne, self.DIALOG_TEXT_DURATION, substrings, index + 1)
end

function DialogLayerController:onActionEnded()
	self:generateNextDialog()
end