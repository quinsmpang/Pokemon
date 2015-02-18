--[[
	Description: Test view controller
	Author: M.Wan
	Date: 01/03/2015
]]

class("TestViewController", psViewController)

require "src/scene/test/TestClippingCircleLayer"
require "src/scene/test/TestParabolaLayer"
require "src/scene/test/TestBlendLayer"

TestViewController.resources = {
	"images/item.plist",
	"images/item.pvr.ccz",
}

function TestViewController:load()
	self:loadResources()
	self:renderView()
end

function TestViewController:unload()
	self:cleanResources()
end

function TestViewController:loadResources()
	LoadSpriteFrames(self.resources)
end

function TestViewController:cleanResources()
	RemoveSpriteFrames(self.resources)
end

function TestViewController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	-- local testLayer = TestClippingCircleLayer:create()
	-- local testLayer = TestParabolaLayer:create()
	local testLayer = TestBlendLayer:create()
	coreLayer:addChild(testLayer)
end