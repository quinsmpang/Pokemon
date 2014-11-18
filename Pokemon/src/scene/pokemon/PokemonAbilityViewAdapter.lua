--[[
	Description: Pokemon ability view adapter
	Author: M.Wan
	Date: 11/18/2014
]]

luaClass("PokemonAbilityViewAdapter")

PokemonAbilityViewAdapter.layer = nil

function PokemonAbilityViewAdapter:adapt(detailView)
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
	local tabItem = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabItem:setAnchorPoint(0, 1)
	tabItem:setPosition(winSize.width * 0.52, winSize.height - 20)
	layer:addChild(tabItem)
	local lblTabItem = cc.Label:createWithTTF("道具", GameConfig.DEFAULT_FONT_PATH, 22)
	lblTabItem:setAnchorPoint(0, 0.5)
	lblTabItem:setPosition(8.5, tabItem:getContentSize().height * 0.5)
	tabItem:addChild(lblTabItem)

	local itemBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 30, 30))
	itemBorder:setPreferredSize(CCSizeMake(210, 35))
	itemBorder:setAnchorPoint(0, 1)
	itemBorder:setPosition(tabItem:getPositionX(), tabItem:getPositionY() - tabItem:getContentSize().height - 10)
	layer:addChild(itemBorder)
	local itemText = "无"
	if pokemon.carriedItem ~= DBNULL then
		-- 道具todo
	end
	local lblItem = cc.Label:createWithTTF(itemText, GameConfig.DEFAULT_FONT_PATH, 22)
	lblItem:setAnchorPoint(0, 0.5)
	lblItem:setColor(COLOR3B_BLACK)
	lblItem:setPosition(itemBorder:getContentSize().width * 0.05, itemBorder:getContentSize().height * 0.5)
	itemBorder:addChild(lblItem)

	-- 能力值
	local tabAbility = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabAbility:setAnchorPoint(0, 1)
	tabAbility:setPosition(tabItem:getPositionX(), itemBorder:getPositionY() - itemBorder:getContentSize().height - 10)
	layer:addChild(tabAbility)
	local lblAbilityTitle = cc.Label:createWithTTF("能力值", GameConfig.DEFAULT_FONT_PATH, 22)
	lblAbilityTitle:setAnchorPoint(0, 0.5)
	lblAbilityTitle:setPosition(lblTabItem:getPosition())
	tabAbility:addChild(lblAbilityTitle)

	local abilityBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 30, 30))
	abilityBorder:setPreferredSize(CCSizeMake(360, 105))
	abilityBorder:setAnchorPoint(0, 1)
	abilityBorder:setPosition(tabAbility:getPositionX(), tabAbility:getPositionY() - tabAbility:getContentSize().height - 10)
	layer:addChild(abilityBorder)

	local basicData = pokemon.basicData

	local nameMap = { "HP", "物攻", "物防", "特攻", "特防", "速度" }
	local valueMap = { "hp", "physicalAttack", "physicalDefense", "specialAttack", "specialDefense", "agility" }
	for i = 1, 6 do
		local lblAbilityName = cc.Label:createWithTTF(nameMap[i], GameConfig.DEFAULT_FONT_PATH, 22)
		lblAbilityName:setColor(COLOR3B_BLACK)
		lblAbilityName:setAnchorPoint(0, 1)
		lblAbilityName:setPosition(lblItem:getPositionX() + math.floor((i - 1) / 3) * 175, abilityBorder:getContentSize().height - 5 - (i - 1) % 3 * 32)
		abilityBorder:addChild(lblAbilityName)
		local lblValue = cc.Label:createWithTTF(tostring(basicData[valueMap[i]]), GameConfig.DEFAULT_FONT_PATH, 22)
		lblValue:setColor(COLOR3B_BLACK)
		lblValue:setAnchorPoint(1, 1)
		lblValue:setPosition(lblItem:getPositionX() + 150 + math.floor((i - 1) / 3) * 175, abilityBorder:getContentSize().height - 5 - (i - 1) % 3 * 32)
		abilityBorder:addChild(lblValue)
	end

	-- 经验
	local tabExp = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabExp:setAnchorPoint(0, 1)
	tabExp:setPosition(tabItem:getPositionX(), abilityBorder:getPositionY() - abilityBorder:getContentSize().height - 10)
	layer:addChild(tabExp)
	local lblExpTitle = cc.Label:createWithTTF("经验值", GameConfig.DEFAULT_FONT_PATH, 22)
	lblExpTitle:setAnchorPoint(0, 0.5)
	lblExpTitle:setPosition(lblTabItem:getPosition())
	tabExp:addChild(lblExpTitle)

	local expBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 30, 30))
	expBorder:setPreferredSize(CCSizeMake(360, 70))
	expBorder:setAnchorPoint(0, 1)
	expBorder:setPosition(tabExp:getPositionX(), tabExp:getPositionY() - tabExp:getContentSize().height - 10)
	layer:addChild(expBorder)

	local lblCurrentExp = cc.Label:createWithTTF("经验值", GameConfig.DEFAULT_FONT_PATH, 22)
	lblCurrentExp:setAnchorPoint(0, 1)
	lblCurrentExp:setColor(COLOR3B_BLACK)
	lblCurrentExp:setPosition(lblItem:getPositionX(), expBorder:getContentSize().height - 5)
	expBorder:addChild(lblCurrentExp)
	local lblExpValue = cc.Label:createWithTTF(tostring(pokemon.exp), GameConfig.DEFAULT_FONT_PATH, 22)
	lblExpValue:setAnchorPoint(1, 1)
	lblExpValue:setColor(COLOR3B_BLACK)
	lblExpValue:setPosition(lblItem:getPositionX() + 321, lblCurrentExp:getPositionY())
	expBorder:addChild(lblExpValue)

	local lblRestExp = cc.Label:createWithTTF("升级剩余", GameConfig.DEFAULT_FONT_PATH, 22)
	lblRestExp:setAnchorPoint(0, 1)
	lblRestExp:setColor(COLOR3B_BLACK)
	lblRestExp:setPosition(lblCurrentExp:getPositionX(), lblCurrentExp:getPositionY() - 32)
	expBorder:addChild(lblRestExp)
	local lblRestExpValue = cc.Label:createWithTTF(tostring(pokemon:getRestExp()), GameConfig.DEFAULT_FONT_PATH, 22)
	lblRestExpValue:setAnchorPoint(1, 1)
	lblRestExpValue:setColor(COLOR3B_BLACK)
	lblRestExpValue:setPosition(lblExpValue:getPositionX(), lblRestExp:getPositionY())
	expBorder:addChild(lblRestExpValue)
end

function PokemonAbilityViewAdapter:remove()
	if self.layer then
		self.layer:removeFromParent()
	end
end