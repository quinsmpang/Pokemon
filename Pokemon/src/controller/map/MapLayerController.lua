--[[
	Description: map layer controller
	Author: M.Wan
	Date: 05/29/2014
]]

class("MapLayerController", psViewController)

require "src/view/map/TMXMapLayer"

MapLayerController.currentMap = nil		-- 当前地图层
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

	local playerData = DataCenter.currentPlayerData
	local mapInfo = MapInfo:create(playerData.currentMapId)

	local map = TMXMapLayer:createWithMapInfo(mapInfo)

	coreLayer:pushLayer(map)
end

function MapLayerController:switchMap(mapInfo)
	
end