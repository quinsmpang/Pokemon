--[[
	Description: The core layer of map scene, to handle map scene keyboard events
	Author: M.Wan
	Date: 06/30/2014
]]

--[[ DEPRECATED ]]
class("MapCoreLayer", psCoreLayer)

MapCoreLayer.pressedKeys = nil

MapCoreLayer.KEYBOARD_DT = 0.25

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

	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		local kbdListener = cc.EventListenerKeyboard:create()
		kbdListener:registerScriptHandler(MakeScriptHandler(self, self.onKeyboardPressed), cc.Handler.EVENT_KEYBOARD_PRESSED)
		kbdListener:registerScriptHandler(MakeScriptHandler(self, self.onKeyboardReleased), cc.Handler.EVENT_KEYBOARD_RELEASED)

		self:getEventDispatcher():addEventListenerWithSceneGraphPriority(kbdListener, self)

		self.pressedKeys = {}
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
	table.insert(self.pressedKeys, keyCode)

	CallFunctionAsync(self, self.onKeyboardLongPressed, self.KEYBOARD_DT, keyCode, event)
end

function MapCoreLayer:onKeyboardReleased(keyCode, event)
	log("MapCoreLayer:onKeyboardReleased")
	local newKeys = {}
	for _, pressedKey in ipairs(self.pressedKeys) do
		if pressedKey ~= keyCode then
			table.insert(newKeys, pressedKey)
		end
	end
	self.pressedKeys = newKeys
	-- 分发事件
	if MapStateController.currentState == Enumerations.MAP_STATE.FREEDOM then
		Notifier:notify(NotifyEvents.MapView.MapKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.RELEASED, self.pressedKeys)
	elseif MapStateController.currentState == Enumerations.MAP_STATE.DIALOG then
		Notifier:notify(NotifyEvents.MapView.DialogKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.RELEASED)
	elseif MapStateController.currentState == Enumerations.MAP_STATE.MENU then
		Notifier:notify(NotifyEvents.MapView.MenuKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.RELEASED)
	end
end

function MapCoreLayer:onKeyboardLongPressed(keyCode, event)
	if not table.contains(self.pressedKeys, function(pressedKey, key) return pressedKey == key end, keyCode) then
		return
	end
	log("MapCoreLayer:onKeyboardLongPressed")
	if MapStateController.currentState == Enumerations.MAP_STATE.FREEDOM then
		Notifier:notify(NotifyEvents.MapView.MapKeyboardResponse, keyCode, Enumerations.KEYBOARD_STATE.LONGPRESSED, self.pressedKeys)
		CallFunctionAsync(self, self.onKeyboardLongPressed, self.KEYBOARD_DT, keyCode, event)
	end
end