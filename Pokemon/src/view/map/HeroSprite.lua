--[[
	Description: Hero Sprite
	Author: M.Wan
	Date: 06/25/2014
]]

class("HeroSprite", psSprite)

HeroSprite.walkUpWithLeftStepAction = nil
HeroSprite.walkUpWithRightStepAction = nil
HeroSprite.walkDownWithLeftStepAction = nil
HeroSprite.walkDownWithRightStepAction = nil
HeroSprite.walkLeftWithLeftStepAction = nil
HeroSprite.walkLeftWithRightStepAction = nil
HeroSprite.walkRightWithLeftStepAction = nil
HeroSprite.walkRightWithRightStepAction = nil
HeroSprite.runUpAction = nil
HeroSprite.runDownAction = nil
HeroSprite.runLeftAction = nil
HeroSprite.runRightAction = nil

HeroSprite.isLeftStep = nil		-- 是否是左脚起步

-- const
HeroSprite.WALK_DURATION = 0.25
HeroSprite.RUN_DURATION = 0.1

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

	self.isLeftStep = true

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function HeroSprite:createWalkStepAction(direction, isLeftStep)
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
	return cc.Spawn:create(
		cc.Animate:create(animation),
		cc.MoveBy:create(self.WALK_DURATION * 2, dirVec)
		)
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

function HeroSprite:onMovingEnded()
	log("HeroSprite:onMovingEnded")
	self.isLeftStep = not self.isLeftStep
end

function HeroSprite:getNextPosition(direction)
	local curPos = DataCenter.currentPlayerData.currentPosition
	if direction == Enumerations.DIRECTIONS.UP then
		curPos.y = curPos.y + 1
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		curPos.y = curPos.y - 1
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		curPos.x = curPos.x - 1
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		curPos.x = curPos.x + 1
	else
		assert(false, "Inavailable direction.")
	end

	return curPos
end