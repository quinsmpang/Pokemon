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

	local dots = {}
	-- y = -2 * (x - 400) ^ 2 + 300
	for i = 250, 550 do
		local pt = ccp(i, -0.015 * (i - 400) ^ 2 + 420)
		table.insert(dots, pt)
	end
	local parabola = cc.DrawNode:create()
	parabola:drawPolygon(dots, 301, ccc4f(1, 1, 1, 0), 2, ccc4f(1, 1, 1, 1))
	parabola:setAnchorPoint(0.5, 0.5)
	-- parabola:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self:addChild(parabola)
end