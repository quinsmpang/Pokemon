--[[
	Description: Model base
	Author: M.Wan
	Date: 04/29/2014
]]

-- null in database transfered to game is a null string, so when you use a model, you should use DBNULL instead of nil
DBNULL = "null"

luaClass("psModel")

psModel.updateFlag = false

-- override init.
function psModel:init()
	
end

