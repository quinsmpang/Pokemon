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

function MapViewController:loadResources()
	log("MapViewController:loadResources")
	cc.SpriteFrameCache:getInstance():addSpriteFrames("images/map/map.plist", "images/map/map.pvr.ccz")
end

function MapViewController:cleanResources()
	log("MapViewController:cleanResources")
	cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile("images/map/map.plist")
end

function MapViewController:renderView()
	local screenSize = cc.Director:getInstance():getWinSize()
	
	local tiledMap = cc.TMXTiledMap:create("maps/test.tmx")
	tiledMap:setAnchorPoint(0.5, 0.5)
	tiledMap:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

	local coreLayer = psCoreLayer:create()
	self:getScene():setCoreLayer(coreLayer)

	coreLayer:addChild(tiledMap)
end