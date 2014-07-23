--[[
	Description: Entrance info (from map)
	Author: M.Wan
	Date: 06/24/2014
]]

luaClass("Entrance", psModel)

Entrance.position = DBNULL		-- 入口位置
Entrance.width = DBNULL			-- 宽度
Entrance.height = DBNULL		-- 高度
Entrance.direction = DBNULL		-- 出口方向
Entrance.conditionId = DBNULL 	-- 可用条件
Entrance.conditionParam = DBNULL	-- 条件参数
Entrance.message = DBNULL		-- 不可用状态下显示的消息
Entrance.relatedMapId = DBNULL	-- 相连的地图id

function Entrance:create(entranceInfo)
	if type(entranceInfo) ~= "table" then
		return nil
	end

	local model = Entrance:new()
	model:initWithInfo(entranceInfo)

	return model
end

function Entrance:initWithInfo(entranceInfo)
	self.position = ccp(tonumber(entranceInfo["x"]) / 32, tonumber(entranceInfo["y"]) / 32)
	self.width = entranceInfo["width"] / 32
	self.height = entranceInfo["height"] / 32
	self.direction = tonumber(entranceInfo["direction"])
	if entranceInfo["conditionId"] then
		self.conditionId = tonumber(entranceInfo["conditionId"])
		self.conditionParam = entranceInfo["conditionParam"]
	end
	self.message = entranceInfo["message"]
	self.relatedMapId = tonumber(entranceInfo["relatedMapId"])
end

function Entrance:isEnabled()
	if self.conditionId == DBNULL then
		return true
	end
	return self:checkCondition()
end

function Entrance:checkCondition()
	if self.conditionId == 1 then
		return DataCenter.currentPlayerData.lastStep >= tonumber(self.conditionParam)
	end
	return true
end