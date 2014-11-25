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

-- Action Type
Enumerations.ACTION_TYPE = {
	FADEOUT = 1,		-- 显示黑屏
	FADEIN = 2,			-- 显示地图
	WALKOUT = 3,		-- 移动并走出地图
	FADEOUTIN = 4,		-- 立即更换地图
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

-- 事件类型
Enumerations.EVENT_TYPE = {
	GAIN_NEW_PET = 1,	-- 获得新宠物
}

-- 属性
Enumerations.PROPERTIES = {
	NORMAL = 1,		-- 普通
	WRESTLE = 2,	-- 格斗
	FLY = 3,		-- 飞行
	POISON = 4,		-- 毒
	GROUND = 5,		-- 地
	STONE = 6,		-- 岩
	INSECT = 7,		-- 虫
	GHOST = 8,		-- 鬼
	STEEL = 9,		-- 钢
	FIRE = 10,		-- 火
	WATER = 11, 	-- 水
	GRASS = 12,		-- 草
	ELECTRICITY = 13,	-- 电
	SUPER = 14, 	-- 超能
	ICE = 15,		-- 冰
	DRAGON = 16,	-- 龙
	EVIL = 17,		-- 恶
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
Enumerations.CapturePlaces = {
	[10001] = "命中注定般相遇",
}

-- 精灵界面场景参数
Enumerations.POKEMON_VIEW_SCENE_TYPE = {
	VIEW_STATUS = 1,
}

-- 背包界面场景参数
Enumerations.BAG_VIEW_SCENE_TYPE = {
	VIEW_ITEMS = 1,
}