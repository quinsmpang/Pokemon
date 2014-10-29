--[[
	Description: map layer controller
	Author: M.Wan
	Date: 05/29/2014
]]

class("MapLayerController", psViewController)

require "src/view/map/TMXMapLayer"
require "src/view/map/MessageTip"
require "src/view/map/MapNameBoard"

MapLayerController.root = nil
MapLayerController.currentMap = nil		-- 当前地图层

-- logic
MapLayerController.isDirectionKeyPressed = nil
MapLayerController.isCancelKeyPressed = nil
MapLayerController.isEnabled = nil
MapLayerController.nextDirection = nil

-- const
MapLayerController.KEYBOARD_DT = 0.25

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
end

function MapLayerController:removeObservers()
	log("MapLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionBegan, self)
	Notifier:removeObserver(NotifyEvents.MapView.SwitchMap, self)
	Notifier:removeObserver(NotifyEvents.MapView.ActionInstructionsEnded, self)
end

function MapLayerController:renderView()
	self.isDirectionKeyPressed = false
	self.isCancelKeyPressed = false
	self.isEnabled = true

	local coreLayer = self:getScene():getCoreLayer()

	self.root = cc.Layer:create()
	self.root:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
	coreLayer:addChild(self.root)

	local screenSize = cc.Director:getInstance():getWinSize()

	local playerData = DataCenter.currentPlayerData
	local mapInfo = MapInfo:create(playerData.currentMapId)

	local map = TMXMapLayer:createWithMapInfo(mapInfo)
	self.currentMap = map

	coreLayer:pushLayer(map)
end

function MapLayerController:onNodeEvent(event)
	if event == "enter" then
		local kbdListener = Win32EventListenerKeyboard:createWithTarget(self.root)
		kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
		kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardReleased), pf.Handler.WIN32_KEYBOARD_UP)
		Win32Notifier:getInstance():addEventListener(kbdListener)
		self.kbdListener = kbdListener
	elseif event == "exit" then
		if self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
		end
	end
end

function MapLayerController:onKeyboardPressed(keyCode)
	log("!!!")
end

function MapLayerController:onKeyboardReleased(keyCode)
	log("@@@")
end

function MapLayerController:onKeyboardEvent(keyCode, eventType, pressedKeys)
	if not self.isEnabled then
		return
	end
	log("MapLayerController:onKeyboardEvent, eventType: [" .. eventType .. "]")
	if eventType == Enumerations.KEYBOARD_STATE.PRESSED then
		-- 方向键处理
		if keyCode == GameSettings.upKey or keyCode == GameSettings.downKey or keyCode == GameSettings.leftKey or keyCode == GameSettings.rightKey then
			self.isDirectionKeyPressed = true

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

			self.nextDirection = nextDir

			self:handleDirectionEvents()

			-- scheduler is not friendly.
			--self.walkSchedulerEntry = cc.Director:getInstance():getScheduler():scheduleScriptFunc(MakeScriptHandler(self, self.onWalkSchedule, nextDir), HeroSprite.WALK_DURATION * 2, false)
		elseif keyCode == GameSettings.confirmKey then
			if self.currentMap then
				local response = self.currentMap:checkResponse()
				if response then
					ResponseController:processResponse(response)
				end
			end
		elseif keyCode == GameSettings.cancelKey then
			self.isCancelKeyPressed = true
		end
	elseif eventType == Enumerations.KEYBOARD_STATE.RELEASED then
		if keyCode == GameSettings.upKey or keyCode == GameSettings.downKey or keyCode == GameSettings.leftKey or keyCode == GameSettings.rightKey then
			--cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.walkSchedulerEntry)
			local hasDirectionKey = false
			for _, pressedKey in ipairs(pressedKeys) do
				if pressedKey == GameSettings.upKey or pressedKey == GameSettings.downKey or pressedKey == GameSettings.leftKey or pressedKey == GameSettings.rightKey then
					hasDirectionKey = true
					break
				end
			end
			self.isDirectionKeyPressed = hasDirectionKey
			if not hasDirectionKey then
				self.currentMap.hero:changeDirection(DataCenter.currentPlayerData.currentDirection)
			end
		elseif keyCode == GameSettings.cancelKey then
			self.isCancelKeyPressed = false
		end
	elseif eventType == Enumerations.KEYBOARD_STATE.LONGPRESSED then
		if self.isDirectionKeyPressed then
			if self.isCancelKeyPressed then
				self.currentMap:heroRun(self.nextDirection, MakeScriptHandler(self, self.turnBackStandState))
			else
				self.currentMap:heroWalk(self.nextDirection)
			end
		end
	end
end

function MapLayerController:handleDirectionEvents()
	log("MapLayerController:handleDirectionEvents")
	if self.isDirectionKeyPressed then
		local hero = self.currentMap.hero
		if self.isCancelKeyPressed then
			self.currentMap:heroRun(self.nextDirection, MakeScriptHandler(self, self.turnBackStandState))
		else
			if not self.currentMap:isHeroMoving() and DataCenter.currentPlayerData.currentDirection ~= self.nextDirection then
				hero:changeDirection(self.nextDirection)
				DataCenter.currentPlayerData.currentDirection = self.nextDirection
			else
				self.currentMap:heroWalk(self.nextDirection)
			end
		end
	end
end

-- 跑步完后 将状态设回站立
function MapLayerController:turnBackStandState()
	if not self.isCancelKeyPressed or not self.isDirectionKeyPressed then
		self.currentMap.hero:changeDirection(DataCenter.currentPlayerData.currentDirection)
		-- local frameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. DataCenter.currentPlayerData:getDirectionString() .. "1.png"
		-- local frame = cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName)
		-- self.currentMap.hero:setSpriteFrame(frame)
	end
end

function MapLayerController:switchMap(newMapId)
	self.isEnabled = false
	local coreLayer = self:getScene():getCoreLayer()

	if self.currentMap and self.currentMap.mapInfo.id == newMapId then
		self.currentMap:setVisible(true)
	else
		-- 记录新地图id
		DataCenter.currentPlayerData.currentMapId = newMapId

		if self.currentMap then
			-- self.currentMap:setVisible(false)
			coreLayer:popLayer()
		end

		CallFunctionAsync(self, self.switchMapCallFunc, 0.25, newMapId)
	end
	--coreLayer:pushLayer(newMap)
end
function MapLayerController:switchMapCallFunc(newMapId)
	local coreLayer = self:getScene():getCoreLayer()

	local newMapInfo = MapInfo:create(newMapId)
	local newMap = TMXMapLayer:createWithMapInfo(newMapInfo)
		
	self.currentMap = newMap
	self.currentMap:retain()
	CallFunctionAsync(coreLayer, function() 
			coreLayer:pushLayer(newMap) 
			newMap:release()
			-- 检测当前位置是否有剧情触发
			local trigger = newMap:checkTrigger(DataCenter.currentPlayerData.currentPosition)
			if trigger then
				newMap:continueStory(trigger)
			end
			self.isEnabled = true
			-- 显示地图名
			if newMapInfo.name ~= DBNULL then
				log("Map name: ", newMapInfo.name)
				local board = MapNameBoard:create(newMapInfo.name)
				board:setAnchorPoint(0, 0)
				board:setPosition(0, cc.Director:getInstance():getWinSize().height)
				coreLayer:addChild(board)
			end
		end, 0.25)
end

function MapLayerController:onMapStateChanged(oldState, newState)
	if oldState == Enumerations.MAP_STATE.INFO and newState == Enumerations.MAP_STATE.MENU then
		if self.menuLayerController then
			self:getScene():addChild(self.menuLayerController.root)
			self.menuLayerController.root:release()
		end
	elseif oldState ~= Enumerations.MAP_STATE.MENU and newState == Enumerations.MAP_STATE.FREEDOM then
		self.menuLayerController = MenuLayerController:create()
		self:getScene():loadViewController(self.menuLayerController)
	elseif newState == Enumerations.MAP_STATE.DIALOG then
		if self.menuLayerController then
			self:getScene():unloadViewController(self.menuLayerController)
		end
	elseif newState == Enumerations.MAP_STATE.INFO then
		if self.menuLayerController then
			self.menuLayerController.root:retain()
			self:getScene():removeChild(self.menuLayerController.root, false)
		end
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
	self:switchMap(mapId)
	CallFunctionAsync(self, self.endAction, 0.5)
end

function MapLayerController:action_WalkOut(params)
	local target = self:doWalkInstructions(params)

	Notifier:addObserver(NotifyEvents.MapView.ActionInstructionsEnded, self, self.onWalkOutEnd, target)
end

function MapLayerController:action_SwitchMap(params)
	local newMapId = tonumber(params)
	self:switchMap(newMapId)
	CallFunctionAsync(self, self.endAction, 0.5)
end

function MapLayerController:action_Walk(params)
	self:doWalkInstructions(params)

	Notifier:addObserver(NotifyEvents.MapView.ActionInstructionsEnded, self, self.onWalkEnd)
end

function MapLayerController:action_PopMessage(params)
	local tip = MessageTip:create(params, function()
		CallFunctionAsync(self, self.endAction, 0.5)
	end)
	tip:pop()
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

function MapLayerController:doWalkInstructions(params)
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

	return target
end

function MapLayerController:onWalkOutEnd(target)
	log("MapLayerController:onWalkOutEnd", target)
	Notifier:removeObserver(NotifyEvents.MapView.ActionInstructionsEnded, self)
	if target == 0 then
		self.currentMap.hero:removeFromParent()
	end

	CallFunctionAsync(self, self.endAction, 0.5)
end

function MapLayerController:onWalkEnd()
	Notifier:removeObserver(NotifyEvents.MapView.ActionInstructionsEnded, self)
	CallFunctionAsync(self, self.endAction, 0.5)
end