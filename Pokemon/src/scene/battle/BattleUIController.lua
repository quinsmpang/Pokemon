--[[
	Description: battle ui controller
	Author: M.Wan
	Date: 12/31/2014
]]

class("BattleUIController", psViewController)

BattleUIController.root = nil
BattleUIController.fieldPlayer = nil
BattleUIController.fieldEnemy = nil
BattleUIController.enemyBoard = nil		-- 1v1

BattleUIController.wildPokemonModel = nil	-- wild 1v1

BattleUIController.battleType = nil
BattleUIController.bgType = nil
BattleUIController.fieldType = nil

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
	self.battleType = battleType
	self.bgType = bgType
	self.fieldType = fieldType
	log(string.format("Battle type: %d, Bg type: %d, Field type: %d", battleType, bgType, fieldType))

	-- init bg ui
	local bg = cc.Sprite:createWithSpriteFrameName("images/battle/battle_bg" .. battleType .. ".png")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.root:addChild(bg)

	-- fields init
	local fieldFrameName = "images/battle/battle_field" .. fieldType .. ".png"
	local fieldPlayer = cc.Sprite:createWithSpriteFrameName(fieldFrameName)
	fieldPlayer:setPosition(winSize.width * 1.3, winSize.height * 0.3)
	self.root:addChild(fieldPlayer)
	self.fieldPlayer = fieldPlayer
	local player = cc.Sprite:createWithSpriteFrameName("images/battle/battle_player" .. DataCenter.currentPlayerData.gender .. ".png")
	player:setAnchorPoint(0.5, 0)
	player:setPosition(fieldPlayer:getContentSize().width * 0.5, fieldPlayer:getContentSize().height * 0)
	player:setScale(1.4)
	fieldPlayer:addChild(player)
	local fieldEnemy = cc.Sprite:createWithSpriteFrameName(fieldFrameName)
	fieldEnemy:setPosition(winSize.width * -0.3, winSize.height * 0.7)
	self.root:addChild(fieldEnemy)
	self.fieldEnemy = fieldEnemy

	if battleType == Enumerations.BATTLE_TYPE.WILD then
		-- 野生精灵对战 直接显示野生精灵
		local pokemonId = self:getScene():getIntAttribute("pokemon_id")
		local pokemonLevel = self:getScene():getIntAttribute("pokemon_level")

		-- 随机生成神奇宝贝
		local pokemonModel = Pokemon:create(pokemonId, pokemonLevel)
		self.wildPokemonModel = pokemonModel

		self:beginBattleWild1v1(pokemonModel)
	elseif battleType == Enumerations.BATTLE_TYPE.TRAINER_1V1 then
		-- 训练师对战1v1
		local trainerId = self:getScene():getIntAttribute("trainer_id")
	elseif battleType == Enumerations.BATTLE_TYPE.TRAINER_2V2 then
		-- 训练师对战2v2
		local trainer1Id = self:getScene():getIntAttribute("trainer1_id")
		local trainer2Id = self:getScene():getIntAttribute("trainer2_id")
	end
end

function BattleUIController:beginBattleAnimation()
	local winSize = cc.Director:getInstance():getWinSize()

	local action = cc.Spawn:create(
		cc.TargetedAction:create(self.fieldPlayer, cc.MoveBy:create(3, ccp(-winSize.width, 0))),
		cc.TargetedAction:create(self.fieldEnemy, cc.MoveBy:create(3, ccp(winSize.width, 0)))
		)

	if self.battleType == Enumerations.BATTLE_TYPE.WILD then
		-- 显示遭遇精灵面板
		local enemyBoard = cc.Scale9Sprite:createWithSpriteFrameName("images/common/back_gray.png", CCRectMake(10, 10, 30, 30))
		enemyBoard:setPreferredSize(CCSizeMake(240, 64))
		enemyBoard:setPosition(winSize.width * -0.2, winSize.height * 0.85)
		self.root:addChild(enemyBoard)
		self.enemyBoard = enemyBoard

		local lblWildName = cc.Label:createWithTTF(self.wildPokemonModel.model.name, GameConfig.DEFAULT_FONT_PATH, 15)
		-- lblWildName:enableOutline(ccc4(0, 0, 0, 1), 4)
		lblWildName:setPosition(enemyBoard:getContentSize().width * 0.15, enemyBoard:getContentSize().height * 0.77)
		enemyBoard:addChild(lblWildName)

		action = cc.Sequence:create(
			action,
			cc.TargetedAction:create(enemyBoard, cc.MoveBy:create(0.8, ccp(winSize.width * 0.4, 0)))
			)
	end

	self.root:runAction(action)
end

function BattleUIController:beginBattleWild1v1(pokemonModel)
	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemons.rc", string.format("%03d.png", pokemonModel.id), GameConfig.ZIP_PASSWORD)
	local wildPokemon = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	wildPokemon:setScale(2)
	wildPokemon:setPosition(self.fieldEnemy:getContentSize().width * 0.5, self.fieldEnemy:getContentSize().height * 0.5)
	wildPokemon:setAnchorPoint(0.5, 0)
	self.fieldEnemy:addChild(wildPokemon)

	self:beginBattleAnimation()
end