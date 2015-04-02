--[[
	Description: battle menu controller
	Author: M.Wan
	Date: 4/2/2015
]]

class("BattleMenuController", psViewController)

require "src/scene/battle/BattleCommonMenu"

BattleMenuController.root = nil

BattleMenuController.battleMenu = nil		-- 战斗菜单
BattleMenuController.skillMenu = nil		-- 技能菜单
BattleMenuController.focusMenu = nil		-- 当前锁定的菜单

BattleMenuController.BATTLE_INSTRUCTIONS = {
	"战斗", "背包", "精灵", "逃跑",
}

local winSize = cc.Director:getInstance():getWinSize()

function BattleMenuController:load()
	self:addObservers()
	self:renderView()
end

function BattleMenuController:unload()
	self:removeObservers()
	self.root:removeFromParent(true)
end

function BattleMenuController:addObservers()
	Notifier:addObserver(NotifyEvents.Battle.ShowBattleMenu, self, self.onShowBattleMenu)
end

function BattleMenuController:removeObservers()
	Notifier:removeObserver(NotifyEvents.Battle.ShowBattleMenu, self)
end

function BattleMenuController:renderView()
	self.root = cc.Layer:create()
	self.root:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
	self:getScene():addChild(self.root)

	self.battleMenu = BattleCommonMenu:create(self.BATTLE_INSTRUCTIONS)
	self.battleMenu:setPosition(winSize.width * 0.8, winSize.height * 0.1)
	self.battleMenu:setVisible(false)
	self.root:addChild(self.battleMenu)

	self.focusMenu = self.battleMenu
end

function BattleMenuController:onNodeEvent(event)
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

function BattleMenuController:onKeyboardPressed(keyCode)
	if keyCode == GameSettings.leftKey then
		self.focusMenu:cursorLeft()
	elseif keyCode == GameSettings.rightKey then
		self.focusMenu:cursorRight()
	elseif keyCode == GameSettings.upKey then
		self.focusMenu:cursorUp()
	elseif keyCode == GameSettings.downKey then
		self.focusMenu:cursorDown()
	end
end

function BattleMenuController:onShowBattleMenu()
	self.battleMenu:setVisible(true)
end