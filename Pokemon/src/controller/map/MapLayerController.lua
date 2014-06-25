--[[
	Description: map layer controller
	Author: M.Wan
	Date: 05/29/2014
]]

class("MapLayerController", psViewController)

require "src/view/map/TMXMapLayer"

MapLayerController.currentMap = nil		-- 当前地图层

MapLayerController.resources = {
	"images/characters.plist", 
	"images/characters.pvr.ccz",
}

-- const
MapLayerController.ZORDER = {
	PLAYER = 999,
}

function MapLayerController:load()
	log("MapLayerController:load")
	self:loadResources()
	self:addObservers()
	self:renderView()
end

function MapLayerController:unload()
	log("MapLayerController:unload")
	self:cleanResources()
	self:removeObservers()
end

function MapLayerController:loadResources()
	log("MapLayerController:loadResources")
	LoadSpriteFrames(self.resources)
end

function MapLayerController:cleanResources()
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(self.resources[i])
	end
end

function MapLayerController:addObservers()
	log("MapLayerController:addObservers")
	Notifier:addObserver(NotifyEvents.MapView.ActionBegan, self, self.onActionBegan)
end

function MapLayerController:removeObservers()
	log("MapLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionBegan, self)
end

function MapLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	local playerData = DataCenter.currentPlayerData
	local mapInfo = MapInfo:create(playerData.currentMapId)

	local map = TMXMapLayer:createWithMapInfo(mapInfo)
	self.currentMap = map

	coreLayer:pushLayer(map)
end

function MapLayerController:onActionBegan(actionModel)
	log("MapLayerController:onActionBegan", actionModel.handler)
	local actionHandler = actionModel.handler
	local handler = self["action_" .. actionHandler]
	assert(type(handler) == "function", "Unimplemented action handler in MapLayerController.")
	handler(self, actionModel.params)
end

-- don't forget to call this function when action is over.
function MapLayerController:endAction()
	log("MapLayerController:endAction")
	Notifier:notify(NotifyEvents.MapView.ActionEnded)
end

-------------------------- Action 处理函数 --------------------------
function MapLayerController:action_FadeOut(params)
	if self.currentMap then
		self.currentMap:removeFromParent()
		CallFunctionAsync(self, self.endAction, 0.5)
	end
end