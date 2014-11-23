--[[
	Description: public data
	Author: M.Wan
	Date: 06/23/2014
]]

DataCenter = {}

DataCenter.currentPlayerData = nil		-- 当前玩家数据(PlayerData)
DataCenter.carriedPokemons = nil	-- 当前携带的宠物({Pokemon})
DataCenter.currentBagData = nil		-- 当前背包数据({Item})
DataCenter.computerData = nil	-- 电脑宠物布局信息(ComputerData)
DataCenter.currentComputerChannel = nil		-- 当前电脑频道(每个频道可以放30个精灵)
DataCenter.collectionData = nil		-- 图鉴信息({[id]=true/false})
DataCenter.bonusCollection = nil	-- 获取过的地图道具
DataCenter.relatedSaveIndex = nil	-- 相关的存档位置

function DataCenter:addNewPokemon(pokemon)
	log("DataCenter:addNewPokemon")
	if not self.carriedPokemons then
		self.carriedPokemons = {}
	end
	self:addNewCollection(pokemon.id, true)
	if #self.carriedPokemons < 6 then
		table.insert(self.carriedPokemons, pokemon)
		return nil
	else
		return self:addPokemonToComputer(pokemon)
	end
end

function DataCenter:addPokemonToComputer(pokemon)
	log("DataCenter:addPokemonToComputer")
	if not self.computerData then
		self.computerData = {}
		self.computerData[1] = {}
		self.currentComputerChannel = 1
	end
	local curChannel = self.currentComputerChannel
	local existPos = false
	repeat
		if not self.computerData[curChannel] then
			self.computerData[curChannel] = {}
		end
		for i = 1, 30 do
			if not self.computerData[curChannel][i] then
				self.computerData[curChannel][i] = pokemon
				existPos = true
				break
			end
		end
		if not existPos then
			curChannel = curChannel % 30 + 1
			if curChannel == self.currentComputerChannel then
				-- 电脑没有位置了
				log("There is no position in the computer.")
				break
			end
		end
	until existPos
	return existPos
end

function DataCenter:addNewCollection(pokemonId, catched)
	assert(type(pokemonId) == "number" and pokemonId >= 1 and pokemonId <= 649, "invalide pokemon id")
	if catched == nil then
		catched = false
	end
	if not self.collectionData then
		self.collectionData = {}
	end
	self.collectionData[pokemonId] = catched
end