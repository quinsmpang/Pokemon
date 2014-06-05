--[[
	Description: Game database helper class
	Author: M.Wan
	Date: 05/30/2014
]]

GameDBHelper = {}

GameDBHelper.db = nil		-- sqlite3 db instance

function GameDBHelper:openDB()
	-- self.db = SqliteDb:openSqlite(GameConst.GAME_DB_PATH)

	-- local columns = Vector:create()
	-- columns:addString("id")
	-- columns:addString("name")
	-- columns:addString("age")

	-- self.db:createTable("test", columns)

	-- local values = Map:create()
	-- values:setStringForKey("1", "id")
	-- values:setStringForKey("Maple", "name")
	-- values:setStringForKey("23", "age")
	-- self.db:insertTable("test", values)

	-- local table = self.db:selectTable("test")
	-- local count = table:getLength()
	-- log("table count", count)
	-- for i = 0, count - 1 do
	-- 	local dict = table:objectAt(i)
	-- 	local keys = dict:allKeys()
	-- 	log("key count", keys:getLength())
	-- 	for i = 0, keys:getLength() - 1 do
	-- 		local key = keys:objectAt(i)
	-- 		local value = dict:objectForKey(key:getCString())
	-- 		tolua.cast(value, "pf.RefString")
	-- 		log(key:getCString(), value:getCString())
	-- 	end
	-- end

	self.db = SqliteLua:openSqlite(GameConst.GAME_DB_PATH)
	self.db:createTableByLuaArray("test", {"id", "name", "age"})
	self.db:insertLuaTableIntoDB({ id = 1, name = "Maple", age = 23 }, "test")
	self.db:insertLuaTableIntoDB({ id = 2, name = "Mary", age = 22 }, "test")
	self.db:updateLuaTableIntoDB({ id = 2, name = "Frank", age = 21 }, "test")
	self.db:deleteFromTableByConditions("test", {id = 1, name = "Maple"})

	local table = self.db:selectTableByConditionWithMultipleValues("test", "id", {"1", "2"})
	for _, v in ipairs(table) do 
		for k2, v2 in pairs(v) do
			print(k2, v2)
		end
	end
end