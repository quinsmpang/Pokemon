--[[
	Description: Game save manager
	Author: M.Wan
	Date: 11/21/2014
]]

GameSaveManager = {}

local PREFIX = "PS1X"

function GameSaveManager:saveTo(number)
	log("GameSaveManager:saveTo", number)
	if not IOUtils:getInstance():directoryExists("save") then
		IOUtils:getInstance():createDirectory("save")
	end
	-- serialize DataCenter
	local data = "1;"
	-- 玩家信息
	local playerDataStr = table.serialize(DataCenter.currentPlayerData.__model)
	data = data .. playerDataStr
	-- 携带精灵信息
	if DataCenter.carriedPokemons then
		data = data .. ";2;"
		for i, pokemon in ipairs(DataCenter.carriedPokemons) do
			local str = table.serialize(pokemon.__model)
			data = data .. str
			if i < #DataCenter.carriedPokemons then
				data = data .. "|"
			end
		end
	end
	-- 图鉴信息
	if DataCenter.collectionData then
		data = data .. ";3;"
		local collectionDataStr = table.serialize(DataCenter.collectionData)
		data = data .. collectionDataStr
	end
	-- 背包信息
	if DataCenter.currentBagData then
		data = data .. ";4;"
		local bagDataStr = table.serialize(DataCenter.currentBagData)
		data = data .. bagDataStr
	end
	-- 零用钱
	if DataCenter.money then
		data = data .. ";5;" .. DataCenter.money
	end

	log("save data: ", data)
	local saveData = SaveData:createWithData(data)
	saveData:setPrefix(PREFIX)
	saveData:setVersion(PSFrameworkVersionNumber)
	saveData:serializeToFile("save/ps_save" .. number .. ".sav", GameConfig.SAVE_PASSWORD)
	log("save okay")
end

function GameSaveManager:load(number)
	log("GameSaveManager:load", number)
	if not IOUtils:getInstance():directoryExists("save") then
		IOUtils:getInstance():createDirectory("save")
	end
	-- deserialize
	local saveData = SaveData:deserializeFromFile("save/ps_save" .. number .. ".sav", GameConfig.SAVE_PASSWORD)
	local err = false
	if saveData:getPrefix() == PREFIX then
		local version = saveData:getVersion()
		log("load save version: " .. version)
		local data = saveData:getData()
		log("load data: ", data)
		data = string.split(data, ";")

		local mapScene = MapViewScene:create()
		mapScene:loadData(data)
		DataCenter.relatedSaveIndex = number
		cc.Director:getInstance():replaceScene(cc.TransitionFade:create(2, mapScene))
	else
		err = true
	end
end

function GameSaveManager:getBasicInfo(index)
	local saveData = SaveData:deserializeFromFile("save/ps_save" .. index .. ".sav", GameConfig.SAVE_PASSWORD)
	local data = string.split(saveData:getData(), ";")

	local loadData = assert(loadstring(data[2]))()
	local playerData = PlayerData:createWithLoadData(loadData)

	local mapInfo = MapInfo:create(playerData.currentMapId)
	local mapName = mapInfo.name == DBNULL and "室内" or mapInfo.name

	local index = nil
	for i = 1, #data, 2 do
		if tonumber(data[i]) == 3 then
			index = i + 1
			break
		end
	end
	local collections = 0
	if index then
		local collectionData = assert(loadstring(data[index]))()
		collections = table.getTotalCount(collectionData)
	end

	local ret = {
		MapName = mapName,
		GameTime = TimeSpan:create(playerData.gameTime):toString(),
		Collection = tostring(collections),
		Badges = tostring(0),
	}

	return ret
end