--[[
	Description: map controller
	Author: M.Wan
	Date: 05/18/2014
]]

class("MapViewController", psViewController)

function MapViewController:load()
	log("MapViewController:load")
	--self:loadResources()
	self:renderView()
end

function MapViewController:unload()
	log("MapViewController:unload")
end

function MapViewController:loadResources()
	log("MapViewController:loadResources")
	cc.SpriteFrameCache:getInstance():addSpriteFrames("images/terrains/rock1.plist", "images/terrains/rock1.pvr.ccz")
end

function MapViewController:cleanResources()
	log("MapViewController:cleanResources")
	cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile("images/terrains/rock1.plist")
end

function MapViewController:renderView()
	local coreLayer = psCoreLayer:create()
	self:getScene():setCoreLayer(coreLayer)

	local screenSize = cc.Director:getInstance():getWinSize()
	
	local tiledMap = cc.TMXTiledMap:create("maps/test.tmx")
	tiledMap:setAnchorPoint(0.5, 0.5)
	tiledMap:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

	coreLayer:addChild(tiledMap)
end