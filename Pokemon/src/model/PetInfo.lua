--[[
	Description: Pet info (from DB)
	Author: M.Wan
	Date: 07/29/2014
]]

luaClass("PetInfo", psModel)

PetInfo.id = DBNULL		-- id
PetInfo.name = DBNULL	-- 名称
PetInfo.property = DBNULL	-- 属性
PetInfo.speciality = DBNULL	-- 特性
PetInfo.type = DBNULL	-- 类型
PetInfo.height = DBNULL	-- 高
PetInfo.weight = DBNULL	-- 重量
PetInfo.racial = DBNULL	-- 种族值
PetInfo.description = DBNULL	-- 宠物描述
PetInfo.hardValue = DBNULL		-- 努力值
PetInfo.evolution = DBNULL		-- 进化信息
PetInfo.levelUpSkills = DBNULL	-- 升级学习的技能 { {lv, skillId}, {lv, skillId}, ... }
PetInfo.machineSkills = DBNULL	-- 机器学习的技能 { skillId, skillId, ... }
PetInfo.heredSkills = DBNULL	-- 遗传学习的技能
PetInfo.fixedSkills = DBNULL	-- 定点学习的技能

function PetInfo:create(id)
	local model = PetInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function PetInfo:updateFromDB()
	log("PetInfo:updateFromDB")

	local data = GameDBHelper:queryPetById(self.id)
	if data then
		self:updateWithData(data)

		self.id = tonumber(data.id)
		local properties = string.split(data.property, ",")
		self.property = table.cast(properties, function(item) return tonumber(item) end)
		local specialities = string.split(data.speciality, ",")
		self.speciality = table.cast(specialities, function(item) return tonumber(item) end)
		self.height = tonumber(data.height)
		self.weight = tonumber(data.weight)
		self.racial = string.split(data.racial, ",")
		self.racial = table.cast(self.racial, function(item) return tonumber(item) end)
		local hardValues = string.split(data.hardValue, ";")
		self.hardValue = {}
		for _, v in ipairs(hardValues) do
			local pair = string.split(v, ",")
			self.hardValue[tonumber(pair[1])] = tonumber(pair[2])
		end
		self.levelUpSkills = {}
		local growSkills = string.split(data.levelUpSkills, ",")
		for _, v in ipairs(growSkills) do
			local t = string.split(v, ":")
			for i, v in ipairs(t) do
				t[i] = tonumber(v)
			end
			table.insert(self.levelUpSkills, t)
		end
		local machineSkills = string.split(data.machineSkills, ",")
		for i, v in ipairs(machineSkills) do
			machineSkills[i] = tonumber(v)
		end
		self.machineSkills = machineSkills
		-- rest todo
	else
		log("PetInfo:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end

function PetInfo:generateRandomSpeciality()
	if #self.speciality == 1 then
		return self.speciality[1]
	end

	local hiddenSpeciality = self.speciality[#self.speciality]
	if FallInRandom(1, 20) then
		return hiddenSpeciality
	else
		return self.speciality[math.random(1, #self.speciality - 1)]
	end
end