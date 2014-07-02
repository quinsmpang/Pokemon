--[[
	Description: Action info (from DB)
	Author: M.Wan
	Date: 06/25/2014
]]

luaClass("ActionInfo", psModel)

-- db attributes
ActionInfo.id = DBNULL
ActionInfo.actionType = DBNULL
ActionInfo.params = DBNULL
ActionInfo.handler = DBNULL

function ActionInfo:create(id)
	local model = ActionInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function ActionInfo:updateFromDB()
	log("ActionInfo:updateFromDB")

	local data = GameDBHelper:queryActionInfoById(self.id)
	if data then
		self:updateWithData(data)

		self.actionType = tonumber(data.actionType)
	else
		log("ActionInfo:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end