--[[
	Description: Hero Sprite
	Author: M.Wan
	Date: 06/25/2014
]]

class("HeroSprite", psSprite)

function HeroSprite:createWithModel(heroObj)
	local heroFrameName = "images/characters/player_" .. DataCenter.currentPlayerData:getGenderString() .. "_walk_" .. DataCenter.currentPlayerData:getDirectionString() .. "1.png"
	local hero = HeroSprite:createWithSpriteFrameName(heroFrameName)
	return hero
end