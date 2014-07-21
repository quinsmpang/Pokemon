--[[
	Description: map layer, to load tmx map file
	Author: M.Wan
	Date: 05/29/2014
]]

class("TMXMapLayer", psGameLayer)

require "src/view/map/HeroSprite"
require "src/view/map/NpcSprite"

TMXMapLayer.mapInfo = nil 		-- MapInfo model
TMXMapLayer.width = nil
TMXMapLayer.height = nil

-- ui
TMXMapLayer.mask = nil 			-- 遮罩层用来实现Fade效果
TMXMapLayer.map = nil 			-- map root layer
TMXMapLayer.playerLayer = nil	-- player layer
TMXMapLayer.npcLayer = nil		-- npc layer
TMXMapLayer.main = nil			-- main layer
TMXMapLayer.tops = nil			-- layer whose items can cover the player
TMXMapLayer.hero = nil 			-- 玩家精灵
TMXMapLayer.npcList = nil 		-- NPC sprite集合

-- logic
TMXMapLayer.tiles = nil 			-- 二维数组
TMXMapLayer.obstacleList = nil		-- 障碍物(Obstacle model)集合
TMXMapLayer.entranceList = nil		-- 入口出口(Entrance model)集合
TMXMapLayer.triggerList = nil 		-- 剧情触发点(Trigger model)集合
TMXMapLayer.instructions = nil 		-- 行走指令队列，一般在剧情中的行走才需要用到
TMXMapLayer.isMoving = nil 			-- 是否在行走，自由行走的时候需要用到
TMXMapLayer.isRunning = nil 		-- 是否在跑
TMXMapLayer.upConcat = nil

-- const
TMXMapLayer.PLAYER_POS = ccp(384, 224)
TMXMapLayer.TILE_SIZE = 32
TMXMapLayer.ZORDER = {
	MAIN = 0,
	PLAYER = 100,
	HIGH_ITEMS = 101,
	MASK = 999,
}

-- treat as static method
function TMXMapLayer:createWithMapInfo(mapInfo)
	-- 本身无法修改opacity, 只好借助一个遮罩层来模拟FadeIn和FadeOut的效果
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setCascadeOpacityEnabled(true)
	mask:retain()
	local mapLayer = TMXMapLayer:createWithTransitions(
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15))
		)
	mapLayer.mask = mask
	mapLayer:initWithMapInfo(mapInfo)

	return mapLayer
end

function TMXMapLayer:initWithMapInfo(mapInfo)
	self.mapInfo = mapInfo
	self.isMoving = false
	self.isRunning = false

	local screenSize = cc.Director:getInstance():getWinSize()

	local map = EncryptedTMXTiledMap:create(mapInfo.path)
	self.map = map

	self.width = map:getMapSize().width
	self.height = map:getMapSize().height

	map:setAnchorPoint(0.5, 0.5)
	map:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	self:addChild(map, self.ZORDER.MAIN)

	-- main layer must be exist
	self.main = map:getLayer("main")
	self.main:setLocalZOrder(self.ZORDER.MAIN)
	-- top items layer
	self.tops = map:getLayer("tops")
	if self.tops then
		self.tops:setLocalZOrder(self.ZORDER.HIGH_ITEMS)
	end

	self.playerLayer = cc.Layer:create()
	map:addChild(self.playerLayer, self.ZORDER.PLAYER)
	self.npcLayer = cc.Layer:create()
	map:addChild(self.npcLayer, self.ZORDER.PLAYER)

	self.tiles = {}
	-- 判断地图是否拥有npc
	log("Map Initialization: Loading npc")
	self.npcList = {}
	local npcObjectGroup = map:getObjectGroup("npcObjects")
	if npcObjectGroup then
		-- 遍历生成npc
		local npcObjects = npcObjectGroup:getObjects()
		for _, npcObj in ipairs(npcObjects) do
			if tonumber(npcObj["step"]) == DataCenter.currentPlayerData.currentStep or tonumber(npcObj["step"]) == 0 then
				local npcModel = NPC:create(npcObj)
				for i = 0, npcModel.width - 1 do
					for j = 0, npcModel.height - 1 do
						self.tiles[npcModel.position.x + i .. "," .. npcModel.position.y + j] = npcModel
					end
				end
				local npc = NpcSprite:createWithModel(npcModel)
				local npcPos = ccp(tonumber(npcObj["x"]), tonumber(npcObj["y"]))
				npc:setAnchorPoint(0, 0)
				npc:setPosition(npcPos)
				table.insert(self.npcList, npc)
				self.npcLayer:addChild(npc)
				npcModel.__sprite = npc
			end
		end
	end

	-- 设置障碍物
	log("Map Initialization: Loading obstacles")
	self.obstacleList = {}
	local obstacleObejctGroup = map:getObjectGroup("obstacleObjects")
	if obstacleObejctGroup then
		-- 遍历放到障碍物table中
		local obstacleObjects = obstacleObejctGroup:getObjects()
		for _, obstacleObj in ipairs(obstacleObjects) do
			local obstacleModel = Obstacle:create(obstacleObj)
			table.insert(self.obstacleList, obstacleModel)
			for i = 0, obstacleModel.width - 1 do
				for j = 0, obstacleModel.height - 1 do
					self.tiles[obstacleModel.position.x + i .. "," .. obstacleModel.position.y + j] = obstacleModel
				end
			end
		end
	end

	-- 设置入口
	log("Map Initialization: Loading entrances")
	self.entranceList = {}
	local entranceObjectGroup = map:getObjectGroup("entranceObjects")
	if entranceObjectGroup then
		-- 遍历放到入口table中
		local entranceObjects = entranceObjectGroup:getObjects()
		for _, entranceObj in ipairs(entranceObjects) do
			local entranceModel = Entrance:create(entranceObj)
			table.insert(self.entranceList, entranceModel)
			for i = 0, entranceModel.width - 1 do
				for j = 0, entranceModel.height - 1 do
					self.tiles[entranceModel.position.x + i .. "," .. entranceModel.position.y + j] = entranceModel
				end
			end
		end
	end

	-- 设置剧情触发点
	log("Map Initialization: Loading triggers")
	self.triggerList = {}
	local triggerObjectGroup = map:getObjectGroup("triggerObjects")
	if triggerObjectGroup then
		-- 遍历放到触发点table中
		local triggerObjects = triggerObjectGroup:getObjects()
		for _, triggerObj in ipairs(triggerObjects) do
			local triggerModel = Trigger:create(triggerObj)
			table.insert(self.triggerList, triggerModel)
		end
	end

	-- 如果当前是非活动状态，说明是剧情载入，则显示在剧情设定位置
	log("Map Initialization: Loading hero")
	DataCenter.currentPlayerData.currentMapId = mapInfo.id
	if DataCenter.currentPlayerData.currentStep ~= 0 then
		local heroObjectGroup = map:getObjectGroup("heroObjects")
		local heroObjects = heroObjectGroup:getObjects()
		for _, heroObj in ipairs(heroObjects) do
			if tonumber(heroObj["step"]) == DataCenter.currentPlayerData.currentStep then
				-- 如果有性别区分的话
				local shouldSkip = false
				if heroObj["gender"] then
					local gender = tonumber(heroObj["gender"])
					if gender ~= DataCenter.currentPlayerData.gender then
						-- 性别不同则跳过
						shouldSkip = true
					end
				end
				if not shouldSkip then
					DataCenter.currentPlayerData.currentDirection = tonumber(heroObj["direction"])
					local hero = HeroSprite:createWithModel(heroObj)
					local pos = ccp(tonumber(heroObj["x"]), tonumber(heroObj["y"]))
					DataCenter.currentPlayerData:updatePosition(ccp(tonumber(heroObj["x"]) / self.TILE_SIZE, tonumber(heroObj["y"]) / self.TILE_SIZE))
					hero:setAnchorPoint(0, 0)
					hero:setPosition(pos)
					self.playerLayer:addChild(hero)
					self.hero = hero
					break
				end
			end
		end
	else
		local heroFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. DataCenter.currentPlayerData:getDirectionString() .. "1.png"
		local hero = HeroSprite:createWithSpriteFrameName(heroFrameName)
		self.hero = hero
		hero:setAnchorPoint(0, 0)
		-- 通过入口切换
		if MapStateController:getEntranceMapId() then
			for _, entrance in ipairs(self.entranceList) do
				if entrance.relatedMapId == MapStateController:getEntranceMapId() then
					local entrancePos = entrance.position
					DataCenter.currentPlayerData:updatePosition(entrancePos)
					hero:setPosition(entrancePos.x * self.TILE_SIZE, entrancePos.y * self.TILE_SIZE)
					break
				end
			end
			MapStateController:setEntranceMapId(nil)
		else
			-- 说明是读取存档载入，直接显示在存档记录的位置
			hero:setPosition(DataCenter.currentPlayerData.currentPosition.x * self.TILE_SIZE, DataCenter.currentPlayerData.currentPosition.y * self.TILE_SIZE)
		end
		self.playerLayer:addChild(hero)
	end

	self:updatePlayerPosition()
	if self.mask then
		self:addChild(self.mask, self.ZORDER.MASK)
		self.mask:release()
	end
end

-- 玩家需要显示在地图的合适位置、室内则是正中央，室外需要保证地图不会越界
function TMXMapLayer:updatePlayerPosition()
	local heroWorldPos = self.hero:convertToWorldSpace(POINT_ZERO)
	local diffX = self.PLAYER_POS.x - heroWorldPos.x
	local diffY = self.PLAYER_POS.y - heroWorldPos.y

	local curPos = ccp(self:getPosition())
	if self.mapInfo:isInRoom() then
		self:setPosition(curPos.x + diffX, curPos.y + diffY)
	else
		local deltaX, deltaY = 0, 0
		local winSize = cc.Director:getInstance():getWinSize()
		local mapWorldPos = self.map:convertToWorldSpace(POINT_ZERO)
		-- 上下边界(只可能一边越界)
		if mapWorldPos.y + self.map:getContentSize().height * 0.5 < winSize.height then
			deltaY = winSize.height - (mapWorldPos.y + self.map:getContentSize().height * 0.5)
		elseif mapWorldPos.y - self.map:getContentSize().height * 0.5 > 0 then
			deltaY = self.map:getContentSize().height * 0.5 - mapWorldPos.y
		end
		-- 左右边界(只可能一边越界)
		if mapWorldPos.x + self.map:getContentSize().width * 0.5 < winSize.width then
			deltaX = winSize.width - (mapWorldPos.x + self.map:getContentSize().width * 0.5)
		elseif mapWorldPos.x - self.map:getContentSize().width * 0.5 > 0 then
			deltaX = self.map:getContentSize().width * 0.5 - mapWorldPos.x
		end
		self:setPosition(curPos.x + diffX + deltaX, curPos.y + diffY + deltaY)
	end
end

function TMXMapLayer:heroWalk(direction, callback)
	if self.isMoving then
		return
	end

	log("TMXMapLayer:heroWalk [" .. direction .. "]")

	if not self:validateLocation(direction) then
		return
	end

	local heroAction = self.hero:getWalkAction(direction)

	-- 地图是反方向移动
	local mapAction = nil
	if direction == Enumerations.DIRECTIONS.UP then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(0, -self.TILE_SIZE))
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(0, self.TILE_SIZE))
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(self.TILE_SIZE, 0))
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(-self.TILE_SIZE, 0))
	end

	local sequence = {}
	table.insert(sequence, cc.Spawn:create(
			cc.TargetedAction:create(self.hero, heroAction), 
			mapAction
			))
	if callback then
		table.insert(sequence, cc.CallFunc:create(callback))
	end
	table.insert(sequence, cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnd)))
	local action = cc.Sequence:create(sequence)

	self.isMoving = true
	self:runAction(action)
end

function TMXMapLayer:onMovingEnd()
	self.isMoving = false
end

function TMXMapLayer:heroRun(direction, callback)
	if self.isRunning then
		return
	end

	log("TMXMapLayer:heroRun [" .. direction .. "]")

	if not self:validateLocation(direction) then
		return
	end

	local heroAction = self.hero:getRunAction(direction)

	--地图反向运动
	local mapAction = nil
	if direction == Enumerations.DIRECTIONS.UP then
		mapAction = cc.MoveBy:create(HeroSprite.RUN_DURATION * 2, ccp(0, -self.TILE_SIZE))
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		mapAction = cc.MoveBy:create(HeroSprite.RUN_DURATION * 2, ccp(0, self.TILE_SIZE))
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		mapAction = cc.MoveBy:create(HeroSprite.RUN_DURATION * 2, ccp(self.TILE_SIZE, 0))
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		mapAction = cc.MoveBy:create(HeroSprite.RUN_DURATION * 2, ccp(-self.TILE_SIZE, 0))
	end

	local sequence = {}
	table.insert(sequence, cc.Spawn:create(
			cc.TargetedAction:create(self.hero, heroAction), 
			mapAction
			))
	if callback then
		table.insert(sequence, cc.CallFunc:create(callback))
	end
	table.insert(sequence, cc.CallFunc:create(MakeScriptHandler(self, self.onRunningEnd)))
	local action = cc.Sequence:create(sequence)

	self.isRunning = true
	self:runAction(action)
end

function TMXMapLayer:onRunningEnd()
	self.isRunning = false
end

function TMXMapLayer:validateLocation(direction)
	DataCenter.currentPlayerData.currentDirection = direction

	-- 检测当前位置是否是入口
	if self:checkEntrance(DataCenter.currentPlayerData.currentPosition) then
		self.hero:changeDirection(direction)
		return false
	end
	
	-- 验证下个位置
	if not self:validateHeroNextPosition(direction) then
		log("Hero walk: Next position is invalid.")
		local collisionAction = cc.Sequence:create(
			self.hero:getWalkActionWithoutMoving(direction),
			cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnd))
			)
		self.isMoving = true
		self.hero:runAction(collisionAction)
		return false
	end

	DataCenter.currentPlayerData.currentDirection = direction

	return true
end

function TMXMapLayer:heroWalkWithInstructions(sender, direction)
	log("TMXMapLayer:heroWalkWithInstructions [" .. direction .. "]")

	-- 设置hero移动后的位置
	local nextPos = self.hero:getNextPosition(direction)
	DataCenter.currentPlayerData:updatePosition(nextPos)
	if self.observers then
		self:updateObserversDirection(0)
	end

	local action = nil

	local heroAction = self.hero:getWalkAction(direction)

	-- 地图是反方向移动
	local mapAction = nil
	if direction == Enumerations.DIRECTIONS.UP then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(0, -self.TILE_SIZE))
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(0, self.TILE_SIZE))
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(self.TILE_SIZE, 0))
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		mapAction = cc.MoveBy:create(HeroSprite.WALK_DURATION * 2, ccp(-self.TILE_SIZE, 0))
	end

	action = cc.Spawn:create(
		cc.TargetedAction:create(self.hero, heroAction), 
		mapAction
		)

	-- 判断是否拥有下一个指令
	if type(self.instructions) == "table" and self.instructions:count() > 0 then
		local ins = self.instructions:front().data
		log("instructions found, execute next instruction.", ins[1], ins[2])
		local dir = ins[1]
		if ins[2] > 0 then
			ins[2] = ins[2] - 1
			if ins[2] <= 0 then
				-- 步数为0后，出队列
				self.instructions:dequeue()
				-- 如果队列为空，则将指令置空
				if self.instructions:empty() then
					self.instructions = nil
				end
			end
			action = cc.Sequence:create(
				action,
				cc.CallFunc:create(MakeScriptHandler(self, self.heroWalkWithInstructions, dir))
				)
		end
	else
		-- 清空观察的对象
		self.observers = nil
		-- 指令执行完毕的话，通知MapLayerController
		action = cc.Sequence:create(
			action, 
			cc.CallFunc:create(MakeScriptHandler(self, self.onHeroWalkInstructionsEnd))
			)
	end

	self:runAction(action)
end

-- 更新观察对象的方向
function TMXMapLayer:updateObserversDirection(targetId)
	if self.observers then
		local targetPos = nil
		if targetId == 0 then
			targetPos = DataCenter.currentPlayerData.currentPosition
		else
			local targetNpc = table.find(self.npcList, function(obj, seekId)
					return obj.model.id == seekId
				end, targetId)
			assert(targetNpc, "invalid target.")
			targetPos = targetNpc.model.position
		end

		-- target为hero
		for _, observer in ipairs(self.observers) do
			local targetNpc = table.find(self.npcList, function(obj, seekId)
					return obj.model.id == seekId
				end, observer)
			assert(targetNpc, "invalid observer.")
			local newDir = self:calculateObserverDirection(targetPos, targetNpc.model.position)
			if newDir then
				targetNpc:updateDirection(newDir)
			end
		end
	end
end

function TMXMapLayer:calculateObserverDirection(targetPosition, observerPosition)
	local diffX = targetPosition.x - observerPosition.x
	local diffY = targetPosition.y - observerPosition.y
	if math.abs(diffX) > math.abs(diffY) then
		if diffX < 0 then
			return Enumerations.DIRECTIONS.LEFT
		else
			return Enumerations.DIRECTIONS.RIGHT
		end
	elseif math.abs(diffX) < math.abs(diffY) then
		if diffY < 0 then
			return Enumerations.DIRECTIONS.DOWN
		else
			return Enumerations.DIRECTIONS.UP
		end
	end
	return nil
end

-- instruction { direction, steps }
function TMXMapLayer:setInstructions(instructions, observers)
	self.instructions = instructions

	self.observers = observers
end

function TMXMapLayer:onHeroWalkInstructionsEnd()
	Notifier:notify(NotifyEvents.MapView.ActionInstructionsEnded)
end

-- 验证玩家下个位置
function TMXMapLayer:validateHeroNextPosition(direction)
	local nextPos = self.hero:getNextPosition(direction)
	log("TMXMapLayer:validateHeroNextPosition", direction, nextPos.x, nextPos.y)
	if self:checkCollision(nextPos, true) then
		return false
	end
	DataCenter.currentPlayerData:updatePosition(nextPos)
	return true
end

-- 剧情触发点检测
function TMXMapLayer:checkTrigger(position)
	for _, trigger in ipairs(self.triggerList) do
		if PositionEquals(position, trigger.position) and DataCenter.currentPlayerData.lastStep == trigger.lastStep then
			return trigger
		end
	end
	return nil
end

function TMXMapLayer:continueStory(trigger)
	log("进入剧情触发点")
	DataCenter.currentPlayerData:enterStory()
	local actionId = trigger.action
	-- 如果有对应的action需要执行 则执行
	if actionId ~= DBNULL then
		-- 更新step
		DataCenter.currentPlayerData:setStep(trigger.step)
		local action = ActionInfo:create(actionId)
		ActionController:processAction(action)
	else
		-- 这里模拟一个空action结束，为了让DialogLayerController去generateNextDialog
		Notifier:notify(NotifyEvents.MapView.ActionEnded)
	end
end

-- 入口检测
function TMXMapLayer:checkEntrance(position)
	local entrance = self.tiles[position.x .. "," .. position.y]
	if entrance and entrance.__className == "Entrance" then
		if entrance.isEnabled and DataCenter.currentPlayerData.currentDirection == entrance.direction then
			log("到达入口, 当前地图[" .. self.mapInfo.id .. "] 关联地图[" .. entrance.relatedMapId .. "]")
			MapStateController:setEntranceMapId(self.mapInfo.id)
			Notifier:notify(NotifyEvents.MapView.SwitchMap, entrance.relatedMapId)
			return true
		end
	end
	return false
end

-- 检测移动过程中的碰撞
function TMXMapLayer:checkCollision(nextPosition, isHero)
	if not isHero then
		-- 检测与玩家的碰撞
		local heroPos = DataCenter.currentPlayerData.currentPosition
		if PositionEquals(nextPosition, heroPos) then
			log("与玩家发生碰撞")
			return true
		end
	end

	-- npc碰撞
	local npc = self.tiles[nextPosition.x .. "," .. nextPosition.y]
	if npc and npc.__className == "NPC" then
		log("与npc发生碰撞", npc.id)
		return true
	end

	-- 障碍物碰撞
	local obstacle = self.tiles[nextPosition.x .. "," .. nextPosition.y]
	if obstacle and obstacle.__className == "Obstacle" then
		log("与障碍物发生碰撞", obstacle.id)
		return true
	end

	-- 边界碰撞
	-- 没有名字的地图一定是不需要连接的。所以才需要进行碰撞检测
	if self.mapInfo.name == DBNULL then
		if nextPosition.x < 0 or nextPosition.x >= self.width or nextPosition.y < 0 or nextPosition.y >= self.height then
			log("边界碰撞")
			return true
		end
	end

	return false
end

function TMXMapLayer:checkResponse()
	local nextPos = self.hero:getNextPosition(DataCenter.currentPlayerData.currentDirection)

	-- npc
	local npc = self.tiles[nextPos.x .. "," .. nextPos.y]
	if npc and npc.__className == "NPC" and npc.responseId ~= -1 then
		-- 修改npc方向
		npc.__sprite:updateDirection((DataCenter.currentPlayerData.currentDirection - 1 + 2) % 4 + 1)
		-- 判断是否和性别相关
		if npc.specialResponseId ~= DBNULL then
			local params = string.split(npc.specialResponseId, ",")	-- { gender, responseId }
			local gender = tonumber(params[1])
			local responseId = tonumber(params[2])
			if gender ~= DataCenter.currentPlayerData.gender then
				return Response:create(responseId)
			end
		end
		return Response:create(npc.responseId)
	end

	-- 障碍物
	local obstacle = self.tiles[nextPos.x .. "," .. nextPos.y]
	if obstacle and obstacle.__className == "Obstacle" and obstacle.responseId ~= -1 then
		local response = Response:create(obstacle.responseId)
		return response
	end

	return nil
end

function TMXMapLayer:isHeroMoving()
	return self.isMoving
end

function TMXMapLayer:isHeroRunning()
	return self.isRunning
end