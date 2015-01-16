--[[
	Description: enemy pokemon status board
	Author: M.Wan
	Date: 1/16/2015
]]

class("EnemyPokemonBoard", psNode)

EnemyPokemonBoard.bg = nil
EnemyPokemonBoard.iconStatus = nil
EnemyPokemonBoard.hpBar = nil

EnemyPokemonBoard.pokemonModel = nil

EnemyPokemonBoard.__create = psNode.create

function EnemyPokemonBoard:create(pokemonModel)
	local board = EnemyPokemonBoard:__create()
	board:initWithModel(pokemonModel)
	return board
end

function EnemyPokemonBoard:initWithModel(pokemonModel)
	self.pokemonModel = pokemonModel

	local bg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/back_gray.png", CCRectMake(10, 10, 30, 30))
	bg:setPreferredSize(CCSizeMake(240, 64))
	self:addChild(bg)
	self.bg = bg

	-- 名称
	local lblPokemonName = cc.Label:createWithTTF(pokemonModel.model.name, GameConfig.DEFAULT_FONT_PATH, 15)
	-- lblPokemonName:enableOutline(ccc4(0, 0, 0, 1), 4)
	lblPokemonName:setAnchorPoint(0, 0.5)
	lblPokemonName:setPosition(bg:getContentSize().width * 0.05, bg:getContentSize().height * 0.72)
	bg:addChild(lblPokemonName)

	-- 性别
	local iconGender = cc.Sprite:createWithSpriteFrameName(string.format("images/common/icon_%s.png", (pokemonModel.gender == Enumerations.GENDER.MALE and "male" or "female")))
	iconGender:setPosition(lblPokemonName:getPositionX() + lblPokemonName:getContentSize().width + 10, lblPokemonName:getPositionY())
	bg:addChild(iconGender)

	-- 等级
	local lblLevel = cc.Label:createWithTTF("Lv " .. pokemonModel.level, GameConfig.DEFAULT_FONT_PATH, 15)
	lblLevel:setAnchorPoint(1, 0.5)
	lblLevel:setPosition(bg:getContentSize().width * 0.95, lblPokemonName:getPositionY())
	bg:addChild(lblLevel)

	-- hp条
	local hpBack = cc.Sprite:createWithSpriteFrameName("images/common/hp_back.png")
	hpBack:setPosition(bg:getContentSize().width * 0.67, bg:getContentSize().height * 0.3)
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
	lblHp:setPosition(bg:getContentSize().width * 0.32, hpBar:getPositionY())
	bg:addChild(lblHp)

	-- 异常状态
	local iconStatus = cc.Sprite:createWithSpriteFrameName("images/common/icon_state_1.png")
	iconStatus:setScale(0.8)
	iconStatus:setPosition(lblHp:getPositionX() - 27, lblHp:getPositionY())
	bg:addChild(iconStatus)
	self.iconStatus = iconStatus
	iconStatus:setVisible(false)

	-- 捕获状态
	if DataCenter:isPokemonCaptured(pokemonId) then
		local ball = cc.Sprite:createWithSpriteFrameName("images/common/ball_owning.png")
		ball:setPosition(iconStatus:getPositionX() - 30, iconStatus:getPositionY())
		bg:addChild(ball)
	end
end