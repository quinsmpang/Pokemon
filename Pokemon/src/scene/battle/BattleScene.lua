--[[
	Description: battle scene
	Author: M.Wan
	Date: 12/31/2014
]]

class("BattleScene", psGameScene)

require "src/scene/battle/BattleUIController"

BattleScene.resources = {
	"images/battle_1.plist",
	"images/battle_1.pvr.ccz",
}

function BattleScene:onEnter()
	log("BattleScene:onEnter")
end

function BattleScene:onEnterTransitionDidFinish()
	log("BattleScene:onEnterTransitionDidFinish")
	self:loadResources()
	
	local battleUIController = BattleUIController:create()
	self:loadViewController(battleUIController)
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