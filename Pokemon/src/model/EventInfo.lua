--[[
	Description: Event info (from DB)
	Author: M.Wan
	Date: 07/29/2014
]]

luaClass("EventInfo", psModel)

EventInfo.id = DBNULL
EventInfo.eventType = DBNULL	-- 事件类型
EventInfo.eventParams = DBNULL	-- 事件参数
EventInfo.handler = DBNULL		-- 处理函数

function EventInfo:create(id)
	local model = EventInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function EventInfo:updateFromDB()
	log("EventInfo:updateFromDB")

	local data = GameDBHelper:queryEventById(self.id)
	if data then
		self:updateWithData(data)

		self.eventType = tonumber(data.eventType)
	else
		log("EventInfo:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end