--[[
	Description: The core layer of map scene, to handle map scene keyboard events
	Author: M.Wan
	Date: 06/30/2014
]]

class("MapCoreLayer", psCoreLayer)

-- 记录基类的create方法
MapCoreLayer.__create = MapCoreLayer.create

function MapCoreLayer:create()
	local instance = MapCoreLayer:__create()
	if not instance then
		return nil
	end

	instance:init()

	return instance
end

function MapCoreLayer:init()
	log("MapCoreLayer:init")

	if targetPlatform == cc.PLATFORM_OS_WINDOWS then
		local kbdListener = cc.EventListenerKeyboard:create()
		kbdListener:registerScriptHandler(MakeScriptHandler(self, self.onKeyboardPressed), cc.Handler.EVENT_KEYBOARD_PRESSED)
		kbdListener:registerScriptHandler(MakeScriptHandler(self, self.onKeyboardReleased), cc.Handler.EVENT_KEYBOARD_RELEASED)

		self:getEventDispatcher():addEventListenerWithSceneGraphPriority(kbdListener, self)
	end	
end

function MapCoreLayer:onKeyboardPressed(keyCode, event)
	log("MapCoreLayer:onKeyboardPressed")
	-- 分发事件
	if MapStateController.currentState == Enumerations.MAP_STATE.FREEDOM then
		Notifier:notify(NotifyEvents.MapView.MapKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.PRESSED)
	elseif MapStateController.currentState == Enumerations.MAP_STATE.DIALOG then
		Notifier:notify(NotifyEvents.MapView.DialogKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.PRESSED)
	elseif MapStateController.currentState == Enumerations.MAP_STATE.MENU then
		Notifier:notify(NotifyEvents.MapView.MenuKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.PRESSED)
	end
end

function MapCoreLayer:onKeyboardReleased(keyCode, event)
	log("MapCoreLayer:onKeyboardReleased")
	-- 分发事件
	if MapStateController.currentState == Enumerations.MAP_STATE.FREEDOM then
		Notifier:notify(NotifyEvents.MapView.MapKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.RELEASED)
	elseif MapStateController.currentState == Enumerations.MAP_STATE.DIALOG then
		Notifier:notify(NotifyEvents.MapView.DialogKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.RELEASED)
	elseif MapStateController.currentState == Enumerations.MAP_STATE.MENU then
		Notifier:notify(NotifyEvents.MapView.MenuKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.RELEASED)
	end
end