--[[
	Description: game events
	Author: M.Wan
	Date: 06/23/2014
]]

NotifyEvents = {}

-- 地图事件
NotifyEvents.MapView = {}

-- 开始处理Action  DialogViewController通知, MapLayerController接收
NotifyEvents.MapView.ActionBegan = "NotifyEvents.MapView.ActionBegan"
-- Action处理完毕  MapLayerController通知，DialogViewController接收
NotifyEvents.MapView.ActionEnded = "NotifyEvents.MapView.ActionEnded"
-- 指令处理完毕  TMXMapLayer通知，MapLayerController接收
NotifyEvents.MapView.ActionInstructionsEnded = "NotifyEvents.MapView.ActionInstructionsEnded"