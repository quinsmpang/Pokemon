--[[
	Description: map controller
	Author: M.Wan
	Date: 05/18/2014
]]

class("MapViewController", psViewController)

function MapViewController:load()
	log("MapViewController:load")
	self:renderView()
end

function MapViewController:unload()
	log("MapViewController:unload")
end

function MapViewController:renderView()
	local coreLayer = psCoreLayer:create()
	self:getScene():setCoreLayer(coreLayer)

	local screenSize = cc.Director:getInstance():getWinSize()
	
	local tiledMap = cc.TMXTiledMap:create("maps/pokemon_center.tmx")
	tiledMap:setAnchorPoint(0.5, 0.5)
	tiledMap:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

	coreLayer:addChild(tiledMap)
end