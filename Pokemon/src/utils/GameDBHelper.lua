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

------------------------ pet_info ------------------------
function GameDBHelper:queryPetById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.PET_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end

------------------------ event_info ------------------------j
function GameDBHelper:queryEventById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.EVENT_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end

------------------------ skill_info ------------------------j
function GameDBHelper:querySkillById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.SKILL_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end

------------------------ speciality_info ------------------------j
function GameDBHelper:querySpecialityById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.SPECIALITY_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end

------------------------ item_info ------------------------j
function GameDBHelper:queryItemById(id)
	local data = self.db:selectTableByConditionWithOneValue(GameConfig.ITEM_TABLE, "id", tostring(id))

	if data then
		return data[1]
	end
	return nil
end