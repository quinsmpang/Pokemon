--[[
	Description: map layer controller
	Author: M.Wan
	Date: 05/29/2014
]]

class("MapLayerController", psViewController)

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
	cc.SpriteFrameCache:getInstance():addSpriteFrames("images/characters.plist", "images/characters.pvr.ccz")
end

function MapLayerController:cleanResources()
	cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile("images/characters.plist")
end

function MapLayerController:renderView()
	
end