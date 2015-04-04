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
--[[
	优先级分为2级，道具使用、精灵更换、逃跑的优先级为2，战斗优先级为1
]]
BattleBehavior.priority = nil		-- 优先级
BattleBehavior.skillId = nil		-- 技能id
BattleBehavior.itemId = nil			-- 道具id
BattleBehavior.pokemonId = nil		-- 更换精灵id


-- 战斗行为
luaClass("AttackBehavior", BattleBehavior)

function AttackBehavior:create(skillId)
	local ret = AttackBehavior:new()
	ret:init(skillId)
	return ret
end

function AttackBehavior:init(skillId)
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.ATTACK
	self.skillId = skillId
	self.priority = 1
end

function AttackBehavior:process()

end


-- 使用道具行为
luaClass("UseItemBehavior", BattleBehavior)

function UseItemBehavior:create(itemId)
	local ret = UseItemBehavior:new()
	ret:init(itemId)
	return ret
end

function UseItemBehavior:init(itemId)
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.USE_ITEM
	self.itemId = itemId
	self.priority = 2
end

function UseItemBehavior:process()
	
end


-- 更换精灵行为
luaClass("ChangePokemonBehavior", BattleBehavior)

function ChangePokemonBehavior:create(pokemonId)
	local ret = ChangePokemonBehavior:new()
	ret:init(pokemonId)
	return ret
end

function ChangePokemonBehavior:init(pokemonId)
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.CHANGE_POKEMON
	self.pokemonId = pokemonId
	self.priority = 2
end

function ChangePokemonBehavior:process()
	
end


-- 逃跑行为
luaClass("EscapeBehavior", BattleBehavior)

function EscapeBehavior:create()
	local ret = EscapeBehavior:new()
	ret:init()
	return ret
end

function EscapeBehavior:init()
	self.behaviorType = BattleBehavior.BEHAVIOR_TYPES.ESCAPE
	self.priority = 2
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