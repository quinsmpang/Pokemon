--[[
	Description: NPC Sprite
	Author: M.Wan
	Date: 06/25/2014
]]

class("NpcSprite", psSprite)

NpcSprite.id = nil
NpcSprite.model = nil

NpcSprite.isLeftStep = nil

NpcSprite.WALK_DURATION = 0.25

function NpcSprite:createWithModel(npcModel)
	local npcFrameName = "images/characters/" .. npcModel:getSpriteName() .. "_" .. npcModel:getDirectionString() .. "1.png"
	local npc = NpcSprite:createWithSpriteFrameName(npcFrameName)
	npc:initWithModel(npcModel)
	return npc
end

function NpcSprite:initWithModel(npcModel)
	self.model = npcModel
	self.id = npcModel.id

	self.isLeftStep = true
end

function NpcSprite:updatePosition(position)
	self.model.position = position
end

function NpcSprite:updateDirection(direction)
	self.model.direction = direction
	local frameName = "images/characters/" .. self.model:getSpriteName() .. "_" .. self.model:getDirectionString() .. "1.png"
	self:setSpriteFrame(frameName)
end

function NpcSprite:getNextPosition(direction)
	local curPos = self.model.position
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

function NpcSprite:getWalkAction(direction)
	local dirStr, dirVec
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

	local frameName = "images/characters/" .. self.model:getSpriteName() .. "_" .. dirStr
	local frames = { cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 1 .. ".png") }
	if self.isLeftStep then
		table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 2 .. ".png"))
	else
		table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 3 .. ".png"))
	end
	table.insert(frames, cc.SpriteFrameCache:getInstance():getSpriteFrame(frameName .. 1 .. ".png"))

	local animation = cc.Animation:createWithSpriteFrames(frames, self.WALK_DURATION)
	local action = cc.Spawn:create(
		cc.Animate:create(animation),
		cc.MoveBy:create(self.WALK_DURATION * 2, dirVec)
		)

	return cc.Sequence:create(
		action,
		cc.CallFunc:create(MakeScriptHandler(self, self.onMovingEnded))
		)
end
function NpcSprite:onMovingEnded()
	log("NpcSprite:onMovingEnded")
	self.isLeftStep = not self.isLeftStep
end