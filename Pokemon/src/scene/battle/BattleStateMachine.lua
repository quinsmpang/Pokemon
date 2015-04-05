--[[
	Description: battle state.
	Author: M.Wan
	Date: 1/17/2015
]]

BattleStateMachine = {}

BattleStateMachine.lastState = nil	-- 上个状态
BattleStateMachine.state = nil		-- 当前状态
BattleStateMachine.battleType = nil		-- 战斗类型

BattleStateMachine.friendBehavior = nil
BattleStateMachine.enemyBehavior = nil

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

function BattleStateMachine:hack_generate_behaviors(behaviorType, param)
	-- 生成战斗行为
	local friendBehavior, enemyBehavior
	local behaviorMap = { "AttackBehavior", "UseItemBehavior", "ChangePokemonBehavior", "EscapeBehavior" }
	friendBehavior = _G[behaviorMap[behaviorType]]:create(param, true)
	enemyBehavior = BattleSharedData.enemyAI:generateBehavior()
	self.friendBehavior = friendBehavior
	self.enemyBehavior = enemyBehavior

	if friendBehavior.priority >= enemyBehavior.priority then
		self:setState(BattleLogicConstants.BATTLE_STATE.PLAYER_TURN)
	else
		self:setState(BattleLogicConstants.BATTLE_STATE.ENEMY_TURN)
	end
	self:process()
end

function BattleStateMachine:hack_player_turn()
	assert(self.friendBehavior, "Invalid player behavior.")
	self.friendBehavior:process()
	self.friendBehavior = nil
end

function BattleStateMachine:hack_enemy_turn()
	assert(self.enemyBehavior, "Invalid enemy behavior.")
	self.enemyBehavior:process()
	self.enemyBehavior = nil
end

function BattleStateMachine:hack_escape()
	-- 逃跑状态仅用于判断
	assert(false, "NO ESCAPE HACK.")
end