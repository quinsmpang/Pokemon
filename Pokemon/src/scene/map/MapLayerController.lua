--[[
	Description: map layer controller
	Author: M.Wan
	Date: 05/29/2014
]]

class("MapLayerController", psViewController)

require "src/scene/map/TMXMapLayer"
require "src/scene/map/MessageTip"
require "src/scene/map/MapNameBoard"
require "src/scene/map/MapMenuLayer"
require "src/scene/map/SaveGameLayer"

MapLayerController.root = nil
MapLayerController.currentMap = nil		-- 当前地图层
MapLayerController.mainMenu = nil		-- 主菜单

-- logic
MapLayerController.pressedDirectionKeys = nil
MapLayerController.nextDirection = nil
MapLayerController.playerState = nil
MapLayerController.scheduleHandle = nil		-- 游戏时间计时器

-- const
MapLayerController.KEYBOARD_DT = 0.25

MapLayerController.resources = {
	"images/characters.plist", 
	"images/characters.pvr.ccz",
}

local PLAYER_STATE = {
	STANDING = 0,	-- 站立状态
	WALKING = 1,	-- 行走
	RUNNING = 2,	-- 跑步
	BYCICLE = 3,	-- 自行车 
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
	Notifier:addObserver(NotifyEvents.MapView.MapUpdate, self, self.onMapUpdate)
	Notifier:addObserver(NotifyEvents.MapView.ShowEntranceMessage, self, self.onShowEntranceMessage)
	Notifier:addObserver(NotifyEvents.MapView.MenuItemSelected, self, self.onMenuItemSelected)
end

function MapLayerController:removeObservers()
	log("MapLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionBegan, self)
	Notifier:removeObserver(NotifyEvents.MapView.SwitchMap, self)
	Notifier:removeObserver(NotifyEvents.MapView.MapUpdate, self)
	Notifier:removeObserver(NotifyEvents.MapView.ShowEntranceMessage, self)
	Notifier:removeObserver(NotifyEvents.MapView.MenuItemSelected, self)

	Notifier:removeObserver(NotifyEvents.MapView.ActionInstructionsEnded, self)
end

function MapLayerController:renderView()
	self.pressedDirectionKeys = {}

	local coreLayer = self:getScene():getCoreLayer()

	self.root = cc.Layer:create()
	self.root:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
	coreLayer:addChild(self.root)

	local screenSize = cc.Director:getInstance():getWinSize()

	local playerData = DataCenter.currentPlayerData

	self:switchMap(playerData.currentMapId)

	-- main menu
	local mainMenu = MapMenuLayer:create()
	self:getScene():addChild(mainMenu)
	mainMenu:setVisible(false)
	self.mainMenu = mainMenu

	self.playerState = PLAYER_STATE.STANDING
end

function MapLayerController:onNodeEvent(event)
	if event == "enter" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self.root)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardReleased), pf.Handler.WIN32_KEYBOARD_UP)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		end

		self.scheduleHandle = cc.Director:getInstance():getScheduler():scheduleScriptFunc(MakeScriptHandler(self, self.onTimeTick), 1, false)
	elseif event == "exit" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
			self.kbdListener = nil
		end

		if self.scheduleHandle then
  			cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.scheduleHandle)
  			self.scheduleHandle = nil
  		end
	end
end

function MapLayerController:setEnabled(isEnabled)
	-- 控制键盘响应
	if self.kbdListener then
		self.kbdListener:setEnabled(isEnabled)
	end
end

-- used in TMXMapLayer's update scheduler
function MapLayerController:onMapUpdate(dt)
	if not self.currentMap then
		return
	end

	if DataCenter.currentPlayerData:isFreedom() then
		local hero = self.currentMap.hero
		-- log("Current state: ", self.playerState)
		if self.playerState == PLAYER_STATE.STANDING then
			if self.nextDirection then
				DataCenter.currentPlayerData.currentDirection = self.nextDirection
				self.nextDirection = nil
			end
			if not self.currentMap.isMoving then
				hero:changeDirection(DataCenter.currentPlayerData.currentDirection, true)
			end
		elseif self.playerState == PLAYER_STATE.WALKING then
			if self.nextDirection then
				DataCenter.currentPlayerData.currentDirection = self.nextDirection
				self.nextDirection = nil
			else
				self.currentMap:heroWalk(DataCenter.currentPlayerData.currentDirection)
			end
		elseif self.playerState == PLAYER_STATE.RUNNING then
			if self.nextDirection then
				DataCenter.currentPlayerData.currentDirection = self.nextDirection
				self.nextDirection = nil
			else
				self.currentMap:heroRun(DataCenter.currentPlayerData.currentDirection)
			end
		elseif self.playerState == PLAYER_STATE.BYCICLE then
		end
		self:checkPlayerState()
	end
end

function MapLayerController:onKeyboardPressed(keyCode)
	log("MapLayerController:onKeyboardPressed", keyCode)
	if not DataCenter.currentPlayerData:isFreedom() then
		return
	end
	-- log("MapLayerController:onKeyboardPressed", keyCode)
	if keyCode ~= GameSettings.upKey and keyCode ~= GameSettings.downKey and keyCode ~= GameSettings.leftKey and keyCode ~= GameSettings.rightKey
		and keyCode ~= GameSettings.confirmKey and keyCode ~= GameSettings.cancelKey and keyCode ~= GameSettings.startKey then
		return
	end

	-- 方向键处理
	if keyCode == GameSettings.upKey or keyCode == GameSettings.downKey or keyCode == GameSettings.leftKey or keyCode == GameSettings.rightKey then
		self.nextDirection = self:getDirectionByKeyCode(keyCode)
		table.insert(self.pressedDirectionKeys, keyCode)
	elseif keyCode == GameSettings.confirmKey then
		if self.currentMap then
			local response = self.currentMap:checkResponse()
			if response then
				self:resetHero()
				ResponseController:processResponse(response)
			end
		end
	elseif keyCode == GameSettings.startKey then
		-- 打开主菜单
		MapStateController:setCurrentState(Enumerations.MAP_STATE.MENU)
		self.mainMenu:validateAllItems()
		self.mainMenu:setVisible(true)
	end
	self:checkPlayerState()
end

function MapLayerController:resetHero(direction)
	direction = direction or DataCenter.currentPlayerData.currentDirection
	self.playerState = PLAYER_STATE.STANDING
	self.currentMap.hero:changeDirection(direction, true)
	self.nextDirection = nil
	self.pressedDirectionKeys = {}
end

function MapLayerController:onKeyboardReleased(keyCode)
	-- 方向键处理
	if keyCode == GameSettings.upKey or keyCode == GameSettings.downKey or keyCode == GameSettings.leftKey or keyCode == GameSettings.rightKey then
		table.erase(self.pressedDirectionKeys, function(key)
			return key == keyCode
		end, keyCode)
		if #self.pressedDirectionKeys > 0 then
			local latestKey = self.pressedDirectionKeys[#self.pressedDirectionKeys]
			self.nextDirection = self:getDirectionByKeyCode(latestKey)
		end
	end
	self:checkPlayerState()
end

function MapLayerController:checkPlayerState()
	if #self.pressedDirectionKeys > 0 then
		if KeyboardHelper:getInstance():isKeyPressed(GameSettings.cancelKey) then
			self.playerState = PLAYER_STATE.RUNNING
		else
			self.playerState = PLAYER_STATE.WALKING
		end
	else
		self.playerState = PLAYER_STATE.STANDING
	end
end

function MapLayerController:getDirectionByKeyCode(keyCode)
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
		assert(false, "Invalid direction")
	end

	return nextDir
end

function MapLayerController:switchMap(newMapId, lastMapId)
	self.nextDirection = nil
	self.playerState = PLAYER_STATE.STANDING
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

		CallFunctionAsync(self, self.switchMapCallFunc, 0.25, newMapId, lastMapId)
	end
	--coreLayer:pushLayer(newMap)
end
function MapLayerController:switchMapCallFunc(newMapId, lastMapId)
	local coreLayer = self:getScene():getCoreLayer()

	local newMapInfo = MapInfo:create(newMapId)
	local newMap = TMXMapLayer:createWithMapInfo(newMapInfo, lastMapId)
		
	self.currentMap = newMap
	self.currentMap:retain()
	CallFunctionAsync(coreLayer, function() 
			coreLayer:pushLayer(newMap) 
			newMap:release()
			-- 检测当前位置是否有剧情触发
			local trigger = newMap:checkTrigger(DataCenter.currentPlayerData.currentPosition)
			if trigger then
				self.nextDirection = nil
				self.playerState = PLAYER_STATE.STANDING
				newMap:continueStory(trigger)
			end
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

function MapLayerController:onShowEntranceMessage(message)
	local reverseDirection = (DataCenter.currentPlayerData.currentDirection + 2) % 4
	self.playerState = PLAYER_STATE.STANDING
	self.currentMap:heroWalk(reverseDirection, function()
			self:resetHero()
			local response = Response:simulate(DBNULL, message)
			ResponseController:processResponse(response)
		end)
end

function MapLayerController:onMenuItemSelected(item)
	if item.__isEnabled then
		GameVolumeHelper:playBtnClickSound()
		local itemIndex = item:getShowIndex()
		if itemIndex == 0 then
			--图鉴
		elseif itemIndex == 1 then
			--精灵
			require "src/scene/pokemon/PokemonViewController"

			local pokemonViewController = PokemonViewController:create()
			-- send enter type (view pokemon)
			self:getScene():putIntAttribute(GameConfig.POKEMON_KEY, 1)
			self:getScene():loadViewController(pokemonViewController)
		elseif itemIndex == 2 then
			--背包
		elseif itemIndex == 3 then
			--通讯器
		elseif itemIndex == 4 then
			--玩家
			if DEBUG then
				log("@@@@@@@@", DataCenter.currentPlayerData.lastStep)
			end
		elseif itemIndex == 5 then
			--记录
			local saveLayer = SaveGameLayer:create()
			self:getScene():addChild(saveLayer)
		elseif itemIndex == 6 then
			--设置
			if DEBUG then
				local pokemon = Pokemon:create(math.random(1, 649), math.random(1, 100), math.random(1, 3), 10001)
				if #DataCenter.carriedPokemons >= 6 then
					DataCenter.carriedPokemons[6] = pokemon
				else
					DataCenter:addNewPokemon(pokemon)
				end
			end
		elseif itemIndex == 7 then
			--退出
			self.mainMenu:exitMenu()
		end
	else
		GameVolumeHelper:playUnableSound()
	end
end

function MapLayerController:onTimeTick(dt)
	DataCenter.currentPlayerData.gameTime = DataCenter.currentPlayerData.gameTime + 1
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