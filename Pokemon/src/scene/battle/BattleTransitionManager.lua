--[[
	Description: battle transition manager
	Author: M.Wan
	Date: 01/05/2015
]]

BattleTransitionManager = {}

BattleTransitionManager.MAX_ID = 1

function BattleTransitionManager:transitionWithId(id)
	local funcName = "transition" .. id
	local func = self[funcName]
	assert(type(func) == "function", "Unimplemented transition with id " .. id)
	return func(self)
end

function BattleTransitionManager:randomTransition()
	local randomId = math.random(1, self.MAX_ID)
	return self:transitionWithId(randomId)
end

-- 固定闪烁
function BattleTransitionManager:blinkAction()
	local scene = cc.Director:getInstance():getRunningScene()

	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 0))
	mask:setCascadeOpacityEnabled(true)
	mask:setPosition(0, 0)
	scene:addChild(mask)
	local action = cc.Sequence:create(
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15))
		)
	return action
end

-- 圆形从外至内裁切
function BattleTransitionManager:transition1()
	local scene = cc.Director:getInstance():getRunningScene()
	local winSize = cc.Director:getInstance():getWinSize()

	-- circle stencil
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

	-- clipping content
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setPosition(0, 0)

	-- create clipper
	local clipper = cc.ClippingNode:create(stencil)
	clipper:setAnchorPoint(0, 0)
	clipper:setPosition(0, 0)
	clipper:addChild(mask)
	clipper:setInverted(true)
	scene:addChild(clipper)

	local blink = self:blinkAction()
	local transition = cc.TargetedAction:create(stencil, cc.ScaleTo:create(1, 0))

	return cc.Sequence:create(blink, transition)
end