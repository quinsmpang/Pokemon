--[[
	Description: game events
	Author: M.Wan
	Date: 06/23/2014
]]

NotifyEvents = {}

-- 地图事件
NotifyEvents.MapView = NotifyEvents.MapView or {}

-- 处理地图状态	TMXMapLayer通知, MapLayerController观察
NotifyEvents.MapView.MapUpdate = "NotifyEvents.MapView.MapUpdate"
-- 开始处理Action  ActionController通知, MapLayerController观察
NotifyEvents.MapView.ActionBegan = "NotifyEvents.MapView.ActionBegan"
-- Action处理完毕  MapLayerController通知，DialogLayerController观察
NotifyEvents.MapView.ActionEnded = "NotifyEvents.MapView.ActionEnded"
-- 指令处理完毕  TMXMapLayer通知，MapLayerController观察
NotifyEvents.MapView.ActionInstructionsEnded = "NotifyEvents.MapView.ActionInstructionsEnded"
-- 切换地图	TMXMapLayer通知，MapLayerController观察
NotifyEvents.MapView.SwitchMap = "NotifyEvents.MapView.SwitchMap"
-- 显示入口消息	TMXMapLayer通知，MapLayerController观察
NotifyEvents.MapView.ShowEntranceMessage = "NotifyEvents.MapView.ShowEntranceMessage"
-- 菜单项被选中 MapMenu通知, MenuLayerController观察
NotifyEvents.MapView.MenuItemSelected = "NotifyEvents.MapView.MenuItemSelected"
-- 开始处理Response  ResponseController通知, DialogLayerController, MapLayerController观察
NotifyEvents.MapView.ResponseBegan = "NotifyEvents.MapView.ResponseBegan"
-- 地图状态变更	MapStateController通知, MapLayerController, DialogLayerController观察
NotifyEvents.MapView.MapStateChanged = "NotifyEvents.MapView.MapStateChanged"

-- 精灵界面事件
NotifyEvents.PokemonView = NotifyEvents.PokemonView or {}

-- 响应PokemonMainView的事件  PokemonMainView通知, PokmeonViewController观察
NotifyEvents.PokemonView.MainViewKeyResponsed = "NotifyEvents.PokemonView.MainViewKeyResponsed"
-- 交换精灵位置	PokemonMainView通知, PokmeonViewController观察
NotifyEvents.PokemonView.ExchangePokemonPosition = "NotifyEvents.PokemonView.ExchangePokemonPosition"