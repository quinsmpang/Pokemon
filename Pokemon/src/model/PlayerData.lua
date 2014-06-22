--[[
	Description: All info of player, to be used in saving data.
	Author: M.Wan
	Date: 06/20/2014
]]

luaClass("PlayerData", psModel)

PlayerData.id = nil				-- id
PlayerData.gender = nil			-- 性别
PlayerData.name = nil			-- 名字

-- const
local NAMES = {
	"小风",
	"小云",
}

function PlayerData:create(gender)
	local model = PlayerData:new()
	model.id = 111
	model.gender = gender
	model.name = NAMES[gender]

	return model
end

function PlayerData:getGenderString()
	if self.gender == Enumerations.GENDER.MALE then
		return "male"
	else
		return "female"
	end
end