--[[
	Description: Battle AI.
	Author: M.Wan
	Date: 4/5/2015
]]

luaClass("BattleAI")

BattleAI.aiLevel = nil		-- AI等级
BattleAI.pokemons = nil		-- 拥有的精灵
BattleAI.items = nil		-- 拥有的道具

function BattleAI:create(aiLevel, pokemons, items)
	local ai = BattleAI:new()
	ai:init(aiLevel, pokemons, items)
	return ai
end

function BattleAI:init(aiLevel, pokemons, items)
	assert(type(aiLevel) == "number" and aiLevel >= 1 and type(pokemons) == "table" and #pokemons > 0, "Invalid params.")
	items = items or {}
	self.aiLevel = aiLevel
	self.pokemons = pokemons
	self.items = items
end

function BattleAI:generateBehavior()
	local handler = "generate_" .. self.aiLevel
	assert(self[handler], "Unimplemented AI.")
	return self[handler](self)
end

-- 野生精灵1v1最低级AI
function BattleAI:generate_1()
	local skills = BattleSharedData.enemyPokemonModel.skills
	local skill = table.random(skills, function(v)
		-- 必须有pp, 必须未被禁用的技能
		return v[2] > 0 and (BattleSharedData.forbiddenEnemyPokemonIndex == nil or skills[BattleSharedData.forbiddenEnemyPokemonIndex] ~= v)
	end)
	local skillId = 165		-- 用尽pp的默认技能
	if skill then
		skillId = skill[1]
	end
	return AttackBehavior:create(skillId, false)
end