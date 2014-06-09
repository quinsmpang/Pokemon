--[[
	Description: Game database helper class
	Author: M.Wan
	Date: 05/30/2014
]]

GameDBHelper = {}

GameDBHelper.db = nil		-- sqlite3 db instance

function GameDBHelper:openDB()
	self.db = SqliteLua:openSqlite(GameConst.GAME_DB_PATH)
end

------------------------ dialog_info ------------------------
function GameDBHelper:queryDialogById(id)
	local data = self.db:selectTableByConditionWithOneValue("dialog_info", "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end