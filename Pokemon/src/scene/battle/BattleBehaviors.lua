--[[
	Description: Battle behaviors.
	Author: M.Wan
	Date: 4/5/2015
]]

luaClass("BattleBehavior")

BattleBehavior.BEHAVIOR_TYPES = {
	ATTACK = 1,				-- 战斗
	USE_ITEM = 2,			-- 使用道具
	CHANGE_POKEMON = 3,		-- 更换精灵
	ESCAPE = 4,				-- 逃跑
}

BattleBehavior.behaviorType = nil
BattleBehavior.isPlayer = nil		-- 是否是玩家行为
--[[
	优先级分为2级，道具使用、精灵更换、逃跑的优先级为2，战斗优先级为1
]]
BattleBehavior.priority = nil		-- 优先级
BattleBehavior.skillId = nil		-- 技能id
BattleBehavior.itemId = nil			-- 道具id
BattleBehavior.pokemonId = nil		-- 更换精灵id

function BattleBehavior:notifyPlaySkillAnimation()
	if self.isPlayer then
		Notifier:notify(NotifyEvents.Battle.PlayerAttackAnimation, self.skillId)
	else
		Notifier:notify(NotifyEvents.Battle.EnemyAttackAnimation, self.skillId)
	end
end


-- 战斗行为
luaClass("AttackBehavior", BattleBehavior)

function AttackBehavior:create(skillId, isPlayer)
	local ret = AttackBehavior:new()
	ret:init(skillId, isPlayer)
	return ret
end

function AttackBehavior:init(skillId, isPlayer)
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.ATTACK
	self.skillId = skillId
	self.priority = 1
	self.isPlayer = isPlayer
end

function AttackBehavior:process()
	local skillModel = SkillInfo:create(self.skillId)
	-- 实际命中率 = (基础命中率 + 我方等级 - 敌方等级) * 命中等级修正 * 道具修正 * 特性修正
	local basicHitRate = skillModel.hitRate + BattleSharedData.currentPokemonModel.level - BattleSharedData.enemyPokemonModel.level
	-- 命中等级修正 = 1 + 命中等级 * 0.1
	local hitRateLevelCorrection = 1 + BattleSharedData.playerPokemonHitRateLevel * 0.1
	-- 道具修正todo
	local itemCorrection = 1
	-- 特性修正todo
	local specicialityCorrection = 1

	local hitRate = math.floor(basicHitRate * hitRateLevelCorrection * itemCorrection * specicialityCorrection)
	if hitRate < 0 then
		hitRate = 0
	elseif hitRate > 100 then
		hitRate = 100
	end

	if FallInRandom(hitRate, 100) then
		-- 判断技能类型 1物理 2特殊 3变化
		if skillModel.type == Enumerations.SKILL_TYPE.PHYSICAL or skillModel.type == Enumerations.SKILL_TYPE.SPECIAL then
			-- 伤害技能
			-- 基础伤害 = (((攻击方等级 * 0.4 + 2) * 技能威力 * 攻击方攻击力 / 防守方防御力) / 50) + 2
			local basicDmg = (BattleSharedData.currentPokemonModel.level * 0.4 + 2) * skillModel.attack
			local atk, def
			-- 特殊攻击还是物理攻击？
			if skillModel.type == Enumerations.SKILL_TYPE.PHYSICAL then
				atk = BattleSharedData.currentPokemonModel.basicData.physicalAttack * (1 + BattleSharedData.playerPokemonPhyAtkLevel * 0.1)
				def = BattleSharedData.enemyPokemonModel.basicData.physicalDefense * (1 + BattleSharedData.enemyPokemonPhyDefLevel * 0.1)
			elseif skillModel.type == Enumerations.SKILL_TYPE.SPECIAL then
				atk = BattleSharedData.currentPokemonModel.basicData.specialAttack * (1 + BattleSharedData.playerPokemonSpeAtkLevel * 0.1)
				def = BattleSharedData.enemyPokemonModel.basicData.specialDefense * (1 + BattleSharedData.enemyPokemonSpeDefLevel * 0.1)
			end
			-- 道具修正todo
			local itemCorrection = 1
			-- 天气修正todo
			local weatherCorrection = 1
			-- 随机修正todo
			local randomCorrection = math.random(85, 100) / 100
			-- 属性修正todo
			local propertyCorrection = 1
			-- 烧伤修正
			local burnCorrection = 1
			if BattleSharedData.currentPokemonModel.status == Enumerations.POKEMON_STATUS.BURNED and skillModel.type == Enumerations.SKILL_TYPE.PHYSICAL then
				burnCorrection = 0.5
			end
			-- 特性修正todo
			local specicialityCorrection = 1
			local 
			-- 会心一击修正
			local criticalCorrection = 1
			local criticalLevel = BattleSharedData.currentPokemonModel:getCriticalLevel() + BattleSharedData.playerPokemonCriticalLevel
			if criticalLevel < 1 then
				criticalLevel = 1
			elseif criticalLevel > 4 then
				criticalLevel = 4
			end
			if FallInRandom(1, BattleLogicConstants.CRITICAL_RATE[criticalLevel]) then
				criticalCorrection = 1.5
			end
			-- 记录一些修正值 用于判断一些文字是否显示
			if self.isPlayer then
				BattleSharedData.playerLastSkillCriticalCorrection = criticalCorrection
				BattleSharedData.playerLastSkillPropertyCorrection = propertyCorrection
			else
				BattleSharedData.enemyLastSkillCriticalCorrection = criticalCorrection
				BattleSharedData.enemyLastSkillPropertyCorrection = propertyCorrection
			end
			-- 最终伤害
			local dmg = (basicDmg * atk / def / 50 + 2) * itemCorrection * weatherCorrection * randomCorrection * propertyCorrection * burnCorrection * specicialityCorrection
			dmg = math.floor(dmg)
			log("Final damage value: " .. dmg)
			BattleSharedData.enemyPokemonModel:hurt(dmg)
		elseif skillModel.type == Enumerations.SKILL_TYPE.VARIATION then
			-- 变化技能
			BattleSharedData.playerLastSkillCriticalCorrection = 1
			BattleSharedData.playerLastSkillPropertyCorrection = 1
			BattleSharedData.enemyLastSkillCriticalCorrection = 1
			BattleSharedData.enemyLastSkillPropertyCorrection = 1
		else
			assert(false, "Invalid skill type.")
		end

		local dialogKey = "USE_SKILL"
		Notifier:notify(NotifyEvents.Battle.ShowDialog, dialogKey, (self.isPlayer and "我方" .. BattleSharedData.currentPokemonModel.model.name or "敌方" .. BattleSharedData.enemyPokemonModel.model.name), skillModel.name)
		CallFunctionAsync(self, self.notifyPlaySkillAnimation, 0.5)
	end
end


-- 使用道具行为
luaClass("UseItemBehavior", BattleBehavior)

function UseItemBehavior:create(itemId, isPlayer)
	local ret = UseItemBehavior:new()
	ret:init(itemId, isPlayer)
	return ret
end

function UseItemBehavior:init(itemId, isPlayer)
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.USE_ITEM
	self.itemId = itemId
	self.priority = 2
	self.isPlayer = isPlayer
end

function UseItemBehavior:process()
	
end


-- 更换精灵行为
luaClass("ChangePokemonBehavior", BattleBehavior)

function ChangePokemonBehavior:create(pokemonId, isPlayer)
	local ret = ChangePokemonBehavior:new()
	ret:init(pokemonId, isPlayer)
	return ret
end

function ChangePokemonBehavior:init(pokemonId, isPlayer)
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.CHANGE_POKEMON
	self.pokemonId = pokemonId
	self.priority = 2
	self.isPlayer = isPlayer
end

function ChangePokemonBehavior:process()
	
end


-- 逃跑行为
luaClass("EscapeBehavior", BattleBehavior)

function EscapeBehavior:create(isPlayer)
	local ret = EscapeBehavior:new()
	ret:init(isPlayer)
	return ret
end

function EscapeBehavior:init(isPlayer)
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.ESCAPE
	self.priority = 2
	self.isPlayer = isPlayer
end

function EscapeBehavior:process()
	if BattleSharedData.battleType == Enumerations.BATTLE_TYPE.WILD then
		-- 逃跑成功率
		-- 可能受到特性影响 todo
		local successParam = math.floor(BattleSharedData.currentPokemonModel.level / BattleSharedData.enemyPokemonModel.level * 100)
		local rd = math.random(1, 100)
		if rd <= successParam then
			-- 逃跑成功
			BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.ESCAPE)
			local dialogKey = "ESCAPE_SUCCESS"
			Notifier:notify(NotifyEvents.Battle.UpdateDialog, dialogKey)
		else
			-- 逃跑失败
			BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.ENEMY_TURN)
			local dialogKey = "ESCAPE_FAILURE"
			Notifier:notify(NotifyEvents.Battle.UpdateDialog, dialogKey)
		end
	else
		local dialogKey = "ESCAPE_FORBIDDEN"
		Notifier:notify(NotifyEvents.Battle.UpdateDialog, dialogKey)
	end
end