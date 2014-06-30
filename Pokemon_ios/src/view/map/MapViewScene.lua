--[[
	Description: map scene
	Author: M.Wan
	Date: 05/18/2014
]]

require "src/controller/map/MapLayerController"
require "src/controller/map/DialogLayerController"

class("MapViewScene", psGameScene)

MapViewScene.resources = {
	"images/map.plist",
	"images/map.pvr.ccz",
}

function MapViewScene:onEnter()
	log("MapViewScene:onEnter")
end

function MapViewScene:onEnterTransitionDidFinish()
	log("MapViewScene:onEnterTransitionDidFinish")
	self:loadResources()
	self:init()
end

function MapViewScene:onExit()
	log("MapViewScene:onExit")
	self:cleanResources()
end

function MapViewScene:loadResources()
	LoadSpriteFrames(self.resources)
end

function MapViewScene:cleanResources()
	RemoveSpriteFrames(self.resources)
end

function MapViewScene:init()
	local coreLayer = CoreLayer:create()
	self:setCoreLayer(coreLayer)

	GameDBHelper:openDB()
	
	local mapLayerController = MapLayerController:create()
	self:loadViewController(mapLayerController)
	local dialogLayerController = DialogLayerController:create()
	self:loadViewController(dialogLayerController)	
end

function MapViewScene:newData(gender)
	local newPlayer = PlayerData:create(gender)
	DataCenter.currentPlayerData = newPlayer
end

function MapViewScene:loadData(data)
end