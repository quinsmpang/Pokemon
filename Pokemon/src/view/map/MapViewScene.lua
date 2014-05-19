--[[
	Description: map scene
	Author: M.Wan
	Date: 05/18/2014
]]

require "src/controller/map/MapViewController"

class("MapViewScene", psGameScene)

function MapViewScene:onEnter()
	log("MapViewScene:onEnter")
	local mapViewController = MapViewController:create()
	self:loadViewController(mapViewController)
end

function MapViewScene:onExit()
	log("MapViewScene:onExit")
end