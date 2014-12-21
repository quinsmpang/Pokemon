--[[
	Description: Loading layer
	Author: M.Wan
	Date: 12/22/2014
]]

class("ProgressLayer", psModalLayer)

ProgressLayer.loadingIcon = nil
ProgressLayer.animation = animation

ProgressLayer.__create = psModalLayer.create

function ProgressLayer:create()
	local layer = ProgressLayer:__create()
	layer:init()
	return layer
end

function ProgressLayer:init()
	local winSize = cc.Director:getInstance():getWinSize()

	self.loadingIcon = cc.Sprite:create()
	self.loadingIcon:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	-- load animation
	local animation = cc.RepeatForever:create(ImageUtils:getInstance():createAnimationByGifImage("images/loading.gif", 0.06))
	animation:retain()
	self.animation = animation
	self.loadingIcon:runAction(animation)

	self:addChild(self.loadingIcon)

	self:setOpacity(100)

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function ProgressLayer:onNodeEvent(event)
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

		self.animation:release()
	end
end

function ProgressLayer:onKeyboardPressed(keyCode)
	log("ProgressLayer Loading...")
end