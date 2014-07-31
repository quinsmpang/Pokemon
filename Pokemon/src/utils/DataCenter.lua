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

function DataCenter:addNewPokemon(pokemon)
	if not self.carriedPokemons then
		self.carriedPokemons = {}
	end
	table.insert(self.carriedPokemons, pokemon)
end