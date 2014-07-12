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