--[[
	Description: map message tip
	Author: M.Wan
	Date: 07/12/2014
]]

class("MessageTip", psModalLayer)

MessageTip.window = nil
MessageTip.message = nil 		-- 消息内容
MessageTip.callback = nil 		-- 点击后的回调
MessageTip.touchListener = nil
MessageTip.keyboardListener = nil
MessageTip.enableClick = nil

MessageTip.FONT_SIZE = 18
MessageTip.FONT_COLOR = ccc3(255, 0, 0)
MessageTip.DELAY_TIME = 1.5

MessageTip.__create = psModalLayer.create

function MessageTip:create(message, callback)
	local dialog = MessageTip:__create()
	dialog:init(message, callback)
	return dialog
end

function MessageTip:init(message, callback)
	self.enableClick = false
	self.message = message
	self.callback = callback

	local winSize = cc.Director:getInstance():getWinSize()

	local label = cc.Label:createWithTTF(message, GameConfig.DEFAULT_FONT_PATH, self.FONT_SIZE)
	label:setColor(self.FONT_COLOR)
	local labelSize = label:getContentSize()
	local suitableSize = CCSizeMake(labelSize.width + 30, labelSize.height + 25)
	local border = cc.Scale9Sprite:createWithSpriteFrameName("images/map/message_tip.png", CCRectMake(20, 20, 10, 10))
	border:setPreferredSize(suitableSize)
	border:setPosition(winSize.width * 0.5, winSize.height * 0.65)
	border:setScale(0)
	self.window = border

	label:setPosition(border:getContentSize().width * 0.5, border:getContentSize().height * 0.5)
	border:addChild(label)

	self:addChild(border)

	-- 注册事件
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		local kbdListener = cc.EventListenerKeyboard:create()
		kbdListener:registerScriptHandler(MakeScriptHandler(self, self.onKeyboardPressed), cc.Handler.EVENT_KEYBOARD_PRESSED)
		self.keyboardListener = kbdListener
		self:getEventDispatcher():addEventListenerWithSceneGraphPriority(kbdListener, self)

		self:registerScriptHandler(MakeScriptHandler(self, self.onSceneEvent))
	end
end

function MessageTip:pop()
	local scene = cc.Director:getInstance():getRunningScene()
	scene:addChild(self)
end

function MessageTip:onSceneEvent(event)
	if event == "enter" then
		local delayAction = cc.Sequence:create(
			cc.DelayTime:create(self.DELAY_TIME),
			cc.CallFunc:create(MakeScriptHandler(self, self.onEnterEnd))
			)
		self:runAction(delayAction)

		local enterAction = cc.Sequence:create(
			cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
			cc.ScaleTo:create(0.03, 1)
			)
		self.window:runAction(enterAction)

		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		end
	elseif event == "exit" then
		-- 移除监听
		if self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
		end
	end
end
function MessageTip:onEnterEnd()
	self.enableClick = true
end

function MessageTip:onKeyboardPressed(keyCode)
	if self.enableClick and (keyCode == GameSettings.confirmKey or keyCode == GameSettings.cancelKey) then
		self:exit()
	end
end

function MessageTip:exit()
	local callback = self.callback
	self:removeFromParent()
	if callback then
		callback()
	end
end