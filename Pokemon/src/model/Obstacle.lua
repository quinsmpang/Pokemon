--[[
	Description: Obstacle info
	Author: M.Wan
	Date: 06/23/2014
]]

luaClass("Obstacle", psModel)

Obstacle.position = DBNULL		-- 障碍所在地图位置
Obstacle.width = DBNULL			-- 宽度
Obstacle.height = DBNULL		-- 高度
Obstacle.allowLeft = DBNULL		-- 是否允许从左侧进入
Obstacle.allowRight = DBNULL		-- 是否允许从右侧进入
Obstacle.allowUp = DBNULL			-- 是否允许从上面进入
Obstacle.allowDown = DBNULL		--是否可以从下面进入
Obstacle.shouldBeCovered = DBNULL	-- 进入后是否应该被遮盖
Obstacle.responseId = DBNULL		-- 响应的事件id, -1表示不能响应

function Obstacle:create(obstacles)
	if type(obstacles) ~= "table" then
		return nil
	end

	local model = Obstacle:new()
	model:init(obstacles)

	return model
end

function Obstacle:init(obstacles)
	self.position = ccp(tonumber(obstacles["x"]) / 32, tonumber(obstacles["y"]) / 32)
	self.width = tonumber(obstacles["width"] / 32)
	self.height = tonumber(obstacles["height"] / 32)
	self.allowLeft = tonumber(obstacles["allowLeft"]) == 1
	self.allowRight = tonumber(obstacles["allowRight"]) == 1
	self.allowUp = tonumber(obstacles["allowUp"]) == 1
	self.allowDown = tonumber(obstacles["allowDown"]) == 1
	self.shouldBeCovered = tonumber(obstacles["shouldBeCovered"]) == 1
	self.responseId = tonumber(obstacles["responseId"])
end

function Obstacle:canBeResponsed()
	return self.responseId ~= -1
end