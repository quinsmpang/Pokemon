--[[
	Description: map scene
	Author: M.Wan
	Date: 05/18/2014
]]

require "src/controller/map/MapLayerController"
require "src/controller/map/DialogLayerController"

class("MapViewScene", psGameScene)

function MapViewScene:onEnter()
	log("MapViewScene:onEnter")
end

function MapViewScene:onEnterTransitionDidFinish()
	log("MapViewScene:onEnterTransitionDidFinish")
	self:init()
end

function MapViewScene:onExit()
	log("MapViewScene:onExit")
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