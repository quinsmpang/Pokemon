--[[
	Description: map layer controller
	Author: M.Wan
	Date: 05/29/2014
]]

class("MapLayerController", psViewController)

MapLayerController.resources = {
	"images/characters.plist", 
	"images/characters.pvr.ccz",
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

	local map = EncryptedTMXTiledMap:create("maps/champion_league1.tmx")
	map:setAnchorPoint(0.5, 0.5)
	map:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

	coreLayer:addChild(map)
end