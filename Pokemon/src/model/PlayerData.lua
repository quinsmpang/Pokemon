--[[
	Description: All info of player, to be used in saving data.
	Author: M.Wan
	Date: 06/20/2014
]]

luaClass("PlayerData", psModel)

PlayerData.id = nil				-- id
PlayerData.gender = nil			-- 性别
PlayerData.name = nil			-- 名字
PlayerData.currentMapId = nil	-- 所在地图的id
PlayerData.currentPosition = nil	-- 所在位置的坐标
PlayerData.currentDirection	= nil	-- 当前面朝的方向
PlayerData.lastStep = nil		-- 剧情发生到的step
PlayerData.currentStep = nil	-- 当前正在发生的剧情step

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

function PlayerData:initNewGameData(gender)
	self.id = 111
	self.gender = gender
	self.name = NAMES[gender]

	self.currentMapId = 1
	self.currentPosition = ccp(6, 6)
	self.currentDirection = Enumerations.DIRECTIONS.UP
	self.lastStep = -1
	self.currentStep = 1
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