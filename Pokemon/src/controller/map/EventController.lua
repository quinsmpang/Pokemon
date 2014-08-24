--[[
	Description: Event controller, handling events
	Author: M.Wan
	Date: 07/29/2014
]]

EventController = {}

function EventController:processEvent(eventModel)
	log("EventController:processEvent", eventModel.eventType, eventModel.eventParams, eventModel.handler)
	local eventHandler = self["event_" .. eventModel.handler]
	assert(type(eventHandler) == "function", "Unimplemented event handler in EventController.")
	eventHandler(self, eventModel.eventParams)
end

-------------------------- Event 处理函数 --------------------------
function EventController:event_gainNewPokemon(params)
	local data = string.split(params, ",")
	data = table.cast(data, function(item) return tonumber(item) end)
	local pokemonId = data[1]
	local level = data[2]
	local pokemon = Pokemon:create(pokemonId, level)

	DataCenter:addNewPokemon(pokemon)
end