--[[
	Description: Battle public data
	Author: M.Wan
	Date: 4/4/2015
]]

BattleSharedData = {}

BattleSharedData.battleType = nil		-- 战斗类型

BattleSharedData.enemyAI = nil		-- 敌人ai

BattleSharedData.currentPokemonModel = nil	-- 当前使用精灵的model
BattleSharedData.enemyPokemonModel = nil	-- 敌人精灵的model
BattleSharedData.currentPokemonModel2 = nil		-- 2v2 用
BattleSharedData.enemyPokemonModel2 = nil		-- 2v2 用
BattleSharedData.currentPokemonModel3 = nil		-- 3v3 用
BattleSharedData.enemyPokemonModel3 = nil		-- 3v3 用

BattleSharedData.forbiddenPlayerPokemonIndex = nil		-- 玩家精灵被封的技能索引
BattleSharedData.forbiddenEnemyPokemonIndex = nil		-- 敌人精灵被封的技能索引
BattleSharedData.forbiddenPlayerPokemon2Index = nil		-- 2v2
BattleSharedData.forbiddenEnemyPokemon2Index = nil		-- 2v2
BattleSharedData.forbiddenPlayerPokemon3Index = nil		-- 3v3
BattleSharedData.forbiddenEnemyPokemon3Index = nil		-- 3v3