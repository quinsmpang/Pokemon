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

	local coreLayer = CoreLayer:create()
	self:setCoreLayer(coreLayer)

	local mapLayerController = MapLayerController:create()
	self:loadViewController(mapLayerController)
	local dialogLayerController = DialogLayerController:create()
	self:loadViewController(dialogLayerController)
end

function MapViewScene:onExit()
	log("MapViewScene:onExit")
end