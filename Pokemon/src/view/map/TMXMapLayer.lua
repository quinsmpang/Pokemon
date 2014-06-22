--[[
	Description: map layer, to load tmx map file
	Author: M.Wan
	Date: 05/29/2014
]]

class("TMXMapLayer", psGameLayer)

TMXMapLayer.mapInfo = nil 		-- MapInfo model
TMXMapLayer.playerLayer = nil	-- player layer
TMXMapLayer.npcLayer = nil		-- npc layer
TMXMapLayer.main = nil			-- main layer

TMXMapLayer.ZORDER = {
	MAIN = 0,
	PLAYER = 2,
	HIGH_ITEMS = 4,
}

-- treat as static method
function TMXMapLayer:createWithMapInfo(mapInfo, heroPos)
	local mapLayer = TMXMapLayer:createWithTransitions(
		cc.FadeIn:create(0.5),
		cc.FadeIn:create(0.5),
		cc.FadeOut:create(0.5),
		cc.FadeOut:create(0.5),
		)

	mapLayer:initWithMapInfo(mapInfo, heroPos)

	return mapLayer
end

function TMXMapLayer:initWithMapInfo(mapInfo, heroPos, heroDirection)
	self.mapInfo = mapInfo

	local screenSize = cc.Director:getInstance():getWinSize()

	local map = EncryptedTMXTiledMap:create(mapInfo.path)
	map:setAnchorPoint(0.5, 0.5)
	map:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

	-- main layer must be exist
	self.main = map:getLayer("main")

	self.playerLayer = cc.Layer:create()
	self:addChild(self.playerLayer)
	self.npcLayer = cc.Layer:create()
	self:addChild(self.npcLayer)

	-- 如果没有hero position的信息，则显示在地图的默认位置
	if not heroPos then
		local heroObj = map:getObjectGroup("heroObjects"):getObject("hero")
		local heroFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. heroObj["direction"] .. "1.png"
		local hero = cc.Sprite:createWithSpriteFrameName(heroFrameName)
		local pos = self.main:convertToWorldSpace(ccp(tonumber(heroObj["x"]), tonumber(heroObj["y"])))
		hero:setAnchorPoint(0, 0)
		hero:setPosition(pos)
		self.playerLayer:addChild(hero)
	else
		local heroFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. heroDirection .. "1.png"
		local hero = cc.Sprite:createWithSpriteFrameName(heroFrameName)
		hero:setAnchorPoint(0, 0)
		hero:setPosition(heroPos)
		self.playerLayer:addChild(hero)
	end

	-- 判断地图是否拥有npc
	local npcObjectGroup = map:getObjectGroup("npcObjects")
	if npcObjectGroup then
		-- 遍历生成npc
		local npcObjects = npcObjectGroup:getObjects()
		for _, npcObj in ipairs(npcObjects) do
			local npcFrameName = "images/characters/" .. npcObj["npc_name"] .. "_" .. npcObj["direction"] .. "1.png"
			local npc = cc.Sprite:createWithSpriteFrameName(npcFrameName)
			local npcPos = self.main:convertToWorldSpace(ccp(tonumber(npcObj["x"]), tonumber(npcObj["y"])))
			npc:setAnchorPoint(0, 0)
			npc:setPosition(npcPos)
			self.npcLayer:addChild(npc)
		end
	end

	-- 设置障碍物
end