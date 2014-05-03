--[[
	Description: Model base
	Author: M.Wan
	Date: 04/29/2014
]]

-- null in database transfered to game is a null string, so when you use a model, you should use DBNULL instead of nil
DBNULL = "null"

luaClass("psModel")

function psModel:init()
	local data = self:getDataFromDB()
	self:updateWithData(data)
end

-- data is the lua table from db.
function psModel:updateWithData(data)
	table.deepCopy(self, data)
end

function psModel:getDataFromDB()
	-- override me
end