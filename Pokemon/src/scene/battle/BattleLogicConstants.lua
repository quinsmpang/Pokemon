--[[
	Description: battle logic constants.
	Author: M.Wan
	Date: 1/17/2015
]]

BattleLogicConstants = {}

BattleLogicConstants.BATTLE_STATE = {
	PREPARE = "prepare",		-- 战斗前准备
	BATTLE_START = "battle_start",	-- 战斗开始
	GENERATE_BEHAVIORS = "generate_behaviors",	-- 生成敌我的战斗行为
	PLAYER_TURN = "player_turn",		-- 玩家回合开始结算(逃跑不会走入此流程)
	ENEMY_TURN = "enemy_turn",		-- 敌人回合开始结算
	PLAYER_ATTACK = "player_attack",	-- 玩家回合攻击
	ENEMY_ATTACK = "enemy_attack",	-- 敌人回合攻击
	ESCAPE = "escape",		-- 逃跑
}

-- 会心一击等级对应概率，分母  实际概率是1/分母
BattleLogicConstants.CRITICAL_RATE = {
	[1] = 16,
	[2] = 8,
	[3] = 4,
	[4] = 2,
}