--[[
	Description: battle ui controller
	Author: M.Wan
	Date: 12/31/2014
]]

class("BattleUIController", psViewController)

require "src/scene/battle/BattleLogicConstants"
require "src/scene/battle/EnemyPokemonBoard"
require "src/scene/battle/BattleStateMachine"

BattleUIController.root = nil
BattleUIController.fieldPlayer = nil
BattleUIController.fieldEnemy = nil
BattleUIController.enemyBoard = nil		-- 1v1
BattleUIController.player = nil
BattleUIController.playerPokemon = nil
BattleUIController.enemyPokemon = nil

BattleUIController.currentPokemonModel = nil
BattleUIController.wildPokemonModel = nil	-- wild 1v1

BattleUIController.battleType = nil
BattleUIController.bgType = nil
BattleUIController.fieldType = nil

BattleUIController.WILD1V1_PREPARE_DIALOGS = {
	"WILD_POKEMON_OCCUR",
	"CHANGE_POKEMON",
}

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
	Notifier:addObserver(NotifyEvents.Battle.DialogEnded, self, self.onDialogEnded)
end

function BattleUIController:removeObservers()
	Notifier:removeObserver(NotifyEvents.Battle.DialogEnded, self)
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
	self.player = player
	local fieldEnemy = cc.Sprite:createWithSpriteFrameName(fieldFrameName)
	fieldEnemy:setPosition(winSize.width * -0.3, winSize.height * 0.7)
	self.root:addChild(fieldEnemy)
	self.fieldEnemy = fieldEnemy

	self.prepareStep = 1

	-- 初始化状态机
	BattleStateMachine:init(battleType)

	if battleType == Enumerations.BATTLE_TYPE.WILD then
		-- 野生精灵对战 直接显示野生精灵
		local pokemonId = self:getScene():getIntAttribute("pokemon_id")
		local pokemonLevel = self:getScene():getIntAttribute("pokemon_level")

		-- 随机生成神奇宝贝
		local pokemonModel = Pokemon:create(pokemonId, pokemonLevel)
		self.wildPokemonModel = pokemonModel

		-- 添加进入图鉴
		DataCenter:addNewCollection(pokemonId, false)

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
		action = cc.Sequence:create(
			action,
			cc.TargetedAction:create(self.enemyBoard, cc.MoveBy:create(0.8, ccp(winSize.width * 0.4, 0))),
			cc.CallFunc:create(MakeScriptHandler(self, self.checkPrepareDialog))
			)
	end

	self.root:runAction(action)
end

function BattleUIController:checkPrepareDialog()
	local dialogs = nil
	if self.battleType == Enumerations.BATTLE_TYPE.WILD then
		dialogs = self.WILD1V1_PREPARE_DIALOGS
	end
	local dialogKey = dialogs[self.prepareStep]
	if dialogKey then
		if dialogKey == "WILD_POKEMON_OCCUR" then
			self:notifyUpdatingDialog(dialogKey, self.wildPokemonModel.model.name)
		elseif dialogKey == "CHANGE_POKEMON" then
			-- 取第一个可用精灵
			self.currentPokemonModel = DataCenter:getFirstAvailablePokemon()
			self:notifyUpdatingDialog(dialogKey, self.currentPokemonModel.model.name)
		end
	else
		-- 正式开始战斗
		-- 播放动画
		local moveAction = cc.MoveBy:create(0.7, ccp(-350, 0))
		self.player:runAction(moveAction)
		CallFunctionAsync(self, self.showPokemon, 0.7)
		CallFunctionAsync(self, self.showBattleBoard, 0.8)
		CallFunctionAsync(self, self.resetBattle, 0.8)
	end
end

function BattleUIController:showPokemon()
	local formatStr = nil
	-- 是否是闪光？
	if self.currentPokemonModel.isShining then
		formatStr = "%03d_sb.png"
	else
		formatStr = "%03d_b.png"
	end
	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemons.rc", string.format(formatStr, self.currentPokemonModel.id), GameConfig.ZIP_PASSWORD)
	local playerPokemon = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	playerPokemon:setScale(0)
	playerPokemon:setPosition(self.fieldPlayer:getContentSize().width * 0.5, self.fieldPlayer:getContentSize().height * 0.5)
	playerPokemon:setAnchorPoint(0.5, 0)
	self.fieldPlayer:addChild(playerPokemon)
	self.playerPokemon = playerPokemon

	-- 丢出精灵球
	local winSize = cc.Director:getInstance():getWinSize()
	local ball = cc.Sprite:createWithSpriteFrameName("images/battle/ball" .. self.currentPokemonModel.ballId .. ".png")
	ball:setPosition(-winSize.width * 0.04, winSize.height * 0.42)
	self.root:addChild(ball)
end

function BattleUIController:showBattleBoard()

end

function BattleUIController:resetBattle()
	BattleStateMachine:reset()
end

function BattleUIController:notifyUpdatingDialog(dialogKey, ...)
	log("BattleUIController:notifyUpdatingDialog", dialogKey, ...)
	Notifier:notify(NotifyEvents.Battle.UpdateDialog, dialogKey, ...)
end

function BattleUIController:beginBattleWild1v1(pokemonModel)
	local formatStr = nil
	-- 是否是闪光？
	if pokemonModel.isShining then
		formatStr = "%03d_s.png"
	else
		formatStr = "%03d.png"
	end
	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemons.rc", string.format(formatStr, pokemonModel.id), GameConfig.ZIP_PASSWORD)
	local wildPokemon = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	wildPokemon:setScale(2)
	wildPokemon:setPosition(self.fieldEnemy:getContentSize().width * 0.5, self.fieldEnemy:getContentSize().height * 0.5)
	wildPokemon:setAnchorPoint(0.5, 0)
	self.fieldEnemy:addChild(wildPokemon)
	self.enemyPokemon = wildPokemon

	-- 遭遇精灵面板初始化
	local winSize = cc.Director:getInstance():getWinSize()

	local board = EnemyPokemonBoard:create(pokemonModel)
	board:setPosition(winSize.width * -0.2, winSize.height * 0.85)
	self.root:addChild(board)
	self.enemyBoard = board

	self:beginBattleAnimation()
end

function BattleUIController:onDialogEnded()
	log("BattleUIController:onDialogEnded")
	if BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.PREPARE then
		-- 准备阶段是否结束？
		self.prepareStep = self.prepareStep + 1
		self:checkPrepareDialog()
	else
		BattleStateMachine:process()
	end
end