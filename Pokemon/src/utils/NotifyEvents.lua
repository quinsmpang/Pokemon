--[[
	Description: game events
	Author: M.Wan
	Date: 06/23/2014
]]

NotifyEvents = {}

-- 地图事件
NotifyEvents.MapView = {}

-- 剧情结束后进入自由活动  DialogViewController通知, MapLayerController接收
NotifyEvents.MapView.DialogEnded = "NotifyEvents.MapView.DialogEnded"
-- 地图切换完成  MapLayerController通知
NotifyEvents.MapView.MapSwitchEnded = "NotifyEvents.MapView.MapSwitchEnded"