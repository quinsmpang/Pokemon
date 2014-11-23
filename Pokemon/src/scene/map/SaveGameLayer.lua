--[[
	Description: Save game layer
	Author: M.Wan
	Date: 11/23/2014
]]

class("SaveGameLayer", psModalLayer)

SaveGameLayer.list = nil		-- 询问框

SaveGameLayer.__create = psModalLayer.create

function SaveGameLayer:create()
	local layer = SaveGameLayer:__create()
	layer:init()
	return layer
end

function SaveGameLayer:init()
	local screenSize = cc.Director:getInstance():getWinSize()

	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	local windowSize = CCSizeMake(screenSize.width * 0.95, screenSize.height * 0.2)
	local windowPos = ccp(screenSize.width * 0.5, screenSize.height * 0.1)
	dialogWindow:setPreferredSize(windowSize)
	dialogWindow:setPosition(windowPos)
	self:addChild(dialogWindow)

	local infoWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	infoWindow:setPreferredSize(CCSizeMake(screenSize.width * 0.65, screenSize.height * 0.7))
	infoWindow:setAnchorPoint(0, 0)
	infoWindow:setPosition(screenSize.width * 0.025, screenSize.height * 0.225)
	self:addChild(infoWindow)

	local listMenu = CommonListMenu:create({"是", "否"}, CCSizeMake(150, 100))
	listMenu:setAnchorPoint(1, 0)
	listMenu:setPosition(screenSize.width * 0.975, screenSize.height * 0.225)
	listMenu:setItemSelectedScript(MakeScriptHandler(self, self.onListItemSelected))
	listMenu:setCancelScript(MakeScriptHandler(self, self.onCancelSelection))	-- overwrite the default behavior
	listMenu:setKeyEventsSwallowed(false)		-- don't swallow the events
	self:addChild(listMenu)
	self.list = listMenu

	-- self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function SaveGameLayer:onNodeEvent(event)
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

function SaveGameLayer:onListItemSelected(menu, item)
	local index = item:getShowIndex()
	log("SaveGameLayer:onListItemSelected", index)
	if index == 0 then
		require "src/scene/save/GameSaveManager"

		GameSaveManager:saveTo(DataCenter.relatedSaveIndex)
		if self.list.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.list.kbdListener)
		end
		self:removeFromParent()
	elseif index == 1 then
		if self.list.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.list.kbdListener)
		end
		self:removeFromParent()
	end
end

function SaveGameLayer:onCancelSelection()
	self.list:removeFromParent()
	self:removeFromParent()
end

function SaveGameLayer:onKeyboardPressed(keyCode)
	log("SaveGameLayer:onKeyboardPressed")
	if keyCode == GameSettings.cancelKey then
		self:removeFromParent()
	end
end