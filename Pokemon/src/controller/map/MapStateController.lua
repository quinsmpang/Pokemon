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
	log("Change MapState from [" .. (self.currentState or "nil") .. "] to [" .. state .. "]")
	self.currentState = state
end