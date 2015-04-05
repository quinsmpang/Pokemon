--[[
	Description: Battle public data
	Author: M.Wan
	Date: 4/4/2015
]]

BattleSharedData = {}

BattleSharedData.battleType = nil		-- 战斗类型

BattleSharedData.enemyAI = nil		-- 敌人ai

BattleSharedData.playerLastSkillCriticalCorrection = nil	-- 玩家上个技能会心修正
BattleSharedData.playerLastSkillPropertyCorrection = nil	-- 玩家上个技能属性修正
BattleSharedData.enemyLastSkillCriticalCorrection = nil		-- 敌人上个技能会心修正
BattleSharedData.enemyLastSkillPropertyCorrection = nil		-- 敌人上个技能属性修正

BattleSharedData.weather = nil		-- 天气
BattleSharedData.specialEnvironments = {}	-- 特殊特性环境(天气锁、压迫等等)

BattleSharedData.currentPokemonModel = nil	-- 当前使用精灵的model
BattleSharedData.enemyPokemonModel = nil	-- 敌人精灵的model

-- 等级都是-6 ~ 6
BattleSharedData.playerPokemonPhyAtkLevel = 0		-- 物攻等级
BattleSharedData.playerPokemonPhyDefLevel = 0		-- 物防等级
BattleSharedData.playerPokemonSpeAtkLevel = 0		-- 特攻等级
BattleSharedData.playerPokemonSpeDefLevel = 0		-- 特防等级
BattleSharedData.playerPokemonSpeedLevel = 0		-- 速度等级
BattleSharedData.playerPokemonHitRateLevel = 0		-- 命中率等级
BattleSharedData.playerPokemonAvoidanceLevel = 0	-- 回避率等级

BattleSharedData.enemyPokemonPhyAtkLevel = 0		-- 物攻等级
BattleSharedData.enemyPokemonPhyDefLevel = 0		-- 物防等级
BattleSharedData.enemyPokemonSpeAtkLevel = 0		-- 特攻等级
BattleSharedData.enemyPokemonSpeDefLevel = 0		-- 特防等级
BattleSharedData.enemyPokemonSpeedLevel = 0			-- 速度等级
BattleSharedData.enemyPokemonHitRateLevel = 0		-- 命中率等级
BattleSharedData.enemyPokemonAvoidanceLevel = 0		-- 回避率等级

BattleSharedData.playerPokemonCriticalLevel = 0		-- 战斗中额外会心率等级
BattleSharedData.enemyPokemonCriticalLevel = 0		-- 战斗中额外会心率等级

BattleSharedData.forbiddenPlayerPokemonIndex = nil		-- 玩家精灵被封的技能索引
BattleSharedData.forbiddenEnemyPokemonIndex = nil		-- 敌人精灵被封的技能索引