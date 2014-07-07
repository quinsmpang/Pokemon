--[[
	Description: Map state controller, to manipulate map state
	Author: M.Wan
	Date: 06/30/2014
]]

MapStateController = {}

MapStateController.currentState = nil	-- 当前地图状态

function MapStateController:getCurrentState()
	return self.currentState
end

function MapStateController:setCurrentState(state)
	if self.currentState == state then
		return
	end
	
	log("Change MapState from [" .. (self.currentState or "nil") .. "] to [" .. state .. "]")
	local oldState = self.currentState
	self.currentState = state

	Notifier:notify(NotifyEvents.MapView.MapStateChanged, oldState, state)
end