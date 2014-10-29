--[[
	Description: game events
	Author: M.Wan
	Date: 06/23/2014
]]

NotifyEvents = {}

-- 地图事件
NotifyEvents.MapView = NotifyEvents.MapView or {}

-- 开始处理Action  ActionController通知, MapLayerController接收
NotifyEvents.MapView.ActionBegan = "NotifyEvents.MapView.ActionBegan"
-- Action处理完毕  MapLayerController通知，DialogLayerController接收
NotifyEvents.MapView.ActionEnded = "NotifyEvents.MapView.ActionEnded"
-- 指令处理完毕  TMXMapLayer通知，MapLayerController接收
NotifyEvents.MapView.ActionInstructionsEnded = "NotifyEvents.MapView.ActionInstructionsEnded"
-- 切换地图	TMXMapLayer通知，MapLayerController接收
NotifyEvents.MapView.SwitchMap = "NotifyEvents.MapView.SwitchMap"
-- 菜单项被选中 MapMenu通知, MenuLayerController接收
NotifyEvents.MapView.MenuItemSelected = "NotifyEvents.MapView.MenuItemSelected"
-- 开始处理Response  ResponseController通知, DialogLayerController, MapLayerController, MenuLayerController接收
NotifyEvents.MapView.ResponseBegan = "NotifyEvents.MapView.ResponseBegan"

-- 精灵界面事件
NotifyEvents.PokemonView = NotifyEvents.PokemonView or {}

-- 响应PokemonMainView的事件  PokemonMainView通知, PokmeonViewController观察
NotifyEvents.PokemonView.BtnClick = "NotifyEvents.PokemonView.BtnClick"