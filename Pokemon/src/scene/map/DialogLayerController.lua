--[[
	Description: dialogue layer controller
	Author: M.Wan
	Date: 06/07/2014
]]

class("DialogLayerController", psViewController)

DialogLayerController.resources = {
}

-- ui
DialogLayerController.root = nil		-- root layer(pf.GameLayer)
DialogLayerController.dialogWindow = nil	-- dialog window
DialogLayerController.dialogLabel = nil		-- dialog text
DialogLayerController.dialogIndice = nil	-- indice for continuing talking

-- logic 
DialogLayerController.currentDialogId = nil		-- current dialog id
DialogLayerController.currentDialogModel = nil
DialogLayerController.isDialogInProcess = nil	-- whether the dialog is in progress
DialogLayerController.responseDialogs = nil		-- 响应的对话内容
DialogLayerController.currentResponseModel = nil	-- 当前的Response model
DialogLayerController.currentResponseIndex = nil	-- 当前响应到的index

-- const values
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

	self:renderView()
end

function DialogLayerController:unload()
	log("DialogLayerController:unload")
	self:removeObservers()
	self.root:removeFromParent()
	self:cleanResources()
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
	Notifier:addObserver(NotifyEvents.MapView.ResponseBegan, self, self.onResponseBegan)
	-- Notifier:addObserver(NotifyEvents.MapView.MapStateChanged, self, self.onMapStateChanged)
end

function DialogLayerController:removeObservers()
	log("DialogLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionEnded, self)
	Notifier:removeObserver(NotifyEvents.MapView.ResponseBegan, self)
	-- Notifier:removeObserver(NotifyEvents.MapView.MapStateChanged, self)
end

function DialogLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	self.root = cc.Layer:create()
	self.root:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	-- dialog window initialization
	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	local windowSize = CCSizeMake(screenSize.width * 0.95, screenSize.height * 0.2)
	local windowPos = ccp(screenSize.width * 0.5, screenSize.height * 0.1)
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
	self.currentDialogId = DataCenter.currentPlayerData.lastDialogId ~= DBNULL and DataCenter.currentPlayerData.lastDialogId or 0

	self.root:setVisible(false)
	self:getScene():addChild(self.root)

	-- 如果是新游戏则自动开始剧情
	if self.currentDialogId == 0 then
		DataCenter.currentPlayerData:enterStory()
		self:generateNextDialog()
	end
	--CallFunctionAsync(self, self.generateNextDialog, 2.5)
end

function DialogLayerController:onNodeEvent(event)
	if event == "enter" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self.root)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
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
			self.touchListener = nil
		end
	end
end

function DialogLayerController:onMapStateChanged(oldState, newState)
	if newState == Enumerations.MAP_STATE.DIALOG then
		self:setEnabled(true)
	elseif newState ~= Enumerations.MAP_STATE.DIALOG then
		self:setEnabled(false)
	end
end

-- set controller state
function DialogLayerController:setEnabled(isEnabled)
	if isEnabled then
		self.root:setVisible(true)
	else
		self.root:setVisible(false)
	end

	-- 控制事件响应
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		if self.kbdListener then
			self.kbdListener:setEnabled(isEnabled)
		end
	else
		if self.touchListener then
			self.touchListener:setEnabled(isEnabled)
		end
	end
end

function DialogLayerController:onKeyboardPressed(keyCode)
	log("DialogLayerController:onKeyboardPressed", keyCode)
	if ActionController.isUnderAction then
		return
	end
	if keyCode == GameSettings.confirmKey or keyCode == GameSettings.cancelKey then
		self:handleDialogDisplay()
	end
end

function DialogLayerController:onTouch(touch, event)
	log("DialogLayerController:onTouch")
	if ActionController.isUnderAction or DataCenter.currentPlayerData.currentStep == 0 then
		return
	end
	self:handleDialogDisplay()
	return true
end

function DialogLayerController:handleDialogDisplay()
	if self.isDialogInProcess then
		self.isDialogInProcess = false
		self.root:stopAllActions()
		-- 普通的npc对话
		if ResponseController.isUnderResponse then
			local dialog = self.responseDialogs[self.currentResponseIndex]
			if self.currentResponseModel.speaker ~= DBNULL then
				dialog = self.currentResponseModel.speaker .. ": " .. dialog
			end
			self.dialogLabel:setString(dialog)
		else
			-- 剧情对话
			self.dialogLabel:setString(self.currentDialogModel.speaker .. ": " .. self.currentDialogModel:getCorrectDialog())
		end
		self.dialogIndice:setVisible(true)
	else
		GameVolumeHelper:playBtnClickSound()

		if ResponseController.isUnderResponse then
			self:generateNextResponse()
		else
			self:generateNextDialog()
		end
	end
end

-- 生成下一段剧情对话
function DialogLayerController:generateNextDialog()
	log("DialogLayerController:generateNextDialog")
	log("current dialog id: " .. self.currentDialogId)
	-- 执行action处理 如果有的话
	if self.currentDialogModel and not ActionController.isUnderAction then
		if self.currentDialogModel.actionId ~= DBNULL then
			-- 如果action是-1，则进入自由活动
			self.root:setVisible(false)
			if tonumber(self.currentDialogModel.actionId) == -1 then
				self.currentDialogModel = nil
				DataCenter.currentPlayerData.lastDialogId = self.currentDialogId
				DataCenter.currentPlayerData:enterFreedom()
			else
				local actionModel = ActionInfo:create(self.currentDialogModel.actionId)
				ActionController:processAction(actionModel)
				-- 处理event
				if self.currentDialogModel.eventId ~= DBNULL then
					local eventModel = EventInfo:create(self.currentDialogModel.eventId)
					EventController:processEvent(eventModel)
				end
			end
			return
		end
	else
		ActionController.isUnderAction = false
		self.root:setVisible(true)
		MapStateController:setCurrentState(Enumerations.MAP_STATE.DIALOG)
	end

	self.dialogIndice:setVisible(false)
	self.currentDialogId = self.currentDialogId + 1
	local currentDialog = Dialog:create(self.currentDialogId)
	local substrings = GenerateAllUTF8Substrings(currentDialog:getCorrectDialog())
	self.currentDialogModel = currentDialog

	self.isDialogInProcess = true
	self:showTextOneByOne(substrings, 1)
end

-- 生成下一段对话
function DialogLayerController:generateNextResponse()
	log("DialogLayerController:generateNextResponse")
	log("current response index: " .. self.currentResponseIndex)

	if self.currentResponseIndex >= #self.responseDialogs then
		-- 普通对话完毕, 清空数据
		self.currentResponse = nil
		self.responseDialogs = nil
		self.root:setVisible(false)
		DataCenter.currentPlayerData:enterFreedom(false)
		ResponseController.isUnderResponse = false
	else
		self.root:setVisible(true)
		self.dialogIndice:setVisible(false)
		self.currentResponseIndex = self.currentResponseIndex + 1
		local currentResponse = self.responseDialogs[self.currentResponseIndex]
		local substrings = GenerateAllUTF8Substrings(currentResponse)

		self.isDialogInProcess = true
		self:showTextOneByOne(substrings, 1)
	end
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
	if ResponseController.isUnderResponse then
		local dialog = substrings[index]
		if self.currentResponseModel.speaker ~= DBNULL then
			dialog = self.currentResponseModel.speaker .. ": " .. dialog
		end
		self.dialogLabel:setString(dialog)
	else
		self.dialogLabel:setString(self.currentDialogModel.speaker .. ": " .. substrings[index])
	end
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

-------------------------- Response 处理函数 --------------------------
function DialogLayerController:response_Speak(params)
	self.responseDialogs = string.split(params, ";")
	self.currentResponseIndex = 0
	self:handleDialogDisplay()
end

function DialogLayerController:response_SpeakWithRest(params)
	-- temp
	self:response_Speak(params)
end

function DialogLayerController:response_ShowLayer(params)
	
end

-------------------------- Response 相关回调函数 --------------------------
function DialogLayerController:onResponseBegan(responseModel)
	log("MapLayerController:onResponseBegan", responseModel.handler)
	self.currentResponseModel = responseModel
	local responseHandler = responseModel.handler
	local handler = self["response_" .. responseHandler]
	assert(type(handler) == "function", "Unimplemented response handler in ResponseController.")
	handler(self, responseModel.params)
end