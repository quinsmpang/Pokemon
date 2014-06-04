--[[
	Description: Game database helper class
	Author: M.Wan
	Date: 05/30/2014
]]

GameDBHelper = {}

GameDBHelper.db = nil		-- sqlite3 db instance

function GameDBHelper:openDB()
	self.db = SqliteDb:openSqlite(GameConst.GAME_DB_PATH)

	local columns = Vector:create()
	columns:addString("id")
	columns:addString("name")
	columns:addString("age")

	self.db:createTable("test", columns)

	local values = Map:create()
	values:setStringForKey("1", "id")
	values:setStringForKey("Maple", "name")
	values:setStringForKey("23", "age")
	self.db:insertTable("test", values)

	local table = self.db:selectTable("test")
	local count = table:getLength()
	log("table count", count)
	for i = 0, count do
		local dict = table:objectAt(i)
		local keys = dict:allKeys()
		for i = 0, keys:getLength() - 1 do
			local key = keys:objectAt(i)
			local value = dict:objectForKey(key:getCString())
			log(key:getCString(), value:getCString())
		end
	end

	-- local sqliteLua = SqliteLua:openSqlite(GameConst.GAME_DB_PATH)
	-- local table = SqliteLua:selectTableAsLuaTable("test")
end