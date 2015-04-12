--[[
	Description: player pokemon status board
	Author: M.Wan
	Date: 3/30/2015
]]

class("PlayerPokemonBoard", psNode)

PlayerPokemonBoard.bg = nil
PlayerPokemonBoard.iconStatus = nil
PlayerPokemonBoard.hpBar = nil
PlayerPokemonBoard.expBar = nil
PlayerPokemonBoard.lblHpDetail = nil

PlayerPokemonBoard.pokemonModel = nil

PlayerPokemonBoard.HURT_SPEED_UNIT = 0.05
PlayerPokemonBoard.EXP_SPEED_UNIT = 0.01

PlayerPokemonBoard.__create = psNode.create

function PlayerPokemonBoard:create(pokemonModel)
	local board = PlayerPokemonBoard:__create()
	board:initWithModel(pokemonModel)
	return board
end

function PlayerPokemonBoard:initWithModel(pokemonModel)
	self.pokemonModel = pokemonModel

	local bg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/back_gray.png", CCRectMake(10, 10, 30, 30))
	bg:setPreferredSize(CCSizeMake(240, 74))
	self:addChild(bg)
	self.bg = bg

	-- 名称
	local lblPokemonName = cc.Label:createWithTTF(pokemonModel.model.name, GameConfig.DEFAULT_FONT_PATH, 15)
	-- lblPokemonName:enableOutline(ccc4(0, 0, 0, 1), 4)
	lblPokemonName:enableShadow()
	lblPokemonName:setAnchorPoint(0, 0.5)
	lblPokemonName:setPosition(bg:getContentSize().width * 0.05, bg:getContentSize().height * 0.8)
	bg:addChild(lblPokemonName)

	-- 性别
	local iconGender = cc.Sprite:createWithSpriteFrameName(string.format("images/common/icon_%s.png", (pokemonModel.gender == Enumerations.GENDER.MALE and "male" or "female")))
	iconGender:setPosition(lblPokemonName:getPositionX() + lblPokemonName:getContentSize().width + 10, lblPokemonName:getPositionY())
	bg:addChild(iconGender)

	-- 等级
	local lblLevel = cc.Label:createWithTTF("Lv " .. pokemonModel.level, GameConfig.DEFAULT_FONT_PATH, 15)
	lblLevel:enableShadow()
	lblLevel:setAnchorPoint(1, 0.5)
	lblLevel:setPosition(bg:getContentSize().width * 0.95, lblPokemonName:getPositionY())
	bg:addChild(lblLevel)

	-- hp条
	local hpBack = cc.Sprite:createWithSpriteFrameName("images/common/hp_back.png")
	hpBack:setPosition(bg:getContentSize().width * 0.67, bg:getContentSize().height * 0.4)
	bg:addChild(hpBack)
	local spHp = cc.Sprite:createWithSpriteFrameName("images/common/hp_green.png")
	local hpBar = cc.ProgressTimer:create(spHp)
	hpBar:setPosition(hpBack:getPosition())
	hpBar:setType(cc.PROGRESS_TIMER_TYPE_BAR)
	-- 从左边中间开始
	hpBar:setMidpoint(ccp(0, 0.5))
	-- 只控制水平方向长短
	hpBar:setBarChangeRate(ccp(1, 0))
	hpBar:setPercentage(100)
	bg:addChild(hpBar)
	self.hpBar = hpBar

	local lblHp = cc.Label:createWithTTF("HP", GameConfig.DEFAULT_FONT_PATH, 15)
	lblHp:enableShadow()
	lblHp:setPosition(bg:getContentSize().width * 0.32, hpBar:getPositionY())
	bg:addChild(lblHp)

	-- 异常状态
	local iconStatus = cc.Sprite:createWithSpriteFrameName("images/common/icon_state_1.png")
	iconStatus:setScale(0.8)
	iconStatus:setPosition(lblHp:getPositionX() - 57, lblHp:getPositionY())
	bg:addChild(iconStatus)
	self.iconStatus = iconStatus
	iconStatus:setVisible(false)

	-- HP详细值
	self.currentHp = pokemonModel.currentHp
	self.maxHp = pokemonModel.basicData.hp
	local lblHpDetail = cc.Label:createWithTTF(string.format("%d / %d", self.currentHp, self.maxHp), GameConfig.DEFAULT_FONT_PATH, 15)
	lblHpDetail:enableShadow()
	lblHpDetail:setPosition(bg:getContentSize().width * 0.95, bg:getContentSize().height * 0.2)
	lblHpDetail:setAnchorPoint(1, 0.5)
	bg:addChild(lblHpDetail)
	self.lblHpDetail = lblHpDetail

	-- 经验条
	local expBg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/back_gray.png", CCRectMake(10, 10, 30, 30))
	expBg:setPreferredSize(CCSizeMake(170, 25))
	expBg:setPosition(30, -40)
	self:addChild(expBg, -1)
	local expBack = cc.Sprite:createWithSpriteFrameName("images/battle/exp_bar.png")
	expBack:setPosition(expBg:getContentSize().width * 0.5, expBg:getContentSize().height * 0.4)
	expBg:addChild(expBack)
	local spExp = cc.Sprite:createWithSpriteFrameName("images/battle/exp_progress.png")
	local expBar = cc.ProgressTimer:create(spExp)
	expBar:setPosition(expBack:getContentSize().width * 0.575, expBack:getContentSize().height * 0.5)
	expBar:setType(cc.PROGRESS_TIMER_TYPE_BAR)
	-- 从左边中间开始
	expBar:setMidpoint(ccp(0, 0.5))
	-- 只控制水平方向长短
	expBar:setBarChangeRate(ccp(1, 0))
	expBar:setPercentage(pokemonModel:getExpPercentage())
	expBack:addChild(expBar)
	self.expBar = expBar
end

function PlayerPokemonBoard:update(dt)
	self.lblHpDetail:setString(string.format("%d / %d", math.floor(self.hpBar:getPercentage() / 100 * self.pokemonModel.basicData.hp), self.pokemonModel.basicData.hp))
end

function PlayerPokemonBoard:progressTo(value, callback)
	self.currentHp = value
	local actionAry = {}
	local progressAction = cc.ProgressFromTo:create(value * self.HURT_SPEED_UNIT, self.hpBar:getPercentage(), self.pokemonModel.currentHp / self.pokemonModel.basicData.hp * 100)
	table.insert(actionAry, progressAction)
	table.insert(actionAry, function()
		self:unscheduleUpdate()
	end)
	if callback then
		table.insert(actionAry, cc.CallFunc:create(callback))
	end
	local action = cc.Sequence:create(actionAry)
	self:scheduleUpdateWithPriorityLua(MakeScriptHandler(self, self.update), 0)
	self.hpBar:runAction(action)
end

function PlayerPokemonBoard:addExp(exp, oldLevel, newLevel, callback)
	assert(newLevel >= oldLevel, "PlayerPokemonBoard:addExp invalid params.")
	local action = nil
	if oldLevel == newLevel then
		-- 无等级变化
		local actionAry = {}
		local progressAction = cc.ProgressFromTo:create((self.pokemonModel:getExpPercentage() - self.expBar:getPercentage()) * self.EXP_SPEED_UNIT, self.expBar:getPercentage(), self.pokemonModel:getExpPercentage())
		table.insert(actionAry, progressAction)
		if callback then
			table.insert(actionAry, cc.CallFunc:create(callback))
		end
		action = cc.Sequence:create(actionAry)
	else
		-- 升级
		local deltaLevel = newLevel - oldLevel
		local actionAry = {}
		local firstProgress = cc.ProgressFromTo:create((100 - self.expBar:getPercentage()) * self.EXP_SPEED_UNIT, self.expBar:getPercentage(), 100)
		table.insert(actionAry, firstProgress)
		local firstCallFunc = cc.CallFunc:create(MakeScriptHandler(self, self.updateHpBar, oldLevel + 1))
		for i = 2, deltaLevel do
			table.insert(actionAry, cc.ProgressFromTo:create(100 * self.EXP_SPEED_UNIT, 0, 100))
			table.insert(actionAry, cc.CallFunc:create(MakeScriptHandler(self, self.updateHpBar, oldLevel + i)))
		end
		table.insert(actionAry, cc.ProgressFromTo:create(self.pokemonModel:getExpPercentage() * self.EXP_SPEED_UNIT, 0, self.pokemonModel:getExpPercentage()))
		if callback then
			table.insert(actionAry, cc.CallFunc:create(callback))
		end
		action = cc.Sequence:create(actionAry)
	end
	self.expBar:runAction(action)
end

function PlayerPokemonBoard:updateHpBar(sender, level)
	local oldHp = self.pokemonModel:getBasicDataAtLevel(level - 1).hp
	local newHp = self.pokemonModel:getBasicDataAtLevel(level).hp
	local deltaHp = newHp - oldHp
	self.lblHpDetail:setString(string.format("%d / %d", self.currentHp + deltaHp, newHp))
end