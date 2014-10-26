--[[
	Description: Pokemon model (used in game)
	Author: M.Wan
	Date: 07/31/2014
]]

luaClass("BasicData")

BasicData.hp = nil					-- HP
BasicData.physicalAttack = nil		-- 物攻
BasicData.physicalDefense = nil		-- 物防
BasicData.specialAttack = nil		-- 特攻
BasicData.specialDefense = nil		-- 特防
BasicData.agility = nil				-- 敏捷

function BasicData:init()
	self.hp = 0
	self.physicalAttack = 0
	self.physicalDefense = 0
	self.specialAttack = 0
	self.specialDefense = 0
	self.agility = 0
end

---------------------------------------------------------------------------

luaClass("Pokemon", psModel)

Pokemon.id = DBNULL		-- id
Pokemon.level = DBNULL		-- 等级
Pokemon.basicData = DBNULL	-- 基础数据
Pokemon.skills = DBNULL	-- 技能
Pokemon.speciality = DBNULL	-- 特性
Pokemon.hardValues = DBNULL	-- 努力值
Pokemon.entityValues = DBNULL	-- 个体值
Pokemon.isShining = DBNULL	-- 是否是闪光
Pokemon.exp = DBNULL	-- 当前经验值
Pokemon.maxExp = DBNULL	-- 下级所需经验值
Pokemon.personality = DBNULL	-- 性格
Pokemon.gender = DBNULL		-- 性别
Pokemon.currentHp = DBNULL	-- 当前hp
Pokemon.status = DBNULL	-- 状态
Pokemon.ballId = DBNULL	-- 精灵球

Pokemon.model = DBNULL

function Pokemon:create(id, level, ballId)
	local pokemon = Pokemon:new()
	pokemon:initRandom(id, level, ballId)
	return pokemon
end

function Pokemon:initRandom(id, level, ballId)
	ballId = ballId or 1
	self.model = PetInfo:create(id)

	self.id = id
	self.level = level
	self.speciality = self.model:generateRandomSpeciality()
	self.hardValues = { 0, 0, 0, 0, 0, 0 }
	self.personality = math.random(0, 24)
	self.gender = math.random(0, 1)
	self.status = Enumerations.POKEMON_STATUS.NORMAL
	self.isShining = FallInRandom(1, 65536)
	self.ballId = ballId

	self:initRandomValues()
	self:initSkills()
	self:recalculateBasicData()
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

function Pokemon:recalculateBasicData()
	if self.basicData == DBNULL then
		self.basicData = BasicData:new()
	end

	local racialValues = self.model.racial
	local personalityConst = self:getPersonalityConst()

	self.basicData.hp = math.floor((racialValues[1] * 2 + self.entityValues[1] + self.hardValues[1] * 0.25) * self.level * 0.01 + self.level + 10)
	self.basicData.physicalAttack = math.floor(((racialValues[2] * 2 + self.entityValues[2] + self.hardValues[2] * 0.25) * self.level * 0.01 + 5) * personalityConst[1])
	self.basicData.physicalDefense = math.floor(((racialValues[3] * 2 + self.entityValues[3] + self.hardValues[3] * 0.25) * self.level * 0.01 + 5) * personalityConst[2])
	self.basicData.specialAttack = math.floor(((racialValues[4] * 2 + self.entityValues[4] + self.hardValues[4] * 0.25) * self.level * 0.01 + 5) * personalityConst[3])
	self.basicData.specialDefense = math.floor(((racialValues[5] * 2 + self.entityValues[5] + self.hardValues[5] * 0.25) * self.level * 0.01 + 5) * personalityConst[4])
	self.basicData.agility = math.floor(((racialValues[6] * 2 + self.entityValues[6] + self.hardValues[6] * 0.25) * self.level * 0.01 + 5) * personalityConst[5])

	-- hp默认满血
	self.currentHp = self.basicData.hp
end

function Pokemon:initSkills()
	
end

function Pokemon:getPersonalityConst()
	local const = { 1, 1, 1, 1, 1 }

	if self.personality >= Enumerations.POKEMON_PERSONALITY.HARDY and self.personality <= Enumerations.POKEMON_PERSONALITY.QUIRKY then
		return const
	end

	local tmp = self.personality - 5
	local addIndex = math.floor(tmp / 4) + 1
	local minusIndex = tmp % 4 + 1 >= addIndex and tmp % 4 + 2 or tmp % 4 + 1
	const[addIndex] = 1.1
	const[minusIndex] = 0.9

	return const
end