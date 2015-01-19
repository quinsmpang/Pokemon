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
-- 显示菜单	SaveGameLayer通知, MapLayerController观察
NotifyEvents.MapView.ShowMapMenu = "NotifyEvents.MapView.ShowMapMenu"
-- 玩家移动了一格  TMXMapLayer通知, MapLayerController观察
NotifyEvents.MapView.HeroMoved = "NotifyEvents.MapView.HeroMoved"
-- 摇杆触屏事件	DirectionRockerLayer通知, MapLayerController观察
NotifyEvents.MapView.RockerEvent = "NotifyEvents.MapView.RockerEvent"
-- 行走/奔跑切换	DirectionRockerLayer通知, MapLayerController观察
NotifyEvents.MapView.WalkStateChanged = "NotifyEvents.MapView.WalkStateChanged"
-- 地图菜单点击时间	DirectionRockerLayer通知, MapLayerController观察
NotifyEvents.MapView.MapMenuClicked = "NotifyEvents.MapView.MapMenuClicked"

-- 精灵界面事件
NotifyEvents.PokemonView = NotifyEvents.PokemonView or {}

-- 响应PokemonMainView的事件  PokemonMainView通知, PokmeonViewController观察
NotifyEvents.PokemonView.MainViewKeyResponsed = "NotifyEvents.PokemonView.MainViewKeyResponsed"
-- 交换精灵位置	PokemonMainView通知, PokmeonViewController观察
NotifyEvents.PokemonView.ExchangePokemonPosition = "NotifyEvents.PokemonView.ExchangePokemonPosition"
-- PokemonDetailView菜单选中事件	PokemonDetailView通知, PokmeonViewController观察
NotifyEvents.PokemonView.DetailMenuItemSelected = "NotifyEvents.PokemonView.DetailMenuItemSelected"
-- PokemonDetailView菜单变化选中项事件	PokemonDetailView通知, PokmeonViewController观察
NotifyEvents.PokemonView.DetailMenuItemChanged = "NotifyEvents.PokemonView.DetailMenuItemChanged"

-- 保存界面事件
NotifyEvents.SaveView = NotifyEvents.SaveView or {}

-- 新游戏中，确认选择了对应存档点	LoadGameLayerController通知, MainViewController观察
NotifyEvents.SaveView.SaveSelected = "NotifyEvents.SaveView.SaveSelected"

-- 背包界面事件
NotifyEvents.Bag = NotifyEvents.Bag or {}

-- Title切换事件	BagMainView通知, BagViewController观察
NotifyEvents.Bag.TitleChanged = "NotifyEvents.Bag.TitleChanged"
-- 道具选择变更	BagMainView通知, BagViewController观察
NotifyEvents.Bag.ItemSelectionChanged = "NotifyEvents.Bag.ItemSelectionChanged"
-- BagMainView事件	BagMainView通知, BagViewController观察
NotifyEvents.Bag.MainViewKeyResponsed = "NotifyEvents.Bag.MainViewKeyResponsed"
-- 道具确认选择	BagMainView通知, BagViewController观察
NotifyEvents.Bag.ItemSelected = "NotifyEvents.Bag.ItemSelected"

-- 图鉴界面事件
NotifyEvents.Collection = NotifyEvents.Collection or {}

-- 图鉴主界面键盘事件 CollectionView通知, CollectionViewController观察
NotifyEvents.Collection.MainViewKeyResponsed = "NotifyEvents.Collection.MainViewKeyResponsed"
-- 图鉴选择变更 CollectionView通知, CollectionViewController观察
NotifyEvents.Collection.CollectionSelectionChanged = "NotifyEvents.Collection.CollectionSelectionChanged"
-- 图鉴选择 CollectionView通知, CollectionViewController观察
NotifyEvents.Collection.CollectionSelected = "NotifyEvents.Collection.CollectionSelected"
-- 图鉴详情界面事件 CollectionView通知, CollectionViewController观察
NotifyEvents.Collection.DetailViewKeyResponsed = "NotifyEvents.Collection.DetailViewKeyResponsed"

-- 战斗事件
NotifyEvents.Battle = NotifyEvents.Battle or {}

-- 需要响应战斗对话框 BattleUIController通知, BattleDialogController观察
NotifyEvents.Battle.UpdateDialog = "NotifyEvents.Battle.UpdateDialog"
-- 战斗对话显示完成 BattleDialogController通知, BattleUIController观察
NotifyEvents.Battle.DialogEnded = "NotifyEvents.Battle.DialogEnded"