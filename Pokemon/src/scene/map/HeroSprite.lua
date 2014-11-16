--[[
	Description: Hero Sprite
	Author: M.Wan
	Date: 06/25/2014
]]

class("HeroSprite", psSprite)

-- walk actions
HeroSprite.walkUpWithLeftStepAction = nil
HeroSprite.walkUpWithRightStepAction = nil
HeroSprite.walkDownWithLeftStepAction = nil
HeroSprite.walkDownWithRightStepAction = nil
HeroSprite.walkLeftWithLeftStepAction = nil
HeroSprite.walkLeftWithRightStepAction = nil
HeroSprite.walkRightWithLeftStepAction = nil
HeroSprite.walkRightWithRightStepAction = nil
-- run actions
HeroSprite.runUpWithLeftStepAction = nil
HeroSprite.runUpWithRightStepAction = nil
HeroSprite.runDownWithLeftStepAction = nil
HeroSprite.runDownWithRightStepAction = nil
HeroSprite.runLeftWithLeftStepAction = nil
HeroSprite.runLeftWithRightStepAction = nil
HeroSprite.runRightWithLeftStepAction = nil
HeroSprite.runRightWithRightStepAction = nil

HeroSprite.isLeftStep = nil		-- 是否是左脚起步

-- const
HeroSprite.WALK_DURATION = 0.25
HeroSprite.RUN_DURATION = 0.1

HeroSprite.__createWithSpriteFrameName = psSprite.createWithSpriteFrameName

function HeroSprite:createWithSpriteFrameName(...)
	local hero = HeroSprite:__createWithSpriteFrameName(...)
	hero:init()

	return hero
end

function HeroSprite:createWithModel(heroObj)
	local heroFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. DataCenter.currentPlayerData:getDirectionString() .. "1.png"
	local hero = HeroSprite:createWithSpriteFrameName(heroFrameName)
	hero:init()

	return hero
end

function HeroSprite:init()
	-- animations initialization
	self.walkUpWithLeftStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.UP, true)
	self.walkUpWithLeftStepAction:retain()
	self.walkUpWithRightStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.UP, false)
	self.walkUpWithRightStepAction:retain()
	self.walkDownWithLeftStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.DOWN, true)
	self.walkDownWithLeftStepAction:retain()
	self.walkDownWithRightStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.DOWN, false)
	self.walkDownWithRightStepAction:retain()
	self.walkLeftWithLeftStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.LEFT, true)
	self.walkLeftWithLeftStepAction:retain()
	self.walkLeftWithRightStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.LEFT, false)
	self.walkLeftWithRightStepAction:retain()
	self.walkRightWithLeftStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.RIGHT, true)
	self.walkRightWithLeftStepAction:retain()
	self.walkRightWithRightStepAction = self:createWalkStepAction(Enumerations.DIRECTIONS.RIGHT, false)
	self.walkRightWithRightStepAction:retain()

	self.runUpWithLeftStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.UP, true)
	self.runUpWithLeftStepAction:retain()
	self.runUpWithRightStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.UP, false)
	self.runUpWithRightStepAction:retain()
	self.runDownWithLeftStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.DOWN, true)
	self.runDownWithLeftStepAction:retain()
	self.runDownWithRightStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.DOWN, false)
	self.runDownWithRightStepAction:retain()
	self.runLeftWithLeftStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.LEFT, true)
	self.runLeftWithLeftStepAction:retain()
	self.runLeftWithRightStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.LEFT, false)
	self.runLeftWithRightStepAction:retain()
	self.runRightWithLeftStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.RIGHT, true)
	self.runRightWithLeftStepAction:retain()
	self.runRightWithRightStepAction = self:createRunStepAction(Enumerations.DIRECTIONS.RIGHT, false)
	self.runRightWithRightStepAction:retain()

	self.isLeftStep = true

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function HeroSprite:createWalkStepAction(direction, isLeftStep, shouldMove)
	if shouldMove == nil then
		shouldMove = true
	end

	local frames = {}
	local frameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_"
	local dirStr, dirVec = nil, nil
	if direction == Enumerations.DIRECTIONS.UP then
		dirStr = "up"
		dirVec = ccp(0, 32)
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		dirStr = "down"
		dirVec = ccp(0, -32)
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		dirStr = "left"
		dirVec = ccp(-32, 0)
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		dirStr = "right"
		dirVec = ccp(32, 0)
	else
		assert(false, "Unavailable direction")
	end
	frameName = frameName .. dirStr

	if isLeftStep then
		table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 2 .. ".png"))
	else
		table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 3 .. ".png"))
	end
	table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 1 .. ".png"))
	local animation = cc.Animation:createWithSpriteFrames(frames, self.WALK_DURATION)
	if shouldMove then
		return cc.Spawn:create(
			cc.Animate:create(animation),
			cc.MoveBy:create(self.WALK_DURATION * 2, dirVec)
			)
	else
		return cc.Animate:create(animation)
	end
end

function HeroSprite:createRunStepAction(direction, isLeftStep, shouldMove)
	if shouldMove == nil then
		shouldMove = true
	end

	local frames = {}
	local frameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_run_"
	local dirStr, dirVec = nil, nil
	if direction == Enumerations.DIRECTIONS.UP then
		dirStr = "up"
		dirVec = ccp(0, 32)
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		dirStr = "down"
		dirVec = ccp(0, -32)
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		dirStr = "left"
		dirVec = ccp(-32, 0)
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		dirStr = "right"
		dirVec = ccp(32, 0)
	else
		assert(false, "Unavailable direction")
	end
	frameName = frameName .. dirStr

	if isLeftStep then
		table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 2 .. ".png"))
	else
		table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 3 .. ".png"))
	end
	table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 1 .. ".png"))
	local animation = cc.Animation:createWithSpriteFrames(frames, self.RUN_DURATION)
	if shouldMove then
		return cc.Spawn:create(
			cc.Animate:create(animation),
			cc.MoveBy:create(self.RUN_DURATION * 2, dirVec)
			)
	else
		return cc.Animate:create(animation)
	end
end

function HeroSprite:onNodeEvent(event)
	if event == "exit" then
		-- release actions
		self.walkUpWithLeftStepAction:release()
		self.walkUpWithRightStepAction:release()
		self.walkDownWithLeftStepAction:release()
		self.walkDownWithRightStepAction:release()
		self.walkLeftWithLeftStepAction:release()
		self.walkLeftWithRightStepAction:release()
		self.walkRightWithLeftStepAction:release()
		self.walkRightWithRightStepAction:release()

		self.runUpWithLeftStepAction:release()
		self.runUpWithRightStepAction:release()
		self.runDownWithLeftStepAction:release()
		self.runDownWithRightStepAction:release()
		self.runLeftWithLeftStepAction:release()
		self.runLeftWithRightStepAction:release()
		self.runRightWithLeftStepAction:release()
		self.runRightWithRightStepAction:release()
	end
end

function HeroSprite:getWalkAction(direction)
	local beginAction = nil
	if direction == Enumerations.DIRECTIONS.UP then
		if self.isLeftStep then
			beginAction = self.walkUpWithLeftStepAction
		else
			beginAction = self.walkUpWithRightStepAction
		end
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		if self.isLeftStep then
			beginAction = self.walkDownWithLeftStepAction
		else
			beginAction = self.walkDownWithRightStepAction
		end
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		if self.isLeftStep then
			beginAction = self.walkLeftWithLeftStepAction
		else
			beginAction = self.walkLeftWithRightStepAction
		end
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		if self.isLeftStep then
			beginAction = self.walkRightWithLeftStepAction
		else
			beginAction = self.walkRightWithRightStepAction
		end
	end

	return cc.Sequence:create(
		beginAction,
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
end

function HeroSprite:getRunAction(direction)
	local beginAction = nil
	if direction == Enumerations.DIRECTIONS.UP then
		if self.isLeftStep then
			beginAction = self.runUpWithLeftStepAction
		else
			beginAction = self.runUpWithRightStepAction
		end
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		if self.isLeftStep then
			beginAction = self.runDownWithLeftStepAction
		else
			beginAction = self.runDownWithRightStepAction
		end
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		if self.isLeftStep then
			beginAction = self.runLeftWithLeftStepAction
		else
			beginAction = self.runLeftWithRightStepAction
		end
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		if self.isLeftStep then
			beginAction = self.runRightWithLeftStepAction
		else
			beginAction = self.runRightWithRightStepAction
		end
	end

	return cc.Sequence:create(
		beginAction,
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
end

function HeroSprite:getWalkActionWithoutMoving(direction)
	local stepAction = self:createWalkStepAction(direction, self.isLeftStep, false)
	return cc.Sequence:create(
		stepAction,
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
end

function HeroSprite:onMovingEnded()
	log("HeroSprite:onMovingEnded")
	self.isLeftStep = not self.isLeftStep
end

function HeroSprite:getNextPosition(direction)
	local curPos = DataCenter.currentPlayerData.currentPosition
	local nextPos = ccp(curPos.x, curPos.y)
	if direction == Enumerations.DIRECTIONS.UP then
		nextPos.y = nextPos.y + 1
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		nextPos.y = nextPos.y - 1
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		nextPos.x = nextPos.x - 1
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		nextPos.x = nextPos.x + 1
	else
		assert(false, "Inavailable direction.")
	end

	return nextPos
end

function HeroSprite:changeDirection(newDirection, bForce)
	if DataCenter.currentPlayerData.currentDirection == newDirection and not bForce then
		return
	end
	-- log("Hero change direction to [" .. (newDirection or "nil") .. "]")

	local directionStr = nil
	if newDirection == Enumerations.DIRECTIONS.UP then
		directionStr = "up"
	elseif newDirection == Enumerations.DIRECTIONS.DOWN then
		directionStr = "down"
	elseif newDirection == Enumerations.DIRECTIONS.LEFT then
		directionStr = "left"
	elseif newDirection == Enumerations.DIRECTIONS.RIGHT then
		directionStr = "right"
	else
		assert(false, "Invalid direction.")
		return
	end

	DataCenter.currentPlayerData.currentDirection = newDirection
	local newFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. directionStr .. "1.png"
	local newFrame = cc.SpriteFrameCache:getInstance():getSpriteFrame(newFrameName)
	self:setSpriteFrame(newFrame)
end