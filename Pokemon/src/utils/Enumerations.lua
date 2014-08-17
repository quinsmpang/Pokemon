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

-- 地图状态
Enumerations.MAP_STATE = {
	FREEDOM = 1,	-- 自由活动状态
	DIALOG = 2,		-- 对话状态
	MENU = 3,		-- 菜单状态
	LOADING = 4,	-- 读取状态
}

-- 键盘状态
Enumerations.KEYBOARD_STATE = {
	PRESSED = 1,
	RELEASED = 2,
	LONGPRESSED = 3,
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

-- 宠物状态
Enumerations.POKEMON_STATUS = {
	NORMAL = 0,		-- 正常
	POISON = 1,		-- 中毒
	SLEEP = 2,		-- 睡眠
	PALSY = 3,		-- 麻痹
	BURNED = 4,		-- 烧伤
	FROZEN = 5,		-- 冰冻
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