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

function BattleStateMachine:reset()
	self.state = BattleLogicConstants.BATTLE_STATE.BATTLE_START
end

-- 该函数只处理 "prepare" 和 "ending" 以外的战斗状态
function BattleStateMachine:process()
	local handler = "hack_" .. self.state
end