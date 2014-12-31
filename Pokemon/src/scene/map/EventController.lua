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
	local place = data[3]
	local pokemon = Pokemon:create(pokemonId, level, nil, place)

	local res = DataCenter:addNewPokemon(pokemon)
	if res == true then
		-- 送入电脑中 显示ui todo
	elseif res == false then
		-- 电脑也满了 todo
	end
end

function EventController:event_gainNewItem(params)
	local data = string.split(params, ",")
	data = table.cast(data, function(item) return tonumber(item) end)
	local itemId = data[1]
	local num = data[2]

	DataCenter:addNewItem(itemId, num)
end

function EventController:event_gainMoney(params)
	local amount = tonumber(params)
	
	DataCenter:addMoney(amount)
end