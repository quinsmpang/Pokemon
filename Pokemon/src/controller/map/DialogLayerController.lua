--[[
	Description: dialogue layer controller
	Author: M.Wan
	Date: 06/07/2014
]]

class("DialogLayerController", psViewController)

function DialogLayerController:load()
	log("DialogLayerController:load")
	self:loadResources()
	self:renderView()
end

function DialogLayerController:unload()
	log("DialogLayerController:unload")
	self:cleanResources()
end

function DialogLayerController:loadResources()
	log("DialogLayerController:loadResources")
	cc.SpriteFrameCache:getInstance():addSpriteFrames("images/common.plist", "images/common.pvr.ccz")
end

function DialogLayerController:cleanResources()
	log("DialogLayerController:cleanResources")
	cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile("images/common.plist")
end

function DialogLayerController:renderView()
	
end