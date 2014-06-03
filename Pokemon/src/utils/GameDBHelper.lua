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
	values:setStringForKey("id", "1")
	values:setStringForKey("name", "Maple")
	values:setStringForKey("age", "23")
	self.db:insertTable("test", values)
end