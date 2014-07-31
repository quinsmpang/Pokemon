--[[
	Description: Pokemon model (used in game)
	Author: M.Wan
	Date: 07/31/2014
]]

luaClass("Pokemon", psModel)

Pokemon.id = DBNULL		-- id
Pokemon.level = DBNULL		-- 等级
Pokemon.hp = DBNULL
Pokemon.physicalAttack = DBNULL	-- 攻击
Pokemon.physicalDefense = DBNULL	-- 物防
Pokemon.specialAttack = DBNULL	-- 特攻
Pokemon.specialDefense = DBNULL	-- 特防
Pokemon.speed = DBNULL	-- 速度
Pokemon.skills = DBNULL	-- 技能
Pokemon.speciality = DBNULL	-- 特性
Pokemon.hardValues = DBNULL	-- 努力值
Pokemon.entityValues = DBNULL	-- 个体值
Pokemon.isShining = DBNULL	-- 是否是闪光

Pokemon.model = DBNULL

function Pokemon:create(id, level)
	local pokemon = Pokemon:new()
	pokemon:initRandom(id, level)
	return pokemon
end

function Pokemon:initRandom(id, level)
	self.id = id
	self.level = level
	self.model = GameDBHelper:queryPetById(id)
	self.speciality = self.model:generateRandomSpeciality()
	self.hardValues = { 0, 0, 0, 0, 0, 0 }
	self.isShining = FallInRandom(1, 65536)

	self:initRandomValues()
	self:initSkills()
end

function Pokemon:initRandomValues()
	-- 个体值随机
	self.entityValues = {}
	local rdNum = nil
	for i = 1, 6 do
		rdNum = math.random(0, 31)
		table.insert(self.entityValues, rdNum)
	end
end

function Pokemon:initSkills()
	
end