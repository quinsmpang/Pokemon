--[[
	Description: game events
	Author: M.Wan
	Date: 06/23/2014
]]

NotifyEvents = {}

-- 地图事件
NotifyEvents.MapView = NotifyEvents.MapView or {}

-- 响应MapLayerController的键盘事件	MapCoreLayer通知, MapLayerController接收
NotifyEvents.MapView.MapKeyboardResponse = "NotifyEvents.MapView.MapKeyboardResponse"
-- 响应DialogLayerController的键盘事件	MapCoreLayer通知, DialogLayerController接收
NotifyEvents.MapView.DialogKeyboardResponse = "NotifyEvents.MapView.DialogKeyboardResponse"
-- 响应MenuLayerController的键盘事件	MapCoreLayer通知, MenuLayerController接收
NotifyEvents.MapView.MenuKeyboardResponse = "NotifyEvents.MapView.MenuKeyboardResponse"
-- 开始处理Action  DialogViewController通知, MapLayerController接收
NotifyEvents.MapView.ActionBegan = "NotifyEvents.MapView.ActionBegan"
-- Action处理完毕  MapLayerController通知，DialogViewController接收
NotifyEvents.MapView.ActionEnded = "NotifyEvents.MapView.ActionEnded"
-- 指令处理完毕  TMXMapLayer通知，MapLayerController接收
NotifyEvents.MapView.ActionInstructionsEnded = "NotifyEvents.MapView.ActionInstructionsEnded"
-- 切换地图	TMXMapLayer通知，MapLayerController接收
NotifyEvents.MapView.SwitchMap = "NotifyEvents.MapView.SwitchMap"