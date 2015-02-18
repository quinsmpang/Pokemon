--[[
	Description: Test parabola.
	Author: M.Wan
	Date: 02/18/2015
]]

class("TestParabolaLayer", psLayer)

TestParabolaLayer.__create = psLayer.create

function TestParabolaLayer:create()
	local layer = TestParabolaLayer:__create()
	layer:init()
	return layer
end

function TestParabolaLayer:init()
	local winSize = cc.Director:getInstance():getWinSize()

	local a = -0.015
	local h = 400
	local k = 420
	local x1 = 250
	local x2 = 550

	local dots = {}
	-- y = -2 * (x - 400) ^ 2 + 300
	for i = x1, x2 do
		local pt = ccp(i, a * (i - h) ^ 2 + k)
		table.insert(dots, pt)
	end
	local parabola = cc.DrawNode:create()
	parabola:drawPolygon(dots, x2 - x1 + 1, ccc4f(1, 1, 1, 0), 2, ccc4f(1, 1, 1, 1))
	parabola:setAnchorPoint(0.5, 0.5)
	-- parabola:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self:addChild(parabola)

	local sp = cc.Sprite:createWithSpriteFrameName("images/common/ball_owning.png")
	self:addChild(sp)
	local actionParabola = ActionParabola:create(2, a, h, k, x1, x2)
	sp:runAction(cc.RepeatForever:create(cc.Sequence:create(actionParabola, actionParabola:reverse())))
end