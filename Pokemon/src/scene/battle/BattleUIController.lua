--[[
	Description: battle ui controller
	Author: M.Wan
	Date: 12/31/2014
]]

class("BattleUIController", psViewController)

BattleUIController.root = nil

function BattleUIController:load()
	log("BattleUIController:load")
	self:addObservers()
	self:renderView()
end

function BattleUIController:unload()
	log("BattleUIController:unload")
	self:removeObservers()
end

function BattleUIController:addObservers()

end

function BattleUIController:removeObservers()

end

function BattleUIController:renderView()
	log("BattleUIController:renderView")
	local winSize = cc.Director:getInstance():getWinSize()

	self.root = cc.Layer:create()
	self:getScene():addChild(self.root)

	local battleType = self:getScene():getIntAttribute("battle_type")
	local bgType = self:getScene():getIntAttribute("battle_bg_type")
	local fieldType = self:getScene():getIntAttribute("battle_field_type")
	log(string.format("Battle type: %d, Bg type: %d, Field type: %d", battleType, bgType, fieldType))

	-- init bg ui
	local bg = cc.Sprite:createWithSpriteFrameName("images/battle/battle_bg" .. battleType .. ".png")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.root:addChild(bg)

	local fieldFrameName = "images/battle/battle_field" .. fieldType .. ".png"
	local fieldPlayer = cc.Sprite:createWithSpriteFrameName(fieldFrameName)
	fieldPlayer:setPosition(winSize.width * 1.2, winSize.height * 0.3)
	self.root:addChild(fieldPlayer)
	local fieldEnemy = cc.Sprite:createWithSpriteFrameName(fieldFrameName)
	fieldEnemy:setPosition(winSize.width * -0.2, winSize.height * 0.7)
	self.root:addChild(fieldEnemy)
	if battleType == Enumerations.BATTLE_TYPE.WILD then
		-- 野生精灵对战 直接显示野生精灵
		local pokemonId = self:getScene():getIntAttribute("pokemon_id")
		local pokemonLevel = self:getScene():getIntAttribute("pokemon_level")

		-- 随机生成神奇宝贝
		local pokemonModel = Pokemon:create(pokemonId, pokemonLevel)
	elseif battleType == Enumerations.BATTLE_TYPE.TRAINER_1V1 then
		-- 训练师对战1v1
		local trainerId = self:getScene():getIntAttribute("trainer_id")
	elseif battleType == Enumerations.BATTLE_TYPE.TRAINER_2V2 then
		-- 训练师对战2v2
		local trainer1Id = self:getScene():getIntAttribute("trainer1_id")
		local trainer2Id = self:getScene():getIntAttribute("trainer2_id")
	end
end