--[[
	Description: NPC info (from map)
	Author: M.Wan
	Date: 06/24/2014
]]

luaClass("NPC", psModel)

NPC.id = DBNULL
NPC.position = DBNULL			-- npc位置
NPC.direction = DBNULL			-- npc方向
NPC.npcId = DBNULL				-- 对应的npc model id
NPC.responseId = DBNULL			-- 响应的id
NPC.step = DBNULL				-- 对应的剧情step

NPC.npcDbModel = DBNULL			-- 对应id的npc model

function NPC:create(npcInfo)
	if type(npcInfo) ~= "table" then
		return nil
	end

	local model = NPC:new()
	model:initWithInfo(npcInfo)

	return model
end

function NPC:initWithInfo(npcInfo)
	self.id = tonumber(npcInfo["id"])
	self.position = ccp(tonumber(npcInfo["x"]) / 32, tonumber(npcInfo["y"]) / 32)
	self.direction = tonumber(npcInfo["direction"])
	self.npcId = tonumber(npcInfo["npcId"])
	self.responseId = tonumber(npcInfo["responseId"])
	self.step = tonumber(npcInfo["step"])

	self.npcDbModel = NpcInfo:create(self.npcId)
end

function NPC:getDirectionString()
	if self.direction == Enumerations.DIRECTIONS.UP then
		return "up"
	elseif self.direction == Enumerations.DIRECTIONS.DOWN then
		return "down"
	elseif self.direction == Enumerations.DIRECTIONS.LEFT then
		return "left"
	elseif self.direction == Enumerations.DIRECTIONS.RIGHT then
		return "right"
	end

	assert(false, "Invalid npc direction")
end

function NPC:getSpriteName()
	return self.npcDbModel.frameName
end