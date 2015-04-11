--[[
	Description: Public game enumerations
	Author: M.Wan
	Date: 06/20/2014
]]

Enumerations = {}

-- 性别
Enumerations.GENDER = {
	MALE = 0,
	FEMALE = 1,
}

-- 方向
Enumerations.DIRECTIONS = {
	UP = 1,
	LEFT = 2,
	DOWN = 3,
	RIGHT = 4,
}

-- Map state
Enumerations.MAP_STATE = {
	FREEDOM = 1,
	DIALOG = 2,
	MENU = 3,
	ACTION = 4,
}

-- 响应类型
Enumerations.RESPONSE_TYPE = {
	NORMAL = 0,
	QUESTION = 1,
	BRANCH = 2,
	RECOVER = 3,
	LAYER = 4,
}

-- 属性
Enumerations.PROPERTIES = {
	NORMAL = 1,		-- 普通
	FIGHTING = 2,	-- 格斗
	FLYING = 3,		-- 飞行
	POISON = 4,		-- 毒
	GROUND = 5,		-- 地
	ROCK = 6,		-- 岩
	BUG = 7,		-- 虫
	GHOST = 8,		-- 鬼
	STEEL = 9,		-- 钢
	FIRE = 10,		-- 火
	WATER = 11, 	-- 水
	GRASS = 12,		-- 草
	ELECTRIC = 13,	-- 电
	PSYCHIC = 14, 	-- 超能
	ICE = 15,		-- 冰
	DRAGON = 16,	-- 龙
	DARK = 17,		-- 恶
	FAIRY = 18,		-- 妖精
}

-- 属性字符串
Enumerations.PROPERTY_STRING = {
	[1] = "普通",
	[2] = "格斗",
	[3] = "飞行",
	[4] = "毒",
	[5] = "地",
	[6] = "岩",
	[7] = "虫",
	[8] = "鬼",
	[9] = "钢",
	[10] = "火",
	[11] = "水",
	[12] = "草",
	[13] = "电",
	[14] = "超能",
	[15] = "冰",
	[16] = "龙",
	[17] = "恶",
	[18] = "妖精",
}

-- 宠物状态
Enumerations.POKEMON_STATUS = {
	NORMAL = 0,		-- 正常
	POISON = 1,		-- 中毒
	SLEEP = 2,		-- 睡眠
	PALSY = 3,		-- 麻痹
	BURNED = 4,		-- 烧伤
	FROZEN = 5,		-- 冰冻
	DEAD = 6,		-- 濒死
}

-- 宠物性格
Enumerations.POKEMON_PERSONALITY = {
	HARDY = 0,		-- 实干
	DOCILE = 1,		-- 坦率
	SERIOUS = 2,	-- 认真
	BASHFUL = 3,	-- 害羞
	QUIRKY = 4,		-- 浮躁
	LONELY = 5,		-- 孤僻
	BRAVE = 6,		-- 勇敢
	ADAMANT = 7,	-- 固执
	NAUGHTY = 8,	-- 调皮
	BOLD = 9,		-- 大胆
	RELAXED = 10,	-- 悠闲
	IMPISH = 11,	-- 淘气
	LAX = 12,		-- 无虑
	TIMID = 13,		-- 胆小
	HASTY = 14,		-- 急躁
	JOLLY = 15,		-- 开朗
	NAIVE = 16,		-- 天真
	MODEST = 17,	-- 保守
	MILD = 18,		-- 稳重
	QUIET = 19,		-- 冷静
	RASH = 20,		-- 马虎
	CALM = 21,		-- 沉着
	GENTLE = 22,	-- 温顺
	SASSY = 23,		-- 狂妄
	CAREFUL = 24,	-- 慎重
}

-- 精灵球
Enumerations.POKEBALL = {
	MASTER_BALL = 1,	-- 大师球
	ULTRA_BALL = 2,		-- 超级球
	GREAT_BALL = 3,		-- 高级球
	POKE_BALL = 4,		-- 精灵球
}

-- 技能类型
Enumerations.SKILL_TYPE = {
	PHYSICAL = 1,		-- 物理
	SPECIAL = 2,		-- 特殊
	VARIATION = 3,		-- 变化
}

-- 技能目标类型
Enumerations.SKILL_TARGET_TYPE = {
	SINGLE_ENEMY = 1,	-- 敌方单体
	ALL_ENEMIES = 2,	-- 敌方全体
	SELF = 3,			-- 自身
	EXCEPT_SELF = 4,	-- 自身以外
	RANDOM_ENEMY = 5,	-- 敌方随机
	SELF_PLACE = 6,		-- 己方场地
	ENEMY_PLACE = 7,	-- 敌方场地
	ALL_PLACE = 8,		-- 全场场地
	FRIEND = 9,			-- 队友
	WAITING = 10,		-- 待机
	UNKNOWN = 11,		-- 不定
	ANY = 12,			-- 任选
}

-- 战斗状态
Enumerations.BATTLE_STATUS = {
	CONFUSED = 1,		-- 混乱
	SCARED = 2,			-- 害怕
	ATTRACTED = 3,		-- 着迷
	BOUND = 4,			-- 束缚
	TIRED = 5,			-- 无法动弹
}

-- 性格名称
Enumerations.PERSONALITY_NAME = {
	[0] = "实干",
	[1] = "坦率",
	[2] = "认真",
	[3] = "害羞",
	[4] = "浮躁",
	[5] = "孤僻",
	[6] = "勇敢",
	[7] = "固执",
	[8] = "调皮",
	[9] = "大胆",
	[10] = "悠闲",
	[11] = "淘气",
	[12] = "无虑",
	[13] = "胆小",
	[14] = "急躁",
	[15] = "开朗",
	[16] = "天真",
	[17] = "保守",
	[18] = "稳重",
	[19] = "冷静",
	[20] = "马虎",
	[21] = "沉着",
	[22] = "温顺",
	[23] = "狂妄",
	[24] = "慎重",
}

-- 特殊捕获地点
Enumerations.CAPTURE_PLACES = {
	[10001] = "命中注定般相遇",
}

-- 精灵界面场景参数
Enumerations.POKEMON_VIEW_SCENE_TYPE = {
	VIEW_STATUS = 1,	-- 查看精灵状态
	USE_ITEM = 2,		-- 使用道具
	CARRY_ITEM = 3,		-- 携带道具
}

-- 背包界面场景参数
Enumerations.BAG_VIEW_SCENE_TYPE = {
	VIEW_ITEMS = 1,		-- 查看道具信息
	CARRY_ITEM = 2,		-- 精灵的携带道具
	BATTLE = 3,			-- 战斗中
}

-- 战斗类型
Enumerations.BATTLE_TYPE = {
	WILD = 1,		-- 野生精灵遭遇
	TRAINER_1V1 = 2,	-- 1v1战斗
	TRAINER_2V2 = 3,	-- 2v2战斗
	TRAINER_3V3_TOGETHER = 4,	-- 3v3战斗(共存制)
	TRAINER_3V3_ROTATION = 5,	-- 3v3战斗(旋转制)
	CONNECTION_1V1 = 6,		-- 联机对战1v1
	CONNECTION_2V2 = 7,		-- 联机对战2v2
	CONNECTION_3V3_TOGETHER = 6,	-- 联机对战3v3(共存制)
	CONNECTION_3V3_ROTATION = 7,	-- 联机对战3v3(旋转制)
}