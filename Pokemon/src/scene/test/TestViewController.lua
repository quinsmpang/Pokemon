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

	local bg = cc.Sprite:createWithSpriteFrameName("images/item/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)

	local dots = {}
	local r = math.sqrt(400 * 400 + 240 * 240)
	for i = 0, 360 do
		local pt = ccp(r * math.cos(math.rad(i)), r * math.sin(math.rad(i)))
		table.insert(dots, pt)
	end
	local stencil = cc.DrawNode:create()
	stencil:drawPolygon(dots, 360, ccc4f(1, 1, 1, 1), 50, ccc4f(1, 1, 1, 1))
	stencil:setAnchorPoint(0.5, 0.5)
	stencil:setPosition(winSize.width * 0.5, winSize.height * 0.5)

	local clipper = cc.ClippingNode:create(stencil)
	clipper:setAnchorPoint(0, 0)
	clipper:setPosition(0, 0)
	clipper:addChild(bg)
	clipper:setInverted(false)
	-- clipper:setAlphaThreshold(0)
	coreLayer:addChild(clipper)

	stencil:runAction(cc.ScaleTo:create(10, 0))

	-- stencil:setBlendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_DST_ALPHA)

	-- local renderer = cc.RenderTexture:create(winSize.width, winSize.height, cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
	-- renderer:setAnchorPoint(0.5, 0.5)
	-- renderer:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	-- coreLayer:addChild(renderer)

	-- renderer:begin()
	-- stencil:visit()
	-- renderer:endToLua()
end