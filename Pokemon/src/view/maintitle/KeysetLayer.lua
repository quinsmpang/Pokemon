--[[
	Description: Keyset Window
	Author: M.Wan
	Date: 05/24/2014
]]

class("KeysetLayer", psModalLayer)

KeysetLayer.window = nil		--背景窗口
KeysetLayer.border = nil		--窗口边框
KeysetLayer.btnConfirm = nil	--确定按钮
KeysetLayer.btnCancel = nil		--取消按钮
KeysetLayer.panelList = nil		--所有按键Panel的集合

KeysetLayer.kbdListener = nil
KeysetLayer.isWaitingForKey = nil		--是否正在等待用户按键
KeysetLayer.availableKeys = nil
KeysetLayer.enableClick = nil		--是否允许用户点击
KeysetLayer.runningLabel = nil
KeysetLayer.runningIndex = nil

-- const value
KeysetLayer.TAG = {
	WINDOW = 1,
	UP_PANEL = 2,
	DOWN_PANEL = 3,
	LEFT_PANEL = 4,
	RIGHT_PANEL = 5,
	A_PANEL = 6,
	B_PANEL = 7,
	START_PANEL = 8,
		KEY_LABEL = 11,
}

function KeysetLayer:initUI()
	log("KeysetLayer:initUI")

	self.isWaitingForKey = false
	self.enableClick = false

	-- init available keys which can set.
	self:setAvailableKeys()

	-- init ui
	self.window = ScriptCCBReader:readCCB("ccb/KeysetLayer.ccbi", self)
	self.window:setPosition(0, 0)
	self.window:setScale(0)
	self:addChild(self.window)

	self.border = self.window:getChildByTag(self.TAG.WINDOW)
	tolua.cast(self.border, "cc.Scale9Sprite")

	-- set panel list
	self.panelList = {}
	for i = 2, 8 do
		table.insert(self.panelList, self.window:getChildByTag(i))
	end

	-- set key label content
	assert(#self.panelList == 7, "Incorrect panel count")

	table.forEachAsHash(self.panelList, MakeScriptHandler(self, self.setKeyString))

	-- init buttons
	local windowSize = self.border:getContentSize()

	local btnConfirmLabel = cc.Label:createWithTTF("保存", GameConfig.DEFAULT_FONT_PATH, 22)
	local btnBack = cc.Scale9Sprite:createWithSpriteFrameName("images/common/black_back.png", CCRectMake(1, 1, 1, 1))
	self.btnConfirm = cc.ControlButton:create(btnConfirmLabel, btnBack)
	self.btnConfirm:setAnchorPoint(0.5, 0.5)
	self.btnConfirm:setPosition(windowSize.width * 0.35, windowSize.height * 0.24)
	self.btnConfirm:registerControlEventHandler(MakeScriptHandler(self, self.onBtnConfirmClick), cc.Handler.CONTROL_TOUCH_UP_INSIDE)
	self.border:addChild(self.btnConfirm)

	local btnCancelLabel = cc.Label:createWithTTF("关闭", GameConfig.DEFAULT_FONT_PATH, 22)
	btnBack = cc.Scale9Sprite:createWithSpriteFrameName("images/common/black_back.png", CCRectMake(1, 1, 1, 1))
	self.btnCancel = cc.ControlButton:create(btnCancelLabel, btnBack)
	self.btnCancel:setAnchorPoint(0.5, 0.5)
	self.btnCancel:setPosition(windowSize.width * 0.65, windowSize.height * 0.24)
	self.btnCancel:registerControlEventHandler(MakeScriptHandler(self, self.onBtnCancelClick), cc.Handler.CONTROL_TOUCH_UP_INSIDE)
	self.border:addChild(self.btnCancel)

	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
	end
end

function KeysetLayer:onNodeEvent(event)
	if event == "enter" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		end
	elseif event == "exit" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
			self.kbdListener = nil
		end
	end
end

function KeysetLayer:setAvailableKeys()
	local tmpDict = {}
	for k, v in pairs(cc.KeyCode) do
		tmpDict[v] = k
	end

	self.availableKeys = {}
	self.availableKeys[pf.Win32KeyCode.VK_RETURN] = "ENTER"
	self.availableKeys[pf.Win32KeyCode.VK_INSERT] = "INSERT"
	self.availableKeys[pf.Win32KeyCode.VK_HOME] = "HOME"
	self.availableKeys[pf.Win32KeyCode.VK_SELECT] = "SELECT"
	self.availableKeys[pf.Win32KeyCode.VK_PGUP] = "PG_UP"
	self.availableKeys[pf.Win32KeyCode.VK_PGDOWN] = "PG_DOWN"
	self.availableKeys[pf.Win32KeyCode.VK_DELETE] = "DELETE"
	self.availableKeys[pf.Win32KeyCode.VK_END] = "END"
	self.availableKeys[pf.Win32KeyCode.VK_LEFT] = "←"
	self.availableKeys[pf.Win32KeyCode.VK_RIGHT] = "→"
	self.availableKeys[pf.Win32KeyCode.VK_UP] = "↑"
	self.availableKeys[pf.Win32KeyCode.VK_DOWN] = "↓"
	self.availableKeys[pf.Win32KeyCode.VK_SPACE] = "SPACE"
	self.availableKeys[pf.Win32KeyCode.VK_MINUS] = "-"
	self.availableKeys[pf.Win32KeyCode.VK_EQUAL] = "="
	-- keypad numbers
	for i = 0x60, 0x69 do
		self.availableKeys[i] = "N-" .. (i - 0x60)
	end
	-- numbers
	for i = 48, 57 do
		self.availableKeys[i] = tostring(i - 48)
	end
	self.availableKeys[65] = "A"
	self.availableKeys[66] = "B"
	self.availableKeys[67] = "C"
	self.availableKeys[68] = "D"
	self.availableKeys[69] = "E"
	self.availableKeys[70]= "F"
	self.availableKeys[71]= "G"
	self.availableKeys[72] = "H"
	self.availableKeys[73] = "I"
	self.availableKeys[74] = "J"
	self.availableKeys[75] = "K"
	self.availableKeys[76] = "L"
	self.availableKeys[77] = "M"
	self.availableKeys[78] = "N"
	self.availableKeys[79] = "O"
	self.availableKeys[80] = "P"
	self.availableKeys[81] = "Q"
	self.availableKeys[82] = "R"
	self.availableKeys[83] = "S"
	self.availableKeys[84] = "T"
	self.availableKeys[85] = "U"
	self.availableKeys[86] = "V"
	self.availableKeys[87] = "W"
	self.availableKeys[88] = "X"
	self.availableKeys[89] = "Y"
	self.availableKeys[90] = "Z"
	self.availableKeys[pf.Win32KeyCode.VK_CONTROL] = "CTRL"
	self.availableKeys[pf.Win32KeyCode.VK_SHIFT] = "SHIFT"
	self.availableKeys[pf.Win32KeyCode.VK_ALT] = "ALT"
end

function KeysetLayer:setKeyString(index, panel)
	local keyCode = GameSettings.Keys[index]
	if self.availableKeys[keyCode] then
		local label = panel:getChildByTag(self.TAG.KEY_LABEL)
		tolua.cast(label, "cc.Label")
		label:setString(self.availableKeys[keyCode])
	end
end

function KeysetLayer:onComeIn()
	local enterAction = cc.Sequence:create(
		cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
		cc.ScaleTo:create(0.03, 1),
		cc.CallFunc:create(MakeScriptHandler(self, self.onComeInEnd))
		)

	self.window:runAction(enterAction)
end
function KeysetLayer:onComeInEnd()
	self.enableClick = true
end

function KeysetLayer:onGoOut()
end

function KeysetLayer:onModalTouchBegan(x, y)
	if not self.enableClick then
		return
	end
	for i, panel in ipairs(self.panelList) do
		if ContainsPoint(panel:getBoundingBox(), ccp(x, y)) then
			self:selectPanel(i, panel)
			break
		end
	end
end

function KeysetLayer:selectPanel(index, panel)
	log("KeysetLayer:selectPanel")

	local keyLabel = panel:getChildByTag(self.TAG.KEY_LABEL)

	-- stop running label actions if there exists
	if self.runningLabel then
		self.runningLabel:stopAllActions()
		self.runningLabel:setVisible(true)
		if self.runningLabel == keyLabel then
			self:exitWaitingStatus()
			return
		end
	end

	local blinkAction = cc.RepeatForever:create(cc.Sequence:create(
		cc.Show:create(),
		cc.DelayTime:create(0.5),
		cc.Hide:create(),
		cc.DelayTime:create(0.5)
		))

	keyLabel:runAction(blinkAction)

	self.isWaitingForKey = true
	self.runningLabel = keyLabel
	self.runningIndex = index
end

function KeysetLayer:exitWaitingStatus()
	self.isWaitingForKey = false
	self.runningLabel = nil
	self.runningIndex = nil
end

function KeysetLayer:onBtnConfirmClick()
	if not self.enableClick then
		return
	end
	log("KeysetLayer:onBtnConfirmClick")

	GameVolumeHelper:playBtnClickSound()

	GameSettings:saveSettings()

	self:close()
end

function KeysetLayer:onBtnCancelClick()
	if not self.enableClick then
		return
	end
	log("KeysetLayer:onBtnCancelClick")

	GameVolumeHelper:playBtnClickSound()

	GameSettings:loadSettings()
	self:close()
end

function KeysetLayer:close()
	local quitAction = cc.Sequence:create(
		cc.EaseOut:create(cc.ScaleTo:create(0.15, 0), 2),
		cc.TargetedAction:create(self, cc.RemoveSelf:create())
		)

	self.window:runAction(quitAction)
end

function KeysetLayer:onKeyboardPressed(keyCode)
	if not self.isWaitingForKey then
		return
	end
	log(string.format("KeysetLayer:onKeyboardPressed: %x", keyCode))

	if self.availableKeys[keyCode] then
		self:handleNewKey(keyCode)

		self.runningLabel:stopAllActions()
		self.runningLabel:setVisible(true)
		self:exitWaitingStatus()
	else
		GameVolumeHelper:playUnableSound()
	end
end

function KeysetLayer:handleNewKey(keyCode)
	assert(self.runningLabel, "running label should not be nil")
	local oldStr = self.runningLabel:getString()
	self.runningLabel:setString(self.availableKeys[keyCode])

	-- check whether there is conflict keys, if exists, exchange them.
	local index = 1
	local exchangeExists = false
	while index <= #GameSettings.Keys do
		if index ~= self.runningIndex and GameSettings.Keys[index] == keyCode then
			log(string.format("Exchange keys: %d, %d", self.runningIndex, index))
			GameSettings.Keys[index], GameSettings.Keys[self.runningIndex] = GameSettings.Keys[self.runningIndex], keyCode
			local exchangePanel = self.panelList[index]
			local exchangeLabel = exchangePanel:getChildByTag(self.TAG.KEY_LABEL)
			exchangeLabel:setString(oldStr)
			exchangeExists = true
			break
		end
		index = index + 1
	end

	if not exchangeExists then
		GameSettings.Keys[self.runningIndex] = keyCode
	end
end