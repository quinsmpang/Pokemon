--[[
	Description: battle ui controller
	Author: M.Wan
	Date: 12/31/2014
]]

class("BattleUIController", psViewController)

require "src/scene/battle/BattleLogicConstants"
require "src/scene/battle/PlayerPokemonBoard"
require "src/scene/battle/EnemyPokemonBoard"
require "src/scene/battle/BattleStateMachine"
require "src/scene/battle/BattleCommonMenu"
require "src/scene/battle/SkillDescriptionBoard"
require "src/scene/battle/BattleBehaviors"
require "src/scene/battle/BattleAI"

BattleUIController.root = nil
BattleUIController.fieldPlayer = nil
BattleUIController.fieldEnemy = nil
BattleUIController.playerBoard = nil
BattleUIController.enemyBoard = nil		-- 1v1
BattleUIController.player = nil
BattleUIController.playerPokemon = nil
BattleUIController.enemyPokemon = nil
BattleUIController.battleMenu = nil		-- 战斗菜单
BattleUIController.skillMenu = nil		-- 技能菜单
BattleUIController.focusMenu = nil		-- 当前锁定的菜单
BattleUIController.skillDescriptionBoard = nil	-- 技能描述栏
BattleUIController.levelUpBoard = nil	-- 升级信息

BattleUIController.battleType = nil
BattleUIController.bgType = nil
BattleUIController.fieldType = nil
BattleUIController.needContinueCalculatingExp = nil		-- 是否需要继续计算经验值
BattleUIController.lastExpCalculatingIndex = nil		-- 上次计算到经验值的索引

BattleUIController.WILD1V1_PREPARE_DIALOGS = {
	"WILD_POKEMON_OCCUR",
	"CHANGE_POKEMON",
}
BattleUIController.BATTLE_INSTRUCTIONS = {
	"战斗", "背包", "精灵", "逃跑",
}

local winSize = cc.Director:getInstance():getWinSize()

function BattleUIController:load()
	log("BattleUIController:load")
	self:addObservers()
	self:renderView()
end

function BattleUIController:unload()
	log("BattleUIController:unload")
	self:removeObservers()
	self.root:removeFromParent(true)
end

function BattleUIController:addObservers()
	Notifier:addObserver(NotifyEvents.Battle.DialogEnded, self, self.onDialogEnded)
	Notifier:addObserver(NotifyEvents.Battle.TurnStart, self, self.onUpdateUI)
	Notifier:addObserver(NotifyEvents.Battle.PokemonHurtAnimation, self, self.onPokemonHurtAnimation)
	Notifier:addObserver(NotifyEvents.Battle.PokemonAbilityLevelChangedAnimation, self, self.onPokemonAbilityLevelChangedAnimation)
end

function BattleUIController:removeObservers()
	Notifier:removeObserver(NotifyEvents.Battle.DialogEnded, self)
	Notifier:removeObserver(NotifyEvents.Battle.TurnStart, self)
	Notifier:removeObserver(NotifyEvents.Battle.PokemonHurtAnimation, self)
	Notifier:removeObserver(NotifyEvents.Battle.PokemonAbilityLevelChangedAnimation, self)
end

function BattleUIController:renderView()
	log("BattleUIController:renderView")

	self.root = cc.Layer:create()
	self.root:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
	self:getScene():addChild(self.root)

	local battleType = self:getScene():getIntAttribute("battle_type")
	local bgType = self:getScene():getIntAttribute("battle_bg_type")
	local fieldType = self:getScene():getIntAttribute("battle_field_type")
	BattleSharedData.battleType = battleType
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
		BattleSharedData.enemyPokemonModel = pokemonModel
		BattleSharedData.enemyAI = BattleAI:create(1, { pokemonModel })

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

function BattleUIController:onNodeEvent(event)
	if event == "enter" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self.root)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			kbdListener:setEventsSwallowed(true)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		else
			local touchListener = cc.EventListenerTouchOneByOne:create()
			touchListener:setSwallowTouches(true)
			touchListener:registerScriptHandler(MakeScriptHandler(self, self.onTouch), cc.Handler.EVENT_TOUCH_BEGAN)
			self.root:getEventDispatcher():addEventListenerWithSceneGraphPriority(touchListener, self.root)
			self.touchListener = touchListener
		end
	elseif event == "exit" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
			self.kbdListener = nil
		elseif self.touchListener then
			self.root:getEventDispatcher():removeEventListener(self.touchListener)
		end
	end
end

function BattleUIController:onKeyboardPressed(keyCode)
	if not self.focusMenu or not self.focusMenu:isVisible() then
		return
	end
	if keyCode == GameSettings.leftKey then
		self.focusMenu:cursorLeft()
	elseif keyCode == GameSettings.rightKey then
		self.focusMenu:cursorRight()
	elseif keyCode == GameSettings.upKey then
		self.focusMenu:cursorUp()
	elseif keyCode == GameSettings.downKey then
		self.focusMenu:cursorDown()
	elseif keyCode == GameSettings.confirmKey then
		if self.levelUpBoard then
			self.levelUpBoard:removeFromParent()
			self.levelUpBoard = nil
			if self.needContinueCalculatingExp then
				self:calculateExp(self.lastExpCalculatingIndex + 1, BattleSharedData.joinBattlePokemons[self.lastExpCalculatingIndex + 1])
			else
				self:endTurn()
			end
		else
			local selectedIndex = self.focusMenu.selectedIndex
			if self.focusMenu == self.battleMenu then
				if selectedIndex == 1 then
					-- 战斗
					-- 检查是否有可用技能
					if self:hasAvailableSkill() then
						local skillNames = {}
						for _, skillInfo in ipairs(BattleSharedData.currentPokemonModel.skills) do
							local skillModel = SkillInfo:create(skillInfo[1])
							table.insert(skillNames, skillModel.name)
						end
						self.skillMenu = BattleCommonMenu:create(skillNames)
						self.skillMenu:setPosition(winSize.width * 0.25, winSize.height * 0.1)
						self.skillMenu:setIndexChangedScript(MakeScriptHandler(self, self.onSkillIndexChanged))
						self:getScene():addChild(self.skillMenu)
						self.focusMenu = self.skillMenu
						self.battleMenu:setVisible(false)

						-- 技能描述栏
						self.skillDescriptionBoard = SkillDescriptionBoard:create(BattleSharedData.currentPokemonModel.skills[1])
						self.skillDescriptionBoard:setPosition(winSize.width * 0.75, self.skillMenu:getContentSize().height * 0.5)
						self.skillMenu:addChild(self.skillDescriptionBoard)
					else
						-- 没有技能可用，使用拼命技能
						BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.GENERATE_BEHAVIORS)
						BattleStateMachine:process(BattleBehavior.BEHAVIOR_TYPES.ATTACK, { 165, 999999, 0 })
					end
				elseif selectedIndex == 2 then
					-- 背包
					require "src/scene/bag/BagViewController"

					local bagViewController = BagViewController:create()
					self:getScene():putIntAttribute(GameConfig.BAG_KEY, Enumerations.BAG_VIEW_SCENE_TYPE.BATTLE)
					self:getScene():loadViewController(bagViewController)
				elseif selectedIndex == 3 then
					-- 精灵
				elseif selectedIndex == 4 then
					-- 逃跑
					self.battleMenu:setVisible(false)
					BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.GENERATE_BEHAVIORS)
					BattleStateMachine:process(BattleBehavior.BEHAVIOR_TYPES.ESCAPE, { true })
				end
			elseif self.focusMenu == self.skillMenu then
				local skills = BattleSharedData.currentPokemonModel.skills
				-- 该技能是否被禁用？
				if BattleSharedData.forbiddenPlayerPokemonIndex == selectedIndex then
					DialogPopHelper:popAutoHideMessage(CCSizeMake(winSize.width * 0.4, winSize.height * 0.1), "该技能被封印!")
					return
				elseif skills[selectedIndex][2] <= 0 then
					DialogPopHelper:popAutoHideMessage(CCSizeMake(winSize.width * 0.4, winSize.height * 0.1), "该技能没有PP!")
					return
				else
					local skillData = skills[selectedIndex]
					self.skillMenu:removeFromParent(true)
					self.skillMenu = nil
					self.focusMenu = self.battleMenu
					BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.GENERATE_BEHAVIORS)
					BattleStateMachine:process(BattleBehavior.BEHAVIOR_TYPES.ATTACK, skillData)
				end 
			end
		end
	elseif keyCode == GameSettings.cancelKey and self.focusMenu == self.skillMenu then
		if self.levelUpBoard then
			if self.needContinueCalculatingExp then
				self:calculateExp(self.lastExpCalculatingIndex + 1, BattleSharedData.joinBattlePokemons[self.lastExpCalculatingIndex + 1])
			else
				self:endTurn()
			end
		else
			self.skillMenu:removeFromParent(true)
			self.skillMenu = nil
			self.focusMenu = self.battleMenu
			self.battleMenu:setVisible(true)
		end
	end
end

function BattleUIController:hasAvailableSkill()
	local skills = BattleSharedData.currentPokemonModel.skills
	local flag = false
	for i, skill in ipairs(skills) do
		if i ~= BattleSharedData.forbiddenPlayerPokemonIndex and skill[2] > 0 then
			flag = true
			break
		end
	end
	return flag
end

function BattleUIController:onSkillIndexChanged(oldIndex, newIndex)
	self.skillDescriptionBoard:update(BattleSharedData.currentPokemonModel.skills[newIndex])
end

function BattleUIController:beginBattleAnimation()
	local action = cc.Spawn:create(
		cc.TargetedAction:create(self.fieldPlayer, cc.MoveBy:create(3, ccp(-winSize.width, 0))),
		cc.TargetedAction:create(self.fieldEnemy, cc.MoveBy:create(3, ccp(winSize.width, 0)))
		)

	if BattleSharedData.battleType == Enumerations.BATTLE_TYPE.WILD then
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
	if BattleSharedData.battleType == Enumerations.BATTLE_TYPE.WILD then
		dialogs = self.WILD1V1_PREPARE_DIALOGS
	end
	local dialogKey = dialogs[self.prepareStep]
	if dialogKey then
		if dialogKey == "WILD_POKEMON_OCCUR" then
			self:notifyUpdatingDialog(dialogKey, BattleSharedData.enemyPokemonModel.model.name)
		elseif dialogKey == "CHANGE_POKEMON" then
			-- 取第一个可用精灵
			BattleSharedData.currentPokemonModel = DataCenter:getFirstAvailablePokemon()
			self:notifyUpdatingDialog(dialogKey, BattleSharedData.currentPokemonModel.model.name)
		end
	else
		-- 正式开始战斗
		-- 播放动画
		local moveAction = cc.MoveBy:create(0.7, ccp(-350, 0))
		self.player:runAction(moveAction)
		CallFunctionAsync(self, self.showPokemon, 0.7)
	end
end

function BattleUIController:showPokemon()
	local formatStr = nil
	-- 是否是闪光？
	if BattleSharedData.currentPokemonModel.isShining then
		formatStr = "%03d_sb.png"
	else
		formatStr = "%03d_b.png"
	end
	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemons.rc", string.format(formatStr, BattleSharedData.currentPokemonModel.id), GameConfig.ZIP_PASSWORD)
	local playerPokemon = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	playerPokemon:setScale(0)
	playerPokemon:setPosition(self.fieldPlayer:getContentSize().width * 0.5, self.fieldPlayer:getContentSize().height * 0.5)
	playerPokemon:setAnchorPoint(0.5, 0)
	self.fieldPlayer:addChild(playerPokemon)
	self.playerPokemon = playerPokemon

	-- 丢出精灵球
	local ball = cc.Sprite:createWithSpriteFrameName("images/battle/ball" .. BattleSharedData.currentPokemonModel.ballId .. ".png")
	self.root:addChild(ball)
	-- 计算抛物线
	local h = winSize.width * 0.125
	local k = winSize.height * 0.7
	local fieldPos = ccp(self.fieldPlayer:getPosition())
	local a = (fieldPos.y - k) / (fieldPos.x - h) / (fieldPos.x - h)
	local parabolaAction = ActionParabola:create(1, a, h, k, -winSize.width * 0.1, fieldPos.x)
	local rotationAction = cc.RotateBy:create(1, 360 * 4)
	local callFuncAction = cc.CallFunc:create(MakeScriptHandler(self, self.showPokemonCallback, ball))
	local action = cc.Sequence:create(
		cc.Spawn:create(
			parabolaAction,
			rotationAction
			),
		callFuncAction
		)
	ball:runAction(action)
end
function BattleUIController:showPokemonCallback(sender, ball)
	ball:removeFromParent(true)
	local scaleAction = cc.ScaleTo:create(0.5, 2)
	local colorAction1 = ActionColorTo:create(0.5, ccc3(255, 0, 0))
	local colorAction2 = colorAction1:reverse()
	local callFuncAction = cc.CallFunc:create(MakeScriptHandler(self, self.showPokemonCallback2))
	local action = cc.Sequence:create(
		cc.Spawn:create(
			scaleAction,
			colorAction1
			),
		colorAction2,
		callFuncAction
		)
	self.playerPokemon:runAction(action)
end
function BattleUIController:showPokemonCallback2()
	local playerBoard = PlayerPokemonBoard:create(BattleSharedData.currentPokemonModel)
	playerBoard:setPosition(winSize.width * 1.2, winSize.height * 0.4)
	self.root:addChild(playerBoard)
	self.playerBoard = playerBoard

	playerBoard:runAction(cc.Sequence:create(
		cc.MoveBy:create(0.8, ccp(-winSize.width * 0.4, 0)),
		cc.CallFunc:create(MakeScriptHandler(self, self.showPokemonCallback3))
		))
end
function BattleUIController:showPokemonCallback3()
	BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.TURN_START)
	BattleStateMachine:process()
end

function BattleUIController:onUpdateUI()
	if BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.TURN_START then
		-- 重置一些信息
		BattleSharedData.joinBattlePokemons = { BattleSharedData.currentPokemonModel }
		local dialogKey = "GIVE_INSTRUCTIONS"
		local showDialog = string.format(BattleDialogConstants[dialogKey])
		Notifier:notify(NotifyEvents.Battle.ShowDialogDirectly, showDialog)
		-- 显示战斗操作面板
		if not self.battleMenu then
			self.battleMenu = BattleCommonMenu:create(self.BATTLE_INSTRUCTIONS)
			self.battleMenu:setPosition(winSize.width * 0.78, winSize.height * 0.1)
			self.battleMenu:setVisible(false)
			self:getScene():addChild(self.battleMenu)
		end
		self.battleMenu:setVisible(true)

		self.focusMenu = self.battleMenu
	end
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
	elseif BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.ESCAPE then
		-- 逃跑
		ReplaceScene(MapViewScene)
	elseif BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.ESCAPE_FORBIDDEN then
		-- 禁止逃跑
		BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.TURN_START)
		BattleStateMachine:process()
	else
		BattleStateMachine:process()
	end
end

function BattleUIController:onPokemonHurtAnimation(dmg, heal)
	if BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.PLAYER_TURN then
		if dmg > 0 then
			-- 敌方伤血(如果有)
			local callback = function()
				if BattleSharedData.enemyPokemonModel:isDead() then
					-- 精灵死亡
					local dialogKey = "POKEMON_DEAD"
					local showDialog = string.format(BattleDialogConstants[dialogKey], BattleSharedData.enemyPokemonModel.model.name)
					local substrings = GenerateAllUTF8Substrings(showDialog)
					Notifier:notify(NotifyEvents.Battle.ShowDialog, substrings)
					CallFunctionAsync(self, self.enemyDead, BattleDialogController.DIALOG_TEXT_DURATION * (#substrings + 2))
				else
					-- 是否继续进行敌方回合
					self:checkOppositeTurn(nil, false)
				end
			end
			if heal > 0 then
				-- 是否有回复？
				callback = function()
					self.playerBoard:progressTo(heal, callback)
				end
			end
			self.enemyBoard:progressTo(dmg, callback)
		elseif heal > 0 then
			-- 我方回复(如果有)
			self.playerBoard:progressTo(heal, MakeScriptHandler(self, self.checkOppositeTurn, false))
		end
	elseif BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.ENEMY_TURN then
		if dmg > 0 then
			-- 我方伤血(如果有)
			local callback = function()
				if BattleSharedData.currentPokemonModel:isDead() then
					-- 精灵死亡
					local dialogKey = "POKEMON_DEAD"
					local showDialog = string.format(BattleDialogConstants[dialogKey], BattleSharedData.currentPokemonModel.model.name)
					local substrings = GenerateAllUTF8Substrings(showDialog)
					Notifier:notify(NotifyEvents.Battle.ShowDialog, substrings)
					CallFunctionAsync(self, self.playerDead, BattleDialogController.DIALOG_TEXT_DURATION * (#substrings + 2))
				else
					-- 是否继续进行我方回合
					self:checkOppositeTurn(nil, true)
				end
			end
			if heal > 0 then
				-- 是否有回复？
				callback = function()
					self.enemyBoard:progressTo(heal, callback)
				end
			else
				callback = MakeScriptHandler(self, self.checkOppositeTurn, true)
			end
			self.playerBoard:progressTo(dmg, callback)
		elseif heal > 0 then
			-- 敌方回复(如果有)
			self.enemyBoard:progressTo(heal, MakeScriptHandler(self, self.checkOppositeTurn, true))
		end
	end
end
function BattleUIController:checkOppositeTurn(sender, isPlayer)
	log("BattleUIController:checkOppositeTurn", isPlayer)
	-- 回合是否继续
	if BattleStateMachine[(isPlayer and "friendBehavior" or "enemyBehavior")] then
		BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE[(isPlayer and "PLAYER_TURN" or "ENEMY_TURN")])
	else
		BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.TURN_START)
	end
	BattleStateMachine:process(NotifyEvents.Battle.ShowDialog, substrings)
end

function BattleUIController:playerDead()
	self.playerPokemon:runAction(cc.FadeOut:create(1))
	CallFunctionAsync(self, self.playerDeadCallback, 1.5)
end
function BattleUIController:playerDeadCallback()
	if DataCenter:getAvailablePokemonCount() > 0 then
		-- 选其他精灵 todo
	else
		-- 战斗失败 todo
	end
end

function BattleUIController:enemyDead()
	self.enemyPokemon:runAction(cc.FadeOut:create(1))
	CallFunctionAsync(self, self.enemyDeadCallback, 1.5)
end
function BattleUIController:enemyDeadCallback()
	if BattleSharedData.battleType == Enumerations.BATTLE_TYPE.WILD then
		-- 是否有学习装置 todo
		-- 当前精灵最后处理
		BattleSharedData.joinBattlePokemons[1], BattleSharedData.joinBattlePokemons[#BattleSharedData.joinBattlePokemons] = BattleSharedData.joinBattlePokemons[#BattleSharedData.joinBattlePokemons], BattleSharedData.joinBattlePokemons[1]
		self:calculateExp(1, BattleSharedData.joinBattlePokemons[1])
	end
end
function BattleUIController:calculateExp(index, pokemon)
	if pokemon.currentHp <= 0 then
		if index == #BattleSharedData.joinBattlePokemons then
			-- 直接处理下一流程
			CallFunctionAsync(self, self.endTurn, BattleDialogController.DIALOG_TEXT_DURATION * 2)
		else
			self:calculateExp(index + 1, BattleSharedData.joinBattlePokemons[index + 1])
		end
		return
	end

	local baseExp = BattleSharedData.enemyPokemonModel:beatenExp()
	local oldLevel = pokemon.level
	local dialogKey = "GAIN_EXP"
	-- 是否有幸福蛋道具 todo
	local happinessEggCorrection = 1
	local exchangeCorrection = 1 / table.getTotalCount(BattleSharedData.joinBattlePokemons, function(v)
		return v.currentHp > 0
	end)
	local exp = baseExp * happinessEggCorrection * exchangeCorrection
	-- 增加经验值
	pokemon:addExp(exp)
	local newLevel = pokemon.level
	-- 增加努力值 todo
	local showDialog = string.format(BattleDialogConstants[dialogKey], pokemon.model.name, exp)
	local substrings = GenerateAllUTF8Substrings(showDialog)
	Notifier:notify(NotifyEvents.Battle.ShowDialog, substrings)
	log(string.format("增加经验值: %d, 等级变化: %d -> %d", exp, oldLevel, newLevel))
	if index < #BattleSharedData.joinBattlePokemons then
		if newLevel > oldLevel then
			-- 升级面板
			self.needContinueCalculatingExp = true
			self.lastExpCalculatingIndex = index
			CallFunctionAsync(self, self.showLevelUpText, BattleDialogController.DIALOG_TEXT_DURATION * (#substrings + 2), pokemon, oldLevel, newLevel)
		else
			CallFunctionAsync(self, self.calculateExp, BattleDialogController.DIALOG_TEXT_DURATION * (#substrings + 2), index + 1, BattleSharedData.joinBattlePokemons[index + 1])
		end
	else
		self.needContinueCalculatingExp = nil
		self.lastExpCalculatingIndex = index
		CallFunctionAsync(self, self.playExpAddAnimation, BattleDialogController.DIALOG_TEXT_DURATION * (#substrings + 2), pokemon, exp, oldLevel, newLevel)
	end
end
function BattleUIController:showLevelUpText(pokemon, oldLevel, newLevel)
	local dialogKey = "LEVEL_UP"
	local showDialog = string.format(BattleDialogConstants[dialogKey], pokemon.model.name, newLevel)
	local substrings = GenerateAllUTF8Substrings(levelUpDialog)
	Notifier:notify(NotifyEvents.Battle.ShowDialog, substrings)
	CallFunctionAsync(self, self.showLevelUpBoard, BattleDialogController.DIALOG_TEXT_DURATION * (#substrings + 2), pokemon, oldLevel, newLevel)
end
function BattleUIController:showLevelUpBoard(pokemon, oldLevel, newLevel)
	self.levelUpBoard = cc.Layer:create()
	self.root:addChild(self.levelUpBoard)
end
function BattleUIController:playExpAddAnimation(pokemon, exp, oldLevel, newLevel)
	local callback = nil
	if newLevel > oldLevel then
		callback = MakeScriptHandler(self, self.playExpAddAnimationCallfunc, pokemon, oldLevel, newLevel)
	else
		callback = MakeScriptHandler(self, self.endTurn)
	end
	self.playerBoard:addExp(exp, oldLevel, newLevel, callback)
end
function BattleUIController:playExpAddAnimationCallfunc(sender, pokemon, oldLevel, newLevel)
	self:showLevelUpText(pokemon, oldLevel, newLevel)
end

function BattleUIController:endTurn()
	BattleStateMachine:setState(BattleLogicConstants.BATTLE_STATE.TURN_END)
	BattleStateMachine:process()
end

function BattleUIController:onPokemonAbilityLevelChangedAnimation(skillId)
	if BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.PLAYER_TURN then
		self:checkOppositeTurn(nil, false)
	elseif BattleStateMachine.state == BattleLogicConstants.BATTLE_STATE.ENEMY_TURN then
		self:checkOppositeTurn(nil, true)
	end
end