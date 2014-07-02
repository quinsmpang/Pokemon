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
Entrance.isEnabled = DBNULL		-- 是否可用
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
	self.isEnabled = tonumber(entranceInfo["enabled"]) == 1
	self.message = entranceInfo["message"]
	self.relatedMapId = tonumber(entranceInfo["relatedMapId"])
end