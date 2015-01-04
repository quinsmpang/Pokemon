--[[
	Description: Test view controller
	Author: M.Wan
	Date: 01/03/2015
]]

class("TestViewController", psViewController)

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

	local winSize = cc.Director:getInstance():getWinSize()

	local testLayer = cc.Layer:create()
	coreLayer:addChild(testLayer)

	local bg = cc.Sprite:createWithSpriteFrameName("images/item/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	testLayer:addChild(bg)

	local clipper = cc.ClippingNode:create()
	clipper:setContentSize(winSize)
	clipper:setPosition(0, 0)
	clipper:setAnchorPoint(0, 0)
	-- clipper:setAlphaThreshold(0)

	local blackLayer = cc.LayerColor:create(ccc4(0, 0, 0, 1))
	blackLayer:setPosition(0, 0)
	clipper:addChild(blackLayer)

	local dots = {}
	local r = 100
	for i = 0, 360 do
		local pt = ccp(r * math.cos(math.rad(i)), r * math.sin(math.rad(i)))
		table.insert(dots, pt)
	end
	local stencil = cc.DrawNode:create()
	stencil:drawPolygon(dots, 360, ccc4f(1, 1, 1, 1), 1, ccc4f(1, 1, 1, 1))
	stencil:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	clipper:setStencil(stencil)
	clipper:setInverted(true)

	-- testLayer:addChild(stencil)

	testLayer:addChild(clipper)
end