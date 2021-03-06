--[[
	Description: All info of player, to be used in saving data.
	Author: M.Wan
	Date: 06/20/2014
]]

luaClass("PlayerData", psModel)

PlayerData.id = DBNULL				-- id
PlayerData.gender = DBNULL			-- 性别
PlayerData.name = DBNULL			-- 名字
PlayerData.currentMapId = DBNULL	-- 所在地图的id
PlayerData.currentPosition = DBNULL	-- 所在位置的坐标
PlayerData.currentDirection	= DBNULL	-- 当前面朝的方向
PlayerData.lastStep = DBNULL		-- 剧情发生到的step
PlayerData.currentStep = DBNULL		-- 当前正在发生的剧情step, 0表示自由活动
PlayerData.lastDialogId = DBNULL	-- 当前执行到的对话id
PlayerData.onBycicle = DBNULL		-- 是否在自行车上
PlayerData.gameTime = DBNULL		-- 游戏经历时间

-- const
local NAMES = {
	"小风",
	"小云",
}

function PlayerData:create(gender)
	local model = PlayerData:new()
	model:initNewGameData(gender)

	return model
end

function PlayerData:createWithLoadData(loadData)
	local model = PlayerData:new()
	table.shallowCopy(model, loadData)
	log("玩家UUID", model.id)

	return model
end

function PlayerData:initNewGameData(gender)
	self.id = UUIDGenerator:getInstance():generateUUID()
	self.gender = gender
	self.name = NAMES[gender + 1]

	self.currentMapId = 1
	self.currentPosition = ccp(6, 6)
	self.currentDirection = Enumerations.DIRECTIONS.UP
	self.lastStep = 0
	self.currentStep = 1
	self.onBycicle = false
	self.gameTime = 0
end

function PlayerData:getGenderString()
	if self.gender == Enumerations.GENDER.MALE then
		return "male"
	elseif self.gender == Enumerations.GENDER.FEMALE then
		return "female"
	end

	assert(false, "Invalid player gender")
end

function PlayerData:getDirectionString()
	if self.currentDirection == Enumerations.DIRECTIONS.UP then
		return "up"
	elseif self.currentDirection == Enumerations.DIRECTIONS.DOWN then
		return "down"
	elseif self.currentDirection == Enumerations.DIRECTIONS.LEFT then
		return "left"
	elseif self.currentDirection == Enumerations.DIRECTIONS.RIGHT then
		return "right"
	end

	assert(false, "Invalid player current direction")
end

function PlayerData:updatePosition(position)
	log("PlayerData:updatePosition: ", position.x, position.y)
	self.currentPosition = position
end

-- 进入自由活动
function PlayerData:enterFreedom(bUpdateStep)
	if type(bUpdateStep) == "nil" then
		bUpdateStep = true
	end
	log("PlayerData:enterFreedom", self.currentStep)
	if bUpdateStep then
		self.lastStep = self.currentStep
	end
	self.currentStep = 0
	MapStateController:setCurrentState(Enumerations.MAP_STATE.FREEDOM)
end

-- 进入剧情
function PlayerData:enterStory(bUpdateStep)
	log("PlayerData:enterStory", self.lastStep)
	self.currentStep = self.lastStep + 1
	MapStateController:setCurrentState(Enumerations.MAP_STATE.DIALOG)
end

function PlayerData:isFreedom()
	return self.currentStep == 0
end

function PlayerData:setStep(step)
	self.currentStep = step
end