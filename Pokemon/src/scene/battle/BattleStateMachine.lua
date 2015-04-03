--[[
	Description: battle state.
	Author: M.Wan
	Date: 1/17/2015
]]

BattleStateMachine = {}

BattleStateMachine.lastState = nil	-- 上个状态
BattleStateMachine.state = nil		-- 当前状态
BattleStateMachine.battleType = nil		-- 战斗类型

function BattleStateMachine:init(battleType)
	self.battleType = battleType
	self.state = BattleLogicConstants.BATTLE_STATE.PREPARE
end

function BattleStateMachine:setState(newState)
	if self.state == newState then
		return
	end
	self.lastState = self.state
	self.state = newState
end

-- 该函数只处理 "prepare" 和 "ending" 以外的战斗状态
function BattleStateMachine:process(...)
	local handler = "hack_" .. self.state
	self[handler](self, unpack{...})
end

function BattleStateMachine:hack_prepare()
	assert(false, "NO PREPARE HACK.")
end

function BattleStateMachine:hack_battle_start()
	-- 开始战斗
	Notifier:notify(NotifyEvents.Battle.StartBattle)
end

function BattleStateMachine:hack_escape()
	-- 逃跑
	local dialogKey = "ESCAPE_SUCCESS"
	Notifier:notify(NotifyEvents.Battle.UpdateDialog, dialogKey)
end