--[[
	Description: menu layer controller
	Author: M.Wan
	Date: 07/04/2014
]]

class("MenuLayerController", psViewController)

MenuLayerController.resources = {
}

function MenuLayerController:load()
	log("MenuLayerController:load")
	self:loadResources()
	self:addObservers()
	self:renderView()
end

function MenuLayerController:unload()
	log("MenuLayerController:unload")
	self:cleanResources()
	self:removeObservers()
end

function MenuLayerController:loadResources()
	log("MenuLayerController:loadResources")
	LoadSpriteFrames(self.resources)
end

function MenuLayerController:cleanResources()
	RemoveSpriteFrames(self.resources)
end

function MenuLayerController:addObservers()
	log("MenuLayerController:addObservers")
end

function MenuLayerController:removeObservers()
	log("MenuLayerController:removeObservers")
end

function MenuLayerController:renderView()
	
end