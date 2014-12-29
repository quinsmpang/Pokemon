--[[
	Description: Encounter info (from map)
	Author: M.Wan
	Date: 12/30/2014
]]

luaClass("Encounter", psModel)

Encounter.position = DBNULL
Encounter.width = DBNULL
Encounter.height = DBNULL
Encounter.bgType = DBNULL		-- 战斗背景类型
Encounter.fieldType = DBNULL	-- 战斗区域类型
Encounter.pets = DBNULL			-- 遭遇精灵信息

function Encounter:create(encounterInfo)
	if type(encounterInfo) ~= "table" then
		return nil
	end

	local model = Encounter:new()
	model:initWithInfo(encounterInfo)

	return model
end

function Encounter:initWithInfo(encounterInfo)
	self.position = ccp(tonumber(encounterInfo["x"]) / 32, tonumber(encounterInfo["y"]) / 32)
	self.width = encounterInfo["width"] / 32
	self.height = encounterInfo["height"] / 32
	self.bgType = tonumber(encounterInfo["bg_type"])
	self.fieldType = tonumber(encounterInfo["field_type"])
	self.pets = {}
	local ary = string.split(encounterInfo["pets"], ",")
	local petInfo = nil
	for _, v in ipairs(ary) do
		petInfo = string.split(v, ":")
		self.pets[tonumber(petInfo[1])] = { Probability = tonumber(petInfo[2]), LowLevel = tonumber(petInfo[3]), HighLevel = tonumber(petInfo[4]) }
	end
end