--[[
	Description: Child class of SqliteDb
	Author: M.Wan
	Date: 04/26/2014
]]

class("SqliteLua", {
		openSqlite = function(...)
			return SqliteDb:openSqlite(...)
		end
	})

