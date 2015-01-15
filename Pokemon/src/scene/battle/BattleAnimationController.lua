--[[
	Description: battle animation controller
	Author: M.Wan
	Date: 1/15/2015
]]

class("BattleAnimationController", psViewController)

BattleAnimationController.root = nil

function BattleAnimationController:load()
	log("BattleAnimationController:load")
	self:addObservers()
	self:renderView()
end

function BattleAnimationController:unload()
	log("BattleAnimationController:unload")
	self:removeObservers()
end

function BattleAnimationController:addObservers()

end

function BattleAnimationController:removeObservers()

end

function BattleAnimationController:renderView()
	local winSize = cc.Director:getInstance():getWinSize()

	self.root = cc.Layer:create()
	self:getScene():addChild(self.root)

	-- 两个遮罩
	local maskUp = cc.LayerColor:create(ccc3(0, 0, 0))
	maskUp:setPosition(0, winSize.height * 0.5)
	maskUp:setOpacity(255)
	self.root:addChild(maskUp)
	local maskDown = cc.LayerColor:create(ccc3(0, 0, 0))
	maskDown:setPosition(0, winSize.height * -0.5)
	maskDown:setOpacity(255)
	self.root:addChild(maskDown)

	local action = cc.Spawn:create(
		cc.TargetedAction:create(maskUp, cc.Sequence:create(
			cc.MoveBy:create(3, ccp(0, winSize.height * 0.5)),
			cc.RemoveSelf:create()
			)),
		cc.TargetedAction:create(maskDown, cc.Sequence:create(
			cc.MoveBy:create(3, ccp(0, -winSize.height * 0.5)),
			cc.RemoveSelf:create()
			))
		)
	self.root:runAction(action)
end