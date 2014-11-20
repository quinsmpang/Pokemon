--[[
	Description: Pokemon skill view adapter
	Author: M.Wan
	Date: 11/20/2014
]]

luaClass("PokemonSkillViewAdapter")

PokemonSkillViewAdapter.layer = nil
PokemonSkillViewAdapter.selection = nil				-- 选中框
PokemonSkillViewAdapter.swapSelection = nil		-- 交换框
PokemonSkillViewAdapter.skillCells = nil
PokemonSkillViewAdapter.descriptionBorder = nil	-- 描述框
PokemonSkillViewAdapter.lblDescription = nil	-- 描述
PokemonSkillViewAdapter.tabEffect = nil
PokemonSkillViewAdapter.effectBorder = nil
PokemonSkillViewAdapter.lblPower = nil
PokemonSkillViewAdapter.lblHitRate = nil

PokemonSkillViewAdapter.relatedPokemon = nil
PokemonSkillViewAdapter.skillModels = nil	-- Model list
PokemonSkillViewAdapter.swapIndex = nil		
PokemonSkillViewAdapter.inSwap = nil
PokemonSkillViewAdapter.selectedIndex = nil

-- const
PokemonSkillViewAdapter.SELECTION_ZORDER = 100
PokemonSkillViewAdapter.SWAP_SELECTION_ZORDER = 101

function PokemonSkillViewAdapter:adapt(detailView)
	assert(detailView and detailView.__className == "PokemonDetailView", "invalid argument")
	if detailView.adapter then
		detailView.adapter:remove()
		detailView.adapter = nil
	end
	detailView.adapter = self	

	self.inSwap = false

	local winSize = cc.Director:getInstance():getWinSize()
	local pokemon = detailView.relatedPokemon
	self.relatedPokemon = pokemon

	local layer = cc.Layer:create()
	detailView:addChild(layer)
	self.layer = layer

	-- 技能
	local tabSkill = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabSkill:setAnchorPoint(0, 1)
	tabSkill:setPosition(winSize.width * 0.52, winSize.height - 20)
	layer:addChild(tabSkill)
	local lblSkillTab = cc.Label:createWithTTF("技能", GameConfig.DEFAULT_FONT_PATH, 22)
	lblSkillTab:setAnchorPoint(0, 0.5)
	lblSkillTab:setPosition(8.5, tabSkill:getContentSize().height * 0.5)
	tabSkill:addChild(lblSkillTab)

	-- skills init
	self.skillModels = {}
	for _, v in ipairs(pokemon.skills) do
		local skillModel = SkillInfo:create(v[1])
		table.insert(self.skillModels, skillModel)
	end

	local skillBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 30, 30))
	skillBorder:setPreferredSize(CCSizeMake(360, 140))
	skillBorder:setAnchorPoint(0, 1)
	skillBorder:setPosition(tabSkill:getPositionX(), tabSkill:getPositionY() - tabSkill:getContentSize().height - 10)
	layer:addChild(skillBorder)

	self.skillCells = {}
	for i = 1, 4 do
		local skillModel = self.skillModels[i]
		if skillModel then
			local cell = cc.Node:create()
			cell:setAnchorPoint(0, 1)
			cell:setPosition(0, skillBorder:getContentSize().height - 10 - (i - 1) * 32)
			skillBorder:addChild(cell)

			-- property icon
			local propIcon = cc.Sprite:createWithSpriteFrameName("images/pokemon/icon_prop_" .. skillModel.property .. ".png")
			propIcon:setAnchorPoint(0, 0.5)
			propIcon:setPosition(10.5, 0)
			cell:addChild(propIcon)

			local lblSkillName = cc.Label:createWithTTF(skillModel.name, GameConfig.DEFAULT_FONT_PATH, 22)
			lblSkillName:setColor(COLOR3B_BLACK)
			lblSkillName:setAnchorPoint(0, 1)
			lblSkillName:setPosition(propIcon:getPositionX() + propIcon:getContentSize().width + 50, 0)
			cell:addChild(lblSkillName)

			local lblPPText = cc.Label:createWithTTF("PP", GameConfig.DEFAULT_FONT_PATH, 22)
			lblPPText:setColor(COLOR3B_BLACK)
			lblPPText:setAnchorPoint(0, 1)
			lblPPText:setPosition(lblSkillName:getPositionX() + 150, lblSkillName:getPositionY())
			cell:addChild(lblPPText)

			local lblPP = cc.Label:createWithTTF(pokemon.skills[i][2] .. "/" .. pokemon:getSkillMaxPP(i), GameConfig.DEFAULT_FONT_PATH, 22)
			lblPP:setAnchorPoint(1, 1)
			lblPP:setColor(COLOR3B_BLACK)
			lblPP:setPosition(skillBorder:getContentSize().width - 10.5, lblSkillName:getPositionY())
			cell:addChild(lblPP)

			propIcon:setPositionY(propIcon:getPositionY() - lblPP:getContentSize().height * 0.5)
			table.insert(self.skillCells, cell)
		else
			-- none
			local lblNone = cc.Label:createWithTTF("无", GameConfig.DEFAULT_FONT_PATH, 22)
			lblNone:setAnchorPoint(0, 1)
			lblNone:setColor(COLOR3B_BLACK)
			lblNone:setPosition(10.5, skillBorder:getContentSize().height - 5 - (i - 1) * 32)
			skillBorder:addChild(lblNone)
		end
	end

	-- 描述
	local tabDescription = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabDescription:setAnchorPoint(0, 1)
	tabDescription:setPosition(tabSkill:getPositionX(), skillBorder:getPositionY() - skillBorder:getContentSize().height - 10)
	layer:addChild(tabDescription)
	local lblDescriptionTitle = cc.Label:createWithTTF("描述", GameConfig.DEFAULT_FONT_PATH, 22)
	lblDescriptionTitle:setAnchorPoint(0, 0.5)
	lblDescriptionTitle:setPosition(lblSkillTab:getPosition())
	tabDescription:addChild(lblDescriptionTitle)

	local descriptionBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 30, 30))
	descriptionBorder:setPreferredSize(CCSizeMake(360, 35))
	descriptionBorder:setAnchorPoint(0, 1)
	descriptionBorder:setPosition(tabDescription:getPositionX(), tabDescription:getPositionY() - tabDescription:getContentSize().height - 10)
	layer:addChild(descriptionBorder)
	self.descriptionBorder = descriptionBorder
	local lblDescription = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, 22)
	lblDescription:setAnchorPoint(0, 1)
	lblDescription:setColor(COLOR3B_BLACK)
	lblDescription:setDimensions(360 - 2 * 10.5, 0)
	lblDescription:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
  	lblDescription:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_TOP)
  	lblDescription:setPosition(10.5, descriptionBorder:getContentSize().height - 5)
  	descriptionBorder:addChild(lblDescription)
  	self.lblDescription = lblDescription

	-- 效果
	local tabEffect = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabEffect:setAnchorPoint(0, 1)
	tabEffect:setPosition(tabDescription:getPositionX(), descriptionBorder:getPositionY() - descriptionBorder:getContentSize().height - 10)
	layer:addChild(tabEffect)
	self.tabEffect = tabEffect
	local lblEffectTitle = cc.Label:createWithTTF("效果", GameConfig.DEFAULT_FONT_PATH, 22)
	lblEffectTitle:setAnchorPoint(0, 0.5)
	lblEffectTitle:setPosition(lblSkillTab:getPosition())
	tabEffect:addChild(lblEffectTitle)

	local effectBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 30, 30))
	effectBorder:setPreferredSize(CCSizeMake(360, 70))
	effectBorder:setAnchorPoint(0, 1)
	effectBorder:setPosition(tabEffect:getPositionX(), tabEffect:getPositionY() - tabEffect:getContentSize().height - 10)
	layer:addChild(effectBorder)
	self.effectBorder = effectBorder
	local lblPowerText = cc.Label:createWithTTF("威力", GameConfig.DEFAULT_FONT_PATH, 22)
	lblPowerText:setAnchorPoint(0, 1)
	lblPowerText:setColor(COLOR3B_BLACK)
	lblPowerText:setPosition(10.5, effectBorder:getContentSize().height - 5)
	effectBorder:addChild(lblPowerText)
	local lblHitRateText = cc.Label:createWithTTF("命中", GameConfig.DEFAULT_FONT_PATH, 22)
	lblHitRateText:setAnchorPoint(0, 1)
	lblHitRateText:setColor(COLOR3B_BLACK)
	lblHitRateText:setPosition(10.5, effectBorder:getContentSize().height - 5 - 32)
	effectBorder:addChild(lblHitRateText)
	local lblPower = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, 22)
	lblPower:setAnchorPoint(1, 1)
	lblPower:setColor(COLOR3B_BLACK)
	lblPower:setPosition(lblPowerText:getPositionX() + 150, lblPowerText:getPositionY())
	effectBorder:addChild(lblPower)
	self.lblPower = lblPower
	local lblHitRate = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, 22)
	lblHitRate:setAnchorPoint(1, 1)
	lblHitRate:setColor(COLOR3B_BLACK)
	lblHitRate:setPosition(lblHitRateText:getPositionX() + 150, lblHitRateText:getPositionY())
	effectBorder:addChild(lblHitRate)
	self.lblHitRate = lblHitRate

	-- 选中框 默认隐藏
	self.selection = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/select_border.png", CCRectMake(10, 10, 30, 30))
	self.selection:setAnchorPoint(0.5, 1)
	self.selection:setPreferredSize(CCSizeMake(350, 32))
	self.selection:setVisible(false)
	skillBorder:addChild(self.selection, self.SELECTION_ZORDER)

	self.swapSelection = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/select_border2.png", CCRectMake(10, 10, 30, 30))
	self.swapSelection:setAnchorPoint(0.5, 1)
	self.swapSelection:setPreferredSize(self.selection:getContentSize())
	self.swapSelection:setVisible(false)
	skillBorder:addChild(self.swapSelection, self.SWAP_SELECTION_ZORDER)
end

function PokemonSkillViewAdapter:remove()
	if self.layer then
		self.layer:removeFromParent()
	end
end

function PokemonSkillViewAdapter:activate()
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		local kbdListener = Win32EventListenerKeyboard:createWithTarget(self.layer)
		kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
		Win32Notifier:getInstance():addEventListener(kbdListener)
		self.kbdListener = kbdListener
	end
	self.selection:setVisible(true)
	if #self.skillModels > 0 then
		self:select(1)
	end
end

function PokemonSkillViewAdapter:blur()
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
		Win32Notifier:getInstance():removeEventListener(self.kbdListener)
		self.kbdListener = nil
	end
	self:unselect()
	self.selection:setVisible(false)
end

function PokemonSkillViewAdapter:onKeyboardPressed(keyCode)
	log("PokemonSkillViewAdapter:onKeyboardPressed", keyCode)
	if keyCode == GameSettings.cancelKey then
		self:blur()
	elseif keyCode == GameSettings.upKey then
		self:shiftUp()
	elseif keyCode == GameSettings.downKey then
		self:shiftDown()
	elseif keyCode == GameSettings.confirmKey then
		-- 交换位置
		if not self.inSwap then
			self.inSwap = true
			self.swapSelection:setPosition(self.selection:getPosition())
			self.swapSelection:setVisible(true)
			self.swapIndex = self.selectedIndex
		else
			if self.swapIndex ~= self.selectedIndex then
				-- swap
				self.relatedPokemon.skills[self.swapIndex], self.relatedPokemon.skills[self.selectedIndex] = self.relatedPokemon.skills[self.selectedIndex], self.relatedPokemon.skills[self.swapIndex]
				self.skillModels[self.swapIndex], self.skillModels[self.selectedIndex] = self.skillModels[self.selectedIndex], self.skillModels[self.swapIndex]
				self.skillCells[self.swapIndex], self.skillCells[self.selectedIndex] = self.skillCells[self.selectedIndex], self.skillCells[self.swapIndex]
				local tmp = ccp(self.skillCells[self.swapIndex]:getPosition())
				self.skillCells[self.swapIndex]:setPosition(self.skillCells[self.selectedIndex]:getPosition())
				self.skillCells[self.selectedIndex]:setPosition(tmp)
				self:select(self.selectedIndex, true)
			end
			self.swapSelection:setVisible(false)
			self.swapIndex = nil
			self.inSwap = false
		end
	end
end

function PokemonSkillViewAdapter:shiftUp()
	if self.selectedIndex and self.selectedIndex <= 1 then
		return
	end
	self:select(self.selectedIndex - 1)
end

function PokemonSkillViewAdapter:shiftDown()
	if self.selectedIndex and self.selectedIndex >= #self.skillModels then
		return
	end
	self:select(self.selectedIndex + 1)
end

function PokemonSkillViewAdapter:select(index, refresh)
	if not refresh and self.selectedIndex == index then
		return
	end

	self.selection:setPosition(360 * 0.5, self.skillCells[index]:getPositionY() + 5.5)
	-- 显示描述信息和效果信息
	local skillModel = self.skillModels[index]
	local typeMap = { "物理", "特殊", "变化" }
	local skillType = typeMap[skillModel.type]
	self.lblDescription:setString(string.format("%s(%s)", skillModel.description, skillType))
	self.descriptionBorder:setPreferredSize(CCSizeMake(360, self.lblDescription:getContentSize().height))
  	self.lblDescription:setPosition(10.5, self.descriptionBorder:getContentSize().height + 10)
	self.tabEffect:setPositionY(self.descriptionBorder:getPositionY() - self.descriptionBorder:getContentSize().height - 10)
	self.effectBorder:setPositionY(self.tabEffect:getPositionY() - self.tabEffect:getContentSize().height - 10)
	self.lblPower:setString(skillModel.attack == DBNULL and "-" or tostring(skillModel.attack))
	self.lblHitRate:setString(skillModel.hitRate == DBNULL and "-" or tostring(skillModel.hitRate))

	self.selectedIndex = index
end

function PokemonSkillViewAdapter:unselect()
	self.lblDescription:setString("")
	self.descriptionBorder:setPreferredSize(CCSizeMake(360, 35))
	self.tabEffect:setPositionY(self.descriptionBorder:getPositionY() - self.descriptionBorder:getContentSize().height - 10)
	self.effectBorder:setPositionY(self.tabEffect:getPositionY() - self.tabEffect:getContentSize().height - 10)
	self.lblPower:setString("")
	self.lblHitRate:setString("")

	self.selectedIndex = nil
end