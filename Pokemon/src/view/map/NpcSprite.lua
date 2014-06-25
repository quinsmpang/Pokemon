--[[
	Description: NPC Sprite
	Author: M.Wan
	Date: 06/25/2014
]]

class("NpcSprite", psSprite)

NpcSprite.id = nil
NpcSprite.model = nil

function NpcSprite:createWithModel(npcModel)
	local npcFrameName = "images/characters/" .. npcModel:getSpriteName() .. "_" .. npcModel:getDirectionString() .. "1.png"
	local npc = NpcSprite:createWithSpriteFrameName(npcFrameName)
	npc.model = npcModel
	return npc
end