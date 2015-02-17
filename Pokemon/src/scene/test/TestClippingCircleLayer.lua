--[[
	Description: Test clip circle.
	Author: M.Wan
	Date: 01/03/2015
]]

class("TestClippingCircleLayer", psLayer)

TestClippingCircleLayer.__create = psLayer.create

function TestClippingCircleLayer:create()
	local layer = TestClippingCircleLayer:__create()
	layer:init()
	return layer
end

function TestClippingCircleLayer:init()
	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/item/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self:addChild(bg)

	local dots = {}
	local r = math.sqrt(400 * 400 + 240 * 240)
	for i = 1, 360 do
		local pt = ccp(r * math.cos(math.rad(i)), r * math.sin(math.rad(i)))
		table.insert(dots, pt)
	end
	local stencil = cc.DrawNode:create()
	stencil:drawPolygon(dots, 360, ccc4f(1, 1, 1, 1), 1, ccc4f(1, 1, 1, 1))
	stencil:setAnchorPoint(0.5, 0.5)
	stencil:setPosition(winSize.width * 0.5, winSize.height * 0.5)

	local mask = cc.LayerColor:create()
	mask:setColor(COLOR3B_BLACK)
	mask:setPosition(0, 0)
	mask:setOpacity(255)

	local clipper = cc.ClippingNode:create(stencil)
	clipper:setAnchorPoint(0, 0)
	clipper:setPosition(0, 0)
	clipper:addChild(mask)
	clipper:setInverted(true)
	-- clipper:setAlphaThreshold(0)
	self:addChild(clipper)

	stencil:runAction(cc.ScaleTo:create(3, 0))

	-- stencil:setBlendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_DST_ALPHA)

	-- local renderer = cc.RenderTexture:create(winSize.width, winSize.height, cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
	-- renderer:setAnchorPoint(0.5, 0.5)
	-- renderer:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	-- self:addChild(renderer)

	-- renderer:begin()
	-- stencil:visit()
	-- renderer:endToLua()
end