--[[
	Description: battle dialog controller
	Author: M.Wan
	Date: 1/15/2015
]]

class("BattleDialogController", psViewController)

require "src/scene/battle/BattleDialogConstants"

BattleDialogController.root = nil
BattleDialogController.dialogWindow = nil
BattleDialogController.dialogLabel = nil

BattleDialogController.isDialogInProcess = nil
BattleDialogController.isEnabled = nil
BattleDialogController.currentDialogKey = nil
BattleDialogController.currentDialogParams = nil
BattleDialogController.currentDialog = nil		-- 当前会话内容

-- const values
BattleDialogController.DIALOG_TEXT_FONT_SIZE = 18
BattleDialogController.DIALOG_TEXT_DIMENSION = CCSizeMake(700, 60)
BattleDialogController.DIALOG_TEXT_POSITION = ccp(60, 80)
BattleDialogController.DIALOG_TEXT_COLOR = ccc3(0, 0, 0)
BattleDialogController.DIALOG_TEXT_DURATION = 0.05
BattleDialogController.DIALOG_INDICE_POSITION = ccp(750, 10)

function BattleDialogController:load()
	log("BattleDialogController:load")
	self:addObservers()
	self:renderView()
end

function BattleDialogController:unload()
	log("BattleDialogController:unload")
	self:removeObservers()
	self.root:removeFromParent(true)
end

function BattleDialogController:addObservers()
	Notifier:addObserver(NotifyEvents.Battle.UpdateDialog, self, self.onUpdateDialog)
	Notifier:addObserver(NotifyEvents.Battle.ShowDialog, self, self.onShowDialog)
end

function BattleDialogController:removeObservers()
	Notifier:removeObserver(NotifyEvents.Battle.UpdateDialog, self)
	Notifier:removeObserver(NotifyEvents.Battle.ShowDialog, self)
end

function BattleDialogController:renderView()
	local winSize = cc.Director:getInstance():getWinSize()

	self.root = cc.Layer:create()
	self.root:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
	self:getScene():addChild(self.root)

	-- dialog window initialization
	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	local windowSize = CCSizeMake(winSize.width * 0.95, winSize.height * 0.2)
	local windowPos = ccp(winSize.width * 0.5, winSize.height * 0.1)
	dialogWindow:setPreferredSize(windowSize)
	dialogWindow:setPosition(windowPos)

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
	local dialogIndice = cc.Sprite:createWithSpriteFrameName("images/battle/dialog_indice.png")
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
	self.isEnabled = false
end

function BattleDialogController:onNodeEvent(event)
	if event == "enter" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self.root)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			kbdListener:setEventsSwallowed(false)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		else
			local touchListener = cc.EventListenerTouchOneByOne:create()
			touchListener:setSwallowTouches(true)
			touchListener:registerScriptHandler(MakeScriptHandler(self, self.onTouch), cc.Handler.EVENT_TOUCH_BEGAN)
			self.root:getEventDispatcher():addEventListenerWithSceneGraphPriority(touchListener, self.root)
			self.touchListener = touchListener
		end
	elseif event == "exit" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
			self.kbdListener = nil
		elseif self.touchListener then
			self.root:getEventDispatcher():removeEventListener(self.touchListener)
		end
	end
end

function BattleDialogController:onKeyboardPressed(keyCode)
	if not self.isEnabled then
		return
	end
	if keyCode == GameSettings.confirmKey or keyCode == GameSettings.cancelKey then
		self:handleDialogDisplay(self.currentDialog)
	end
end

function BattleDialogController:handleDialogDisplay(dialog)
	if self.isDialogInProcess then
		self.isDialogInProcess = false
		self.root:stopAllActions()
		self.dialogLabel:setString(dialog)
		self.dialogIndice:setVisible(true)
	else
		GameVolumeHelper:playBtnClickSound()

		self.dialogIndice:setVisible(false)
		self.dialogLabel:setString("")
		self.isEnabled = false
		Notifier:notify(NotifyEvents.Battle.DialogEnded)
	end
end

function BattleDialogController:showTextOneByOne(substrings, index)
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
	CallFunctionAsync(self, self.showTextOneByOne, self.DIALOG_TEXT_DURATION, substrings, index + 1)
end

function BattleDialogController:onUpdateDialog(dialogKey, ...)
	local showDialog = string.format(BattleDialogConstants[dialogKey], ...)
	log("BattleDialogConstants:onUpdateDialog", showDialog)
	self.currentDialogKey = dialogKey
	self.currentDialogParams = unpack{...}
	self.currentDialog = showDialog
	local substrings = GenerateAllUTF8Substrings(showDialog)
	self.isDialogInProcess = true
	self.isEnabled = true
	self:showTextOneByOne(substrings, 1)
end

function BattleDialogController:onShowDialog(dialogKey, ...)
	local showDialog = string.format(BattleDialogConstants[dialogKey], ...)
	log("BattleDialogController:onShowDialog", showDialog)
	self.dialogLabel:setString(showDialog)
end