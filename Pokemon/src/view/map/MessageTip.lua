--[[
	Description: map message tip
	Author: M.Wan
	Date: 07/12/2014
]]

class("MessageTip", psModalLayer)

MessageTip.message = nil 		-- 消息内容
MessageTip.callback = nil 		-- 点击后的回调
MessageTip.touchListener = nil
MessageTip.keyboardListener = nil

MessageTip.FONT_SIZE = 18
MessageTip.FONT_COLOR = ccc3(255, 0, 0)

MessageTip.__create = psModalLayer.create

function MessageTip:create(message, callback)
	local dialog = MessageTip:__create()
	dialog:init(message, callback)
	return dialog
end

function MessageTip:init(message, callback)
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
	if event == "exit" then
		-- 移除监听
		self:getEventDispatcher():removeEventListener(self.keyboardListener)
	end
end

function MessageTip:onModalTouchBegan(x, y)
	self:exit()
end

function MessageTip:onKeyboardPressed(keyCode)
	if keyCode == GameSettings.confirmKey or keyCode == GameSettings.cancelKey then
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