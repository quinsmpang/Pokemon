--[[
	Description: Collection main view
	Author: M.Wan
	Date: 11/30/2014
]]

class("CollectionView", psGameLayer)

CollectionView.root = nil

CollectionView.__create = psGameLayer.create

function CollectionView:create()
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setCascadeOpacityEnabled(true)
	mask:retain()
	local layer = CollectionView:createWithTransitions(
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15))
		)
	layer.mask = mask
	layer:init()

	return layer
end

function CollectionView:init()
	local modalLayer = ModalLayer:create()
	self:addChild(modalLayer)
	self.root = modalLayer

	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/collection/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.root:addChild(bg)

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	if self.mask then
		self.root:addChild(self.mask, 999)
		self.mask:release()
	end
end

function CollectionView:onNodeEvent(event)
	if event == "enter" then
		self.mask:runAction(cc.FadeOut:create(0.15))

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

function CollectionView:onKeyboardPressed(keyCode)
	Notifier:notify(NotifyEvents.Collection.MainViewKeyResponsed, keyCode)
end