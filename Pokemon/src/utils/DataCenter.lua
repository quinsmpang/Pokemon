--[[
	Description: public data
	Author: M.Wan
	Date: 06/23/2014
]]

DataCenter = {}

DataCenter.currentPlayerData = nil		-- 当前玩家数据(PlayerData)
DataCenter.carriedPokemons = nil	-- 当前携带的宠物({Pokemon})
DataCenter.currentBagData = nil		-- 当前背包数据({subtype1={{itemId,count},...},...})
DataCenter.money = nil				-- 零用钱
DataCenter.computerData = nil	-- 电脑宠物布局信息(ComputerData)
DataCenter.currentComputerChannel = nil		-- 当前电脑频道(每个频道可以放30个精灵)
DataCenter.collectionData = nil		-- 图鉴信息({[id]=true/false})
DataCenter.bonusCollection = nil	-- 获取过的地图道具
DataCenter.battleRecords = nil		-- 发生过的地图战斗记录
DataCenter.badges = nil				-- 徽章
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
	if self.collectionData[pokemonId] == nil then
		self.collectionData[pokemonId] = catched
	end
end

function DataCenter:addNewItem(itemId, count)
	log("DataCenter:addNewItem", itemId, count)
	if not self.currentBagData then
		self.currentBagData = {}
	end
	local subType = math.floor(itemId / 1000)
	if not self.currentBagData[subType] then
		self.currentBagData[subType] = {}
	end
	if not table.contains(self.currentBagData[subType], function(v, itemId) return v[1] == tonumber(itemId) end, itemId) then
		table.insert(self.currentBagData[subType], { tonumber(itemId), count })
	else
		local target = table.find(self.currentBagData[subType], function(v, itemId) return v[1] == tonumber(itemId) end, itemId)
		target[2] = target[2] + count
	end
end

-- 获取图鉴发现数
function DataCenter:getDiscoverCount()
	if not self.collectionData then
		return 0
	end
	return table.getTotalCount(self.collectionData)
end

-- 获取图鉴捕获数
function DataCenter:getCaptureCount()
	if not self.collectionData then
		return 0
	end
	local count = 0
	for k, v in pairs(self.collectionData) do
		if v then
			count = count + 1
		end
	end
	return count
end

-- 添加零花钱
function DataCenter:addMoney(money)
	if not self.money then
		self.money = 0
	end
	self.money = self.money + money
end