--[[
	Description: Menu layer on the map
	Author: M.Wan
	Date: 07/06/2014
]]

class("MapMenuLayer", psModalLayer)

require "src/scene/map/MapMenu"

MapMenuLayer.back = nil 			-- 背景

MapMenuLayer.keyboardListener = nil

MapMenuLayer.__create = psModalLayer.create

function MapMenuLayer:create()
	local mapMenu = MapMenuLayer:__create()
	mapMenu:init()
	return mapMenu
end

function MapMenuLayer:init()
	local screenSize = cc.Director:getInstance():getWinSize()

	self:setOpacity(0.1 * 255)

	-- menu background
	self.back = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", CCRectMake(20, 20, 60, 60))
	self.back:setPreferredSize(CCSizeMake(screenSize.width * 0.18, screenSize.height * 0.75))
	self.back:setAnchorPoint(1, 1)
	self.back:setPosition(screenSize.width - screenSize.height * 0.05 , screenSize.height * 0.85)
	self:addChild(self.back)

	local listMenu = MapMenu:create()
	listMenu:reloadData()
	listMenu:ignoreAnchorPointForPosition(false)
	listMenu:setAnchorPoint(0.5, 1)
	listMenu:setPosition(self.back:getContentSize().width * 0.5, self.back:getContentSize().height * 0.95)
	self.listMenu = listMenu
	self.back:addChild(listMenu)

	self:registerScriptHandler(MakeScriptHandler(self, self.onSceneEvent))
end

function MapMenuLayer:onSceneEvent(event)
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

function MapMenuLayer:onKeyboardPressed(keyCode)
	log("MapMenuLayer:onKeyboardPressed")
	if keyCode == GameSettings.startKey or keyCode == GameSettings.cancelKey then
		self:exitMenu()
	end
end

function MapMenuLayer:exitMenu()
	self:removeFromParent(false)
	-- self:setVisible(false)
	MapStateController:setCurrentState(Enumerations.MAP_STATE.FREEDOM)
end

function MapMenuLayer:validateAllItems()
	self.listMenu:validateAllItems()
end