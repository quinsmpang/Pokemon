--[[
	Description: map layer, to load tmx map file
	Author: M.Wan
	Date: 05/29/2014
]]

class("TMXMapLayer", psGameLayer)

require "src/view/map/HeroSprite"
require "src/view/map/NpcSprite"

TMXMapLayer.mapInfo = nil 		-- MapInfo model

-- ui
TMXMapLayer.playerLayer = nil	-- player layer
TMXMapLayer.npcLayer = nil		-- npc layer
TMXMapLayer.main = nil			-- main layer
TMXMapLayer.tops = nil			-- layer whose items can cover the player
TMXMapLayer.hero = nil 			-- 玩家精灵
TMXMapLayer.npcList = nil 		-- NPC sprite集合

-- logic
TMXMapLayer.obstacleList = nil		-- 障碍物(Obstacle model)集合
TMXMapLayer.entranceList = nil		-- 入口出口(Entrance model)集合

-- const
TMXMapLayer.TILE_SIZE = 32
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
		cc.FadeOut:create(0.5)
		)

	mapLayer:initWithMapInfo(mapInfo, heroPos)

	return mapLayer
end

function TMXMapLayer:initWithMapInfo(mapInfo)
	self.mapInfo = mapInfo

	local screenSize = cc.Director:getInstance():getWinSize()

	local map = EncryptedTMXTiledMap:create(mapInfo.path)
	map:setAnchorPoint(0.5, 0.5)
	map:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	self:addChild(map, self.ZORDER.MAIN)

	-- main layer must be exist
	self.main = map:getLayer("main")
	self.main:setLocalZOrder(self.ZORDER.MAIN)
	-- top items layer
	self.tops = map:getLayer("tops")
	if self.tops then
		self.tops:setLocalZOrder(self.ZORDER.HIGH_ITEMS)
	end

	self.playerLayer = cc.Layer:create()
	map:addChild(self.playerLayer, self.ZORDER.PLAYER)
	self.npcLayer = cc.Layer:create()
	map:addChild(self.npcLayer, self.ZORDER.PLAYER)

	-- 如果当前是非活动状态，说明是剧情载入，则显示在剧情设定位置
	log("Map Initialization: Loading hero")
	DataCenter.currentPlayerData.currentMapId = mapInfo.id
	if DataCenter.currentPlayerData.currentStep ~= 0 then
		local heroObjectGroup = map:getObjectGroup("heroObjects")
		local heroObjects = heroObjectGroup:getObjects()
		for _, heroObj in ipairs(heroObjects) do
			if tonumber(heroObj["step"]) == DataCenter.currentPlayerData.currentStep then
				DataCenter.currentPlayerData.direction = tonumber(heroObj["direction"])
				local hero = HeroSprite:createWithModel(heroObj)
				local pos = ccp(tonumber(heroObj["x"]), tonumber(heroObj["y"]))
				DataCenter.currentPlayerData.currentPosition = ccp(tonumber(heroObj["x"]) / self.TILE_SIZE, tonumber(heroObj["y"]) / self.TILE_SIZE)
				hero:setAnchorPoint(0, 0)
				hero:setPosition(pos)
				self.playerLayer:addChild(hero)
				break
			end
		end
	else	-- 说明是读取存档载入，直接显示在存档记录的位置
		local heroFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. DataCenter.currentPlayerData:getDirectionString() .. "1.png"
		local hero = cc.Sprite:createWithSpriteFrameName(heroFrameName)
		hero:setAnchorPoint(0, 0)
		hero:setPosition(DataCenter.currentPlayerData.currentPosition.x * self.TILE_SIZE, DataCenter.currentPlayerData.currentPosition.y * self.TILE_SIZE)
		self.playerLayer:addChild(hero)
	end

	-- 判断地图是否拥有npc
	log("Map Initialization: Loading npc")
	self.npcList = {}
	local npcObjectGroup = map:getObjectGroup("npcObjects")
	if npcObjectGroup then
		-- 遍历生成npc
		local npcObjects = npcObjectGroup:getObjects()
		for _, npcObj in ipairs(npcObjects) do
			if tonumber(npcObj["step"]) == DataCenter.currentPlayerData.currentStep or tonumber(npcObj["step"]) == 0 then
				local npcModel = NPC:create(npcObj)
				local npc = NpcSprite:createWithModel(npcModel)
				local npcPos = ccp(tonumber(npcObj["x"]), tonumber(npcObj["y"]))
				npc:setAnchorPoint(0, 0)
				npc:setPosition(npcPos)
				table.insert(self.npcList, npc)
				self.npcLayer:addChild(npc)
			end
		end
	end

	-- 设置障碍物
	log("Map Initialization: Loading obstacles")
	self.obstacleList = {}
	local obstacleObejctGroup = map:getObjectGroup("obstacleObjects")
	if obstacleObejctGroup then
		-- 遍历放到障碍物table中
		local obstacleObjects = obstacleObejctGroup:getObjects()
		for _, obstacleObj in ipairs(obstacleObjects) do
			local obstacleModel = Obstacle:create(obstacleObj)
			table.insert(self.obstacleList, obstacleModel)
		end
	end

	-- 设置入口
	log("Map Initialization: Loading entrances")
	self.entranceList = {}
	local entranceObjectGroup = map:getObjectGroup("entranceObjects")
	if entranceObjectGroup then
		-- 遍历放到入口table中
		local entranceObjects = entranceObjectGroup:getObjects()
		for _, entranceObj in ipairs(entranceObjects) do
			local entranceModel = Entrance:create(entranceObj)
			table.insert(self.entranceList, entranceModel)
		end
	end
end