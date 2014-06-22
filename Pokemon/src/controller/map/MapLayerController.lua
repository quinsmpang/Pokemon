--[[
	Description: map layer controller
	Author: M.Wan
	Date: 05/29/2014
]]

class("MapLayerController", psViewController)

MapLayerController.playerLayer = nil		-- 玩家精灵所在层

MapLayerController.resources = {
	"images/characters.plist", 
	"images/characters.pvr.ccz",
}

-- const
MapLayerController.ZORDER = {
	PLAYER = 999,
}

function MapLayerController:load()
	log("MapLayerController:load")
	self:loadResources()
	self:renderView()
end

function MapLayerController:unload()
	log("MapLayerController:unload")
	self:cleanResources()
end

function MapLayerController:loadResources()
	log("MapLayerController:loadResources")
	LoadSpriteFrames(self.resources)
end

function MapLayerController:cleanResources()
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(self.resources[i])
	end
end

function MapLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	local playerData = self:getScene().currentPlayerData

	self.playerLayer = cc.Layer:create()
	coreLayer:addChild(self.playerLayer, self.ZORDER.PLAYER)

	local map = EncryptedTMXTiledMap:create("maps/champion_league1.tmx")
	map:setAnchorPoint(0.5, 0.5)
	map:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

	local main = map:getLayer("main")
	local objects = map:getObjectGroup("characters")
	local heroObj = objects:getObject("hero")

	local heroFrameName = "images/characters/player_" .. playerData:getGenderString() .. "_walk_" .. heroObj["direction"] .. "1.png"
	local hero = cc.Sprite:createWithSpriteFrameName(heroFrameName)
	local heroPos = main:convertToWorldSpace(ccp(tonumber(heroObj["x"]), tonumber(heroObj["y"])))
	hero:setAnchorPoint(0, 0)
	hero:setPosition(heroPos)
	self.playerLayer:addChild(hero)

	local championObj = objects:getObject("champion")
	local championFrameName = "images/characters/" .. championObj["npc_name"] .. "_" .. championObj["direction"] .. "1.png"
	local champion = cc.Sprite:createWithSpriteFrameName(championFrameName)
	local championPos = main:convertToWorldSpace(ccp(tonumber(championObj["x"]), tonumber(championObj["y"])))
	champion:setAnchorPoint(0, 0)
	champion:setPosition(championPos)
	self.playerLayer:addChild(champion)

	coreLayer:addChild(map)
end