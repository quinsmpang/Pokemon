--[[
	Description: Event controller, handling events
	Author: M.Wan
	Date: 07/29/2014
]]

EventController = {}

function EventController:processEvent(eventModel)
	log("EventController:processEvent", eventModel.eventType, eventModel.eventParams)
	local eventHandler = self["event_" .. eventModel.handler]
	assert(type(handler) == "function", "Unimplemented event handler in EventController.")
	handler(self, eventHandler.eventParams)
end

-------------------------- Event 处理函数 --------------------------
function EventController:event_gainNewPokemon(params)
	
end