--[[
	Description: Specility info (from DB)
	Author: M.Wan
	Date: 11/18/2014
]]

luaClass("SpecialityInfo", psModel)

-- db attributes
SpecialityInfo.id = DBNULL
SpecialityInfo.name = DBNULL
SpecialityInfo.description = DBNULL
SpecialityInfo.params = DBNULL

function SpecialityInfo:create(id)
	local model = SpecialityInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function SpecialityInfo:updateFromDB()
	log("SpecialityInfo:updateFromDB")

	local data = GameDBHelper:querySpecialityById(self.id)
	if data then
		self:updateWithData(data)

		self.id = tonumber(data.id)
	else
		log("SpecialityInfo:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end