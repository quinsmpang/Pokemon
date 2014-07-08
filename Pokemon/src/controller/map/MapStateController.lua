--[[
	Description: Map state controller, to manipulate map state
	Author: M.Wan
	Date: 06/30/2014
]]

MapStateController = {}

MapStateController.currentState = nil	-- 当前地图状态
MapStateController.entranceMapId = nil	-- 是否通过入口切换地图

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

-- 标记入口切换
function MapStateController:setEntranceMapId(entranceMapId)
	log("MapStateController:setEntranceMapId", entranceMapId)
	self.entranceMapId = entranceMapId
end

function MapStateController:getEntranceMapId()
	return self.entranceMapId
end