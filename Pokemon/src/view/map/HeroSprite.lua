--[[
	Description: Hero Sprite
	Author: M.Wan
	Date: 06/25/2014
]]

class("HeroSprite", psSprite)

HeroSprite.walkUpAction = nil
HeroSprite.walkDownAction = nil
HeroSprite.walkLeftAction = nil
HeroSprite.walkRightAction = nil
HeroSprite.runUpAction = nil
HeroSprite.runDownAction = nil
HeroSprite.runLeftAction = nil
HeroSprite.runRightAction = nil

HeroSprite.isMoving = nil		-- 是否在移动

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
	local animation = CreateAnimation("images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_up", 3, self.WALK_DURATION)
	self.walkUpAction = cc.Sequence:create(
		cc.Spawn:create(
			animation,
			cc.MoveBy:create(self.WALK_DURATION * 3, ccp(0, 32))
			),
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
	self.walkUpAction:retain()
	animation = CreateAnimation("images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_down", 3, self.WALK_DURATION)
	self.walkDownAction = cc.Sequence:create(
		cc.Spawn:create(
			animation,
			cc.MoveBy:create(self.WALK_DURATION * 3, ccp(0, -32))
			),
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
	self.walkDownAction:retain()
	animation = CreateAnimation("images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_left", 3, self.WALK_DURATION)
	self.walkLeftAction = cc.Sequence:create(
		cc.Spawn:create(
			animation,
			cc.MoveBy:create(self.WALK_DURATION * 3, ccp(-32, 0))
			),
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
	self.walkLeftAction:retain()
	animation = CreateAnimation("images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_right", 3, self.WALK_DURATION)
	self.walkRightAction = cc.Sequence:create(
		cc.Spawn:create(
			animation,
			cc.MoveBy:create(self.WALK_DURATION * 3, ccp(32, 0))
			),
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
	self.walkRightAction:retain()

	self.isMoving = false

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function HeroSprite:onNodeEvent(event)
	if event == "exit" then
		-- release actions
		self.walkUpAction:release()
		self.walkDownAction:release()
		self.walkLeftAction:release()
		self.walkRightAction:release()
	end
end

-- 方向，步数
function HeroSprite:walk(direction)
	if self.isMoving then
		return
	end
	log("HeroSprite:walk, Direction: [" .. direction .. "]")

	self.isMoving = true
	if direction == Enumerations.DIRECTIONS.UP then
		self:runAction(self.walkUpAction)
	elseif direction == Enumerations.DIRECTIONS.DOWN then
		self:runAction(self.walkDownAction)
	elseif direction == Enumerations.DIRECTIONS.LEFT then
		self:runAction(self.walkLeftAction)
	elseif direction == Enumerations.DIRECTIONS.RIGHT then
		self:runAction(self.walkRightAction)
	end
end

function HeroSprite:onMovingEnded()
	log("HeroSprite:onMovingEnded")
	self.isMoving = false
end