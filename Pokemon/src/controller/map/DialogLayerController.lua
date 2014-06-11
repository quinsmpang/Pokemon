--[[
	Description: dialogue layer controller
	Author: M.Wan
	Date: 06/07/2014
]]

class("DialogLayerController", psViewController)

DialogLayerController.resources = {
	"images/common.plist",
	"images/common.pvr.ccz",
	"images/dialog.plist",
	"images/dialog.pvr.ccz"
}

DialogLayerController.root = nil		-- root layer(pf.GameLayer)
DialogLayerController.dialogWindow = nil	-- dialog window
DialogLayerController.dialogLabel = nil		-- dialog text
DialogLayerController.dialogIndice = nil	-- indice for continuing talking

-- logic 
DialogLayerController.currentDialogId = nil		-- current dialog id
DialogLayerController.currentDialogModel = nil
DialogLayerController.isDialogInProcess = nil	-- whether the dialog is in action

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

	self:renderView()
end

function DialogLayerController:unload()
	log("DialogLayerController:unload")
	self:cleanResources()
end

function DialogLayerController:loadResources()
	log("DialogLayerController:loadResources")
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():addSpriteFrames(self.resources[i], self.resources[i + 1])
	end
end

function DialogLayerController:cleanResources()
	log("DialogLayerController:cleanResources")
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(self.resources[i])
	end
end

function DialogLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	self.root = psGameLayer:create()
	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(MakeScriptHandler(self, self.onLayerTouch), cc.Handler.EVENT_TOUCH_BEGAN)
	self.root:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self.root)
	-- register keyboard event
	if targetPlatform == cc.PLATFORM_OS_WIN32 then
		local kbdListener = cc.EventListenerKeyboard:create()
		kbdListener:registerScriptHandler(MakeScriptHandler(self, self.onKeyboardPressed), cc.Handler.EVENT_KEYBOARD_PRESSED)

		self.root:getEventDispatcher():addEventListenerWithSceneGraphPriority(kbdListener, self.root)
	end

	-- dialog window initialization
	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_orange.png", capInsets)
	dialogWindow:setPreferredSize(self.DIALOG_WINDOW_SIZE)
	dialogWindow:setPosition(self.DIALOG_WINDOW_POSITION)

	self.dialogWindow = dialogWindow
	self.root:addChild(dialogWindow)

	-- dialog label initialization
	local dialogLabel = cc.Label:createWithTTF("", GameConst.DEFAULT_FONT_PATH, self.DIALOG_TEXT_FONT_SIZE, self.DIALOG_TEXT_DIMENSION)
	dialogLabel:setAnchorPoint(ccp(0, 1))
	dialogLabel:setPosition(self.DIALOG_TEXT_POSITION)
	dialogLabel:setColor(self.DIALOG_TEXT_COLOR)

	self.dialogLabel = dialogLabel
	self.root:addChild(dialogLabel)

	-- dialog indice
	local dialogIndice = cc.Sprite:createWithSpriteFrameName("images/dialog/dialog_indice.png")
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
	self.currentDialogId = 0

	coreLayer:pushLayer(self.root)

	self:generateNextDialog()
	--CallFunctionAsync(self, self.generateNextDialog, 2.5)
end

function DialogLayerController:onLayerTouch(touch, event)
	log("DialogLayerController:onLayerTouch")
	if self.isDialogInProcess then
		self.isDialogInProcess = false
		self.dialogLabel:setString(self.currentDialogModel.dialog)
		self.dialogIndice:setVisible(true)
	else
		GameVolumeHelper:playBtnClickSound()
		self:generateNextDialog()
	end
end

function DialogLayerController:onKeyboardPressed(keyCode, event)
	log("DialogLayerController:onKeyboardPressed")
	if keyCode == GameSettings.confirmKey or keyCode == GameSettings.cancelKey then
		if self.isDialogInProcess then
			self.isDialogInProcess = false
			self.root:stopAllActions()
			self.dialogLabel:setString(self.currentDialogModel.dialog)
			self.dialogIndice:setVisible(true)
		else
			GameVolumeHelper:playBtnClickSound()
			self:generateNextDialog()
		end
	end
end

function DialogLayerController:generateNextDialog()
	log("DialogLayerController:generateNextDialog")
	log("current dialog id: " .. self.currentDialogId)
	self.dialogIndice:setVisible(false)
	self.currentDialogId = self.currentDialogId + 1
	local currentDialog = GameDBHelper:queryDialogById(self.currentDialogId)
	local substrings = GenerateAllUTF8Substrings(currentDialog.dialog)
	self.currentDialogModel = currentDialog

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
	self.dialogLabel:setString(substrings[index])
	--[[ there is an issue, cc.CallFunc passes an default parameter which is the caller to the callback function
	so use callfunc here would cause error!]]
	-- local action = cc.Sequence:create(
	-- 		cc.DelayTime:create(self.DIALOG_TEXT_DURATION),
	-- 		cc.CallFunc:create(MakeScriptHandler(self, self.showTextOneByOne, substrings, index + 1))
	-- 	)
	-- self.root:runAction(action)
	CallFunctionAsync(self, self.showTextOneByOne, self.DIALOG_TEXT_DURATION, substrings, index + 1)
end