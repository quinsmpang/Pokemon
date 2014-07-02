--[[
	Description: Obstacle info (from map)
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

function Obstacle:create(obstacleInfo)
	if type(obstacleInfo) ~= "table" then
		return nil
	end

	local model = Obstacle:new()
	model:initWithInfo(obstacleInfo)

	return model
end

function Obstacle:initWithInfo(obstacleInfo)
	self.position = ccp(tonumber(obstacleInfo["x"]) / 32, tonumber(obstacleInfo["y"]) / 32)
	self.width = tonumber(obstacleInfo["width"] / 32)
	self.height = tonumber(obstacleInfo["height"] / 32)
	self.allowLeft = tonumber(obstacleInfo["allowLeft"]) == 1
	self.allowRight = tonumber(obstacleInfo["allowRight"]) == 1
	self.allowUp = tonumber(obstacleInfo["allowUp"]) == 1
	self.allowDown = tonumber(obstacleInfo["allowDown"]) == 1
	self.shouldBeCovered = tonumber(obstacleInfo["shouldBeCovered"]) == 1
	self.responseId = tonumber(obstacleInfo["responseId"])
end

function Obstacle:canBeResponsed()
	return self.responseId ~= -1
end