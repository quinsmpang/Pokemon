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
	RemoveSpriteFrames(self.resources)
end

function MapLayerController:addObservers()
	log("MapLayerController:addObservers")
	Notifier:addObserver(NotifyEvents.MapView.ActionBegan, self, self.onActionBegan)
	Notifier:addObserver(NotifyEvents.MapView.SwitchMap, self, self.switchMap)
	Notifier:addObserver(NotifyEvents.MapView.MapKeyboardResponse, self, self.onKeyboardEvent)
end

function MapLayerController:removeObservers()
	log("MapLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionBegan, self)
	Notifier:removeObserver(NotifyEvents.MapView.ActionInstructionsEnded, self)
	Notifier:removeObserver(NotifyEvents.MapView.MapKeyboardResponse, self)
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

function MapLayerController:onKeyboardEvent(keyCode, eventType)
	log("MapLayerController:onKeyboardEvent, eventType: [" .. eventType .. "]")
	if eventType == Enumerations.KEYBOARD_STATE.PRESSED then
		-- 方向键处理
		local nextDir = nil
		if keyCode == GameSettings.upKey then
			nextDir = Enumerations.DIRECTIONS.UP
		elseif keyCode == GameSettings.downKey then
			nextDir = Enumerations.DIRECTIONS.DOWN
		elseif keyCode == GameSettings.leftKey then
			nextDir = Enumerations.DIRECTIONS.LEFT
		elseif keyCode == GameSettings.rightKey then
			nextDir = Enumerations.DIRECTIONS.RIGHT
		else
			return
		end

		local hero = self.currentMap.hero
		if DataCenter.currentPlayerData.currentDirection ~= nextDir then
			hero:changeDirection(nextDir)
			DataCenter.currentPlayerData.currentDirection = nextDir
		else
			self.currentMap:heroWalk(nextDir)
		end
	elseif eventType == Enumerations.KEYBOARD_STATE.RELEASED then
	end
end

function MapLayerController:switchMap(newMapId)
	-- 记录上一个状态
	local lastState = MapStateController:getCurrentState()
	MapStateController:setCurrentState(Enumerations.MAP_STATE.LOADING)
	local coreLayer = self:getScene():getCoreLayer()

	if self.currentMap and self.currentMap.mapInfo.id == newMapId then
		self.currentMap:setVisible(true)
	else
		-- 记录新地图id
		DataCenter.currentPlayerData.currentMapId = newMapId

		local newMapInfo = GameDBHelper:queryMapById(newMapId)
		local newMap = TMXMapLayer:createWithMapInfo(newMapInfo)

		if self.currentMap then
			coreLayer:popLayer()
		end
		self.currentMap = newMap
		self.currentMap:retain()
		CallFunctionAsync(coreLayer, function() 
				coreLayer:pushLayer(newMap) 
				newMap:release()
				-- 还原上一个状态
				MapStateController:setCurrentState(lastState)
			end, 0.25, newMap)
	end
	--coreLayer:pushLayer(newMap)
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
	self:switchMap(mapId)
	CallFunctionAsync(self, self.endAction, 0.5)
end

function MapLayerController:action_WalkOut(params)
	params = string.split(params, ",")
	local target = tonumber(params[1])

	local observers = {}
	if params[2] ~= "" then
		observers = string.split(params[2], "|")
		for i, observer in ipairs(observers) do
			observers[i] = tonumber(observer)
		end
	end

	local instructions = QueueLua:new()
	for i = 3, #params do
		local param = string.split(params[i], "|")
		local ins = { tonumber(param[1]), tonumber(param[2]) }
		instructions:enqueue(ins)
		--table.insert(instructions, ins)
	end

	--取出第一个指令直接执行，并移除第一个指令
	local firstIns = instructions:front().data
	local dir = firstIns[1]
	firstIns[2] = firstIns[2] - 1
	if firstIns[2] <= 0 then
		instructions:dequeue()
	end

	-- target为0说明目标是hero
	if target == 0 then
		self.currentMap:setInstructions(instructions, observers)
		self.currentMap:heroWalkWithInstructions(nil, dir)
	end

	Notifier:addObserver(NotifyEvents.MapView.ActionInstructionsEnded, self, self.onWalkOutEnd, target)
end

function MapLayerController:action_SwitchMap(params)
	local newMapId = tonumber(params)
	self:switchMap(newMapId)
	CallFunctionAsync(self, self.endAction, 0.5)
end

-------------------------- Action相关的回调函数 --------------------------
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

function MapLayerController:onWalkOutEnd(target)
	if target == 0 then
		self.currentMap.hero:removeFromParent()
	end

	CallFunctionAsync(self, self.endAction, 0.5)
end