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

PlayerPokemonBoard.pokemonModel = nil

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
	local lblHpDetail = cc.Label:createWithTTF(string.format("%d / %d", pokemonModel.currentHp, pokemonModel.basicData.hp), GameConfig.DEFAULT_FONT_PATH, 15)
	lblHpDetail:enableShadow()
	lblHpDetail:setPosition(bg:getContentSize().width * 0.95, bg:getContentSize().height * 0.2)
	lblHpDetail:setAnchorPoint(1, 0.5)
	bg:addChild(lblHpDetail)

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