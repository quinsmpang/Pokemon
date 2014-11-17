--[[
	Description: Skill info (from DB)
	Author: M.Wan
	Date: 11/18/2014
]]

luaClass("SkillInfo", psModel)

-- db attributes
SkillInfo.id = DBNULL
SkillInfo.name = DBNULL
SkillInfo.property = DBNULL		-- 技能属性
SkillInfo.type = DBNULL			-- 技能类型 (物理/特殊/变化)
SkillInfo.attack = DBNULL
SkillInfo.hitRate = DBNULL
SkillInfo.pp = DBNULL
SkillInfo.target = DBNULL		-- 目标范围
SkillInfo.description = DBNULL
SkillInfo.handler = DBNULL
SkillInfo.params = DBNULL

function SkillInfo:create(id)
	local model = SkillInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function SkillInfo:updateFromDB()
	log("SkillInfo:updateFromDB")

	local data = GameDBHelper:querySkillById(self.id)
	if data then
		self:updateWithData(data)

		self.id = tonumber(data.id)
		self.property = tonumber(data.property)
		self.type = tonumber(data.type)
		self.attack = tonumber(data.attack)
		self.hitRate = tonumber(data.hitRate)
		self.pp = tonumber(data.pp)
	else
		log("SkillInfo:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end