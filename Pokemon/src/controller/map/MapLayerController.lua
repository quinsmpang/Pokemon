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
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():addSpriteFrames(self.resources[i], self.resources[i + 1])
	end
end

function MapLayerController:cleanResources()
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(self.resources[i])
	end
end

function MapLayerController:renderView()
	
end