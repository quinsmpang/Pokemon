--[[
	Description: map layer, to load tmx map file
	Author: M.Wan
	Date: 05/29/2014
]]

class("TMXMapLayer", psGameLayer)

require "src/view/map/HeroSprite"
require "src/view/map/NpcSprite"

TMXMapLayer.mapInfo = nil 		-- MapInfo model

-- ui
TMXMapLayer.mask = nil 			-- 遮罩层用来实现Fade效果
TMXMapLayer.playerLayer = nil	-- player layer
TMXMapLayer.npcLayer = nil		-- npc layer
TMXMapLayer.main = nil			-- main layer
TMXMapLayer.tops = nil			-- layer whose items can cover the player
TMXMapLayer.hero = nil 			-- 玩家精灵
TMXMapLayer.npcList = nil 		-- NPC sprite集合

-- logic
TMXMapLayer.obstacleList = nil		-- 障碍物(Obstacle model)集合
TMXMapLayer.entranceList = nil		-- 入口出口(Entrance model)集合
TMXMapLayer.instructions = nil 		-- 行走指令队列，一般在剧情中的行走才需要用到
TMXMapLayer.isMoving = nil 			-- 是否在行走，自由行走的时候需要用到

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
	self.mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	self.mask:setCascadeOpacityEnabled(true)
	self.mask:retain()
	local mapLayer = TMXMapLayer:createWithTransitions(
		cc.TargetedAction:create(self.mask, cc.FadeOut:create(0.25)),
		cc.TargetedAction:create(self.mask, cc.FadeOut:create(0.25)),
		cc.TargetedAction:create(self.mask, cc.FadeIn:create(0.25)),
		cc.TargetedAction:create(self.mask, cc.FadeIn:create(0.25))
		)
	-- local mapLayer = TMXMapLayer:create()

	mapLayer:initWithMapInfo(mapInfo)

	return mapLayer
end

function TMXMapLayer:initWithMapInfo(mapInfo)
	self.mapInfo = mapInfo
	self.isMoving = false

	local screenSize = cc.Director:getInstance():getWinSize()

	local map = EncryptedTMXTiledMap:create(mapInfo.path)
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
					DataCenter.currentPlayerData.currentPosition = ccp(tonumber(heroObj["x"]) / self.TILE_SIZE, tonumber(heroObj["y"]) / self.TILE_SIZE)
					hero:setAnchorPoint(0, 0)
					hero:setPosition(pos)
					self.playerLayer:addChild(hero)
					self.hero = hero
					break
				end
			end
		end
	else	-- 说明是读取存档载入，直接显示在存档记录的位置
		local heroFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. DataCenter.currentPlayerData:getDirectionString() .. "1.png"
		local hero = cc.Sprite:createWithSpriteFrameName(heroFrameName)
		hero:setAnchorPoint(0, 0)
		hero:setPosition(DataCenter.currentPlayerData.currentPosition.x * self.TILE_SIZE, DataCenter.currentPlayerData.currentPosition.y * self.TILE_SIZE)
		self.playerLayer:addChild(hero)
	end

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
				local npc = NpcSprite:createWithModel(npcModel)
				local npcPos = ccp(tonumber(npcObj["x"]), tonumber(npcObj["y"]))
				npc:setAnchorPoint(0, 0)
				npc:setPosition(npcPos)
				table.insert(self.npcList, npc)
				self.npcLayer:addChild(npc)
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
		end
	end

	self:updatePlayerPosition()
	self:addChild(self.mask, self.ZORDER.MASK)
	self.mask:release()
end

-- 玩家需要显示在地图中间
function TMXMapLayer:updatePlayerPosition()
	local heroLocalPos = ccp(self.hero:getPosition())
	local heroWorldPos = self.hero:convertToWorldSpace(POINT_ZERO)
	local diffX = self.PLAYER_POS.x - heroWorldPos.x
	local diffY = self.PLAYER_POS.y - heroWorldPos.y

	local curPos = ccp(self:getPosition())
	self:setPosition(curPos.x + diffX, curPos.y + diffY)
end

function TMXMapLayer:heroWalk(direction, callback)
	if self.isMoving then
		return
	end

	log("TMXMapLayer:heroWalk [" .. direction .. "]")

	-- 验证下个位置
	if not self:validateHeroNextPosition(direction) then
		log("Hero walk: Next position is invalid.")
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

function TMXMapLayer:validateHeroNextPosition(direction)
	log("TMXMapLayer:validateHeroNextPosition", direction)
	local nextPos = self.hero:getNextPosition(direction)
	if self:checkCollision(nextPos, true) then
		return false
	end
	DataCenter.currentPlayerData:updatePosition(nextPos)
	return true
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
	for _, npc in ipairs(self.npcList) do
		local npcPos = npc.model.position
		if PositionEquals(npcPos, nextPosition) then
			log("与npc发生碰撞")
			return true
		end
	end

	-- 障碍物碰撞
	for _, obstacle in ipairs(self.obstacleList) do
		local obstaclePos = obstacle.position
		if PositionEquals(obstaclePos, nextPosition) then
			log("与障碍物发生碰撞")
			return true
		end
	end

	return false
end

-- 检测移动后是否在入口或出口处
function TMXMapLayer:checkEntrance()
	local curPos = DataCenter.currentPlayerData.currentPosition

	for _, entrance in ipairs(self.entranceList) do
		if PositionEquals(entrance.position, curPos) then
			-- 切换地图
			DataCenter.currentPlayerData.currentMapId = entrance.relatedMapId
			Notifier:notify(NotifyEvents.MapView.SwitchMap, entrance.relatedMapId)
			break
		end
	end
end

function TMXMapLayer:isHeroMoving()
	return self.isMoving
end