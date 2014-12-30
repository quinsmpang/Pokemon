--[[
	Description: battle scene
	Author: M.Wan
	Date: 12/31/2014
]]

class("BattleScene", psGameScene)

BattleScene.resources = {
	"images/battle.plist",
	"images/battle.pvr.ccz",
}

function BattleScene:onEnter()
	log("BattleScene:onEnter")
end

function BattleScene:onEnterTransitionDidFinish()
	log("BattleScene:onEnterTransitionDidFinish")
	self:loadResources()
	self:renderView()
end

function BattleScene:onExit()
	log("BattleScene:onExit")
	self:cleanResources()
end

function BattleScene:loadResources()
	LoadSpriteFrames(self.resources)
end

function BattleScene:cleanResources()
	RemoveSpriteFrames(self.resources)
end

function BattleScene:renderView()

end