--[[
	Description: Game database helper class
	Author: M.Wan
	Date: 05/30/2014
]]

GameDBHelper = {}

GameDBHelper.db = nil		-- sqlite3 db instance

function GameDBHelper:openDB()
	self.db = SqliteLua:openSqlite(GameConfig.GAME_DB_PATH)
end

------------------------ dialog_info ------------------------
function GameDBHelper:queryDialogById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.DIALOG_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end

------------------------ map_info ------------------------
function GameDBHelper:queryMapById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.MAP_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end

------------------------ npc_info ------------------------
function GameDBHelper:queryNpcInfoById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.NPC_TABLE, "id", tostring(id))

	if data then 
		return data[1]
	end
	return nil
end

------------------------ action_info ------------------------
function GameDBHelper:queryActionInfoById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.ACTION_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end

------------------------ response_info ------------------------
function GameDBHelper:queryResponseById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.RESPONSE_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end