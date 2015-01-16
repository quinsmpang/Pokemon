--[[
	Description: battle state.
	Author: M.Wan
	Date: 1/17/2015
]]

BattleStateMachine = {}

BattleStateMachine.state = nil		-- 当前状态
BattleStateMachine.battleType = nil		-- 战斗类型

function BattleStateMachine:init(battleType)
	self.battleType = battleType
	self.state = BattleLogicConstants.BATTLE_STATE.PREPARE
end

function BattleStateMachine:process()
	local handler = "hack" .. self.state
end