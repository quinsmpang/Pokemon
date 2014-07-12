--[[
	Description: Trigger info (from map)
	Author: M.Wan
	Date: 07/10/2014
]]

luaClass("Trigger", psModel)

Trigger.position = DBNULL		-- 位置
Trigger.width = DBNULL			-- 宽度
Trigger.height = DBNULL			-- 高度
Trigger.lastStep = DBNULL		-- 触发所需的上一个step
Trigger.step = DBNULL			-- 触发的step
Trigger.action = DBNULL			-- 触发后需要执行的action(可以没有)

function Trigger:create(triggerInfo)
	if type(triggerInfo) ~= "table" then
		return nil
	end

	local model = Trigger:new()
	model:initWithInfo(triggerInfo)

	return model
end

function Trigger:initWithInfo(triggerInfo)
	self.position = ccp(tonumber(triggerInfo["x"]) / 32, tonumber(triggerInfo["y"]) / 32)
	self.width = triggerInfo["width"] / 32
	self.height = triggerInfo["height"] / 32
	self.lastStep = tonumber(triggerInfo["lastStep"])
	self.step = tonumber(triggerInfo["step"])
	self.action = tonumber(triggerInfo["action"])
end