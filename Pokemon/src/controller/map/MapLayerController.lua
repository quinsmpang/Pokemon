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

-- ins = { direction, steps }
function MapLayerController:runInstruction(ins)
	if self.currentMap then
		self.currentMap:move(ins[1], HeroSprite.WALK_DURATION * 3)
	end
end

-------------------------- Action 处理函数 --------------------------
function MapLayerController:action_FadeOut(params)
	if self.currentMap then
		local shouldRemove = params == "1"
		if shouldRemove then
			self:getScene():getCoreLayer():popLayer()
			self.currentMap = nil
		else
			self.currentMap:setVisible(false)
		end
		CallFunctionAsync(self, self.endAction, 0.5)
	end
end

function MapLayerController:action_FadeIn(params)
	local mapId = tonumber(params)
	-- 如果map依然存在，说明是直接显示
	if self.currentMap then
		self.currentMap:setVisible(true)
	else
		local newMapInfo = GameDBHelper:queryMapById(mapId)

		local newMap = TMXMapLayer:createWithMapInfo(newMapInfo)
		self.currentMap = newMap

		self:getScene():getCoreLayer():pushLayer(newMap)
	end
	self:endAction()
end

function MapLayerController:action_WalkOut(params)
	params = string.split(params, ",")
	local target = tonumber(params[1])
	local instructions = {}
	for i = 2, #params do
		local param = string.split(params[i], "|")
		local ins = { tonumber(param[1]), tonumber(param[2]) }
		table.insert(instructions, ins)
	end

	local total = 0
	for _, ins in ipairs(instructions) do
		for i = 1, ins[2] do
			-- 貌似会有误差??
			CallFunctionAsync(self, self.runInstruction, (total + i - 1) * HeroSprite.WALK_DURATION, ins)
		end
		total = total + ins[2]
	end
end