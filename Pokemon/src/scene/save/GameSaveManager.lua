--[[
	Description: Game save manager
	Author: M.Wan
	Date: 11/21/2014
]]

GameSaveManager = {}

local PREFIX = "PS1X"

function GameSaveManager:saveTo(number)
	if not IOUtils:getInstance():directoryExists("save") then
		IOUtils:getInstance():createDirectory("save")
	end
	-- serialize DataCenter
	local data = ""
	local playerDataStr = table.serialize(DataCenter.currentPlayerData.__model)
	data = data .. playerDataStr
	if DataCenter.carriedPokemons then
		data = data .. ";"
		for i, pokemon in ipairs(DataCenter.carriedPokemons) do
			local str = table.serialize(pokemon.__model)
			data = data .. str
			if i < #DataCenter.carriedPokemons then
				data = data .. "|"
			end
		end
	end

	log("save data: ", data)
	local saveData = SaveData:createWithData(data)
	saveData:setPrefix(PREFIX)
	saveData:setVersion(PSFrameworkVersionNumber)
	saveData:serializeToFile("save/ps_save" .. number .. ".sav", GameConfig.SAVE_PASSWORD)
	log("save okay")
end

function GameSaveManager:load(number)
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
		cc.Director:getInstance():replaceScene(cc.TransitionFade:create(2, mapScene))
	else
		err = true
	end
end