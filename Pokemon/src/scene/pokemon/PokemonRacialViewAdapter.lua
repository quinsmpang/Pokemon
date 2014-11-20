--[[
	Description: Pokemon racial view adapter
	Author: M.Wan
	Date: 11/21/2014
]]

luaClass("PokemonRacialViewAdapter")

PokemonRacialViewAdapter.layer = nil

function PokemonRacialViewAdapter:adapt(detailView)
	assert(detailView and detailView.__className == "PokemonDetailView", "invalid argument")
	if detailView.adapter then
		detailView.adapter:remove()
		detailView.adapter = nil
	end
	detailView.adapter = self

	local winSize = cc.Director:getInstance():getWinSize()
	local pokemon = detailView.relatedPokemon

	local layer = cc.Layer:create()
	detailView:addChild(layer)
	self.layer = layer

	-- 道具
	local tabRacial = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabRacial:setAnchorPoint(0, 1)
	tabRacial:setPosition(winSize.width * 0.52, winSize.height - 20)
	layer:addChild(tabRacial)
	local lbltabRacial = cc.Label:createWithTTF("种族值", GameConfig.DEFAULT_FONT_PATH, 22)
	lbltabRacial:setAnchorPoint(0, 0.5)
	lbltabRacial:setPosition(8.5, tabRacial:getContentSize().height * 0.5)
	tabRacial:addChild(lbltabRacial)

	local racialBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 30, 30))
	racialBorder:setPreferredSize(CCSizeMake(360, 390))
	racialBorder:setAnchorPoint(0, 1)
	racialBorder:setPosition(tabRacial:getPositionX(), tabRacial:getPositionY() - tabRacial:getContentSize().height - 10)
	layer:addChild(racialBorder)

	local polygonBack = cc.Sprite:createWithSpriteFrameName("images/pokemon/polygon6withline.png")
	polygonBack:setPosition(racialBorder:getContentSize().width * 0.5, racialBorder:getContentSize().height * 0.5)
	racialBorder:addChild(polygonBack)

	local lblHp = cc.Label:createWithTTF("HP", GameConfig.DEFAULT_FONT_PATH, 22)
	lblHp:setColor(COLOR3B_BLACK)
	lblHp:setPosition(racialBorder:getContentSize().width * 0.5, racialBorder:getContentSize().height * 0.95)
	racialBorder:addChild(lblHp)
	local lblAtk = cc.Label:createWithTTF("物攻", GameConfig.DEFAULT_FONT_PATH, 22)
	lblAtk:setColor(COLOR3B_BLACK)
	lblAtk:setPosition(racialBorder:getContentSize().width * 0.1, racialBorder:getContentSize().height * 0.76)
	racialBorder:addChild(lblAtk)
	local lblDef = cc.Label:createWithTTF("物防", GameConfig.DEFAULT_FONT_PATH, 22)
	lblDef:setColor(COLOR3B_BLACK)
	lblDef:setPosition(racialBorder:getContentSize().width * 0.1, racialBorder:getContentSize().height * 0.24)
	racialBorder:addChild(lblDef)
	local lblSAtk = cc.Label:createWithTTF("特攻", GameConfig.DEFAULT_FONT_PATH, 22)
	lblSAtk:setColor(COLOR3B_BLACK)
	lblSAtk:setPosition(racialBorder:getContentSize().width * 0.9, racialBorder:getContentSize().height * 0.76)
	racialBorder:addChild(lblSAtk)
	local lblSDef = cc.Label:createWithTTF("特防", GameConfig.DEFAULT_FONT_PATH, 22)
	lblSDef:setColor(COLOR3B_BLACK)
	lblSDef:setPosition(racialBorder:getContentSize().width * 0.9, racialBorder:getContentSize().height * 0.24)
	racialBorder:addChild(lblSDef)
	local lblAgi = cc.Label:createWithTTF("速度", GameConfig.DEFAULT_FONT_PATH, 22)
	lblAgi:setColor(COLOR3B_BLACK)
	lblAgi:setPosition(racialBorder:getContentSize().width * 0.5, racialBorder:getContentSize().height * 0.05)
	racialBorder:addChild(lblAgi)

	-- calculate vertex points
	local maxVal = 210
	local racials = pokemon.model.racial
	local height = polygonBack:getContentSize().height
	local points = {}
	local angle = math.pi / 6
	local x, y, c
	-- hp point
	x = 0
	y = racials[1] / maxVal * height * 0.5
	local hpPos = ccp(x, y)
	table.insert(points, hpPos)
	-- physical atk point
	c = racials[2] / maxVal * height * 0.5
	x = -c * math.cos(angle)
	y = c * 0.5
	local pAtkPos = ccp(x, y)
	table.insert(points, pAtkPos)
	-- pysical def point
	c = racials[3] / maxVal * height * 0.5
	x = -c * math.cos(angle)
	y = -c * 0.5
	local pDefPos = ccp(x, y)
	table.insert(points, pDefPos)
	-- agility point
	x = 0
	y = -racials[6] / maxVal * height * 0.5
	local agiPos = ccp(x, y)
	table.insert(points, agiPos)
	-- special def point
	c = racials[5] / maxVal * height * 0.5
	x = c * math.cos(angle)
	y = -c * 0.5
	local sDefPos = ccp(x, y)
	table.insert(points, sDefPos)
	-- special atk point
	c = racials[4] / maxVal * height * 0.5
	x = c * math.cos(angle)
	y = c * 0.5
	local sAtkPos = ccp(x, y)
	table.insert(points, sAtkPos)

	-- draw racial polygon
	local racialPolygon = cc.DrawNode:create()
	-- table.dump(points)
	racialPolygon:drawPolygon(points, 6, ccc4f(0, 0, 0, 1), 1, ccc4f(0, 0, 0, 1))
	racialPolygon:setPosition(polygonBack:getPosition())
	racialBorder:addChild(racialPolygon)
end

function PokemonRacialViewAdapter:remove()
	if self.layer then
		self.layer:removeFromParent()
	end
end