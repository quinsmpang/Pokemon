--[[
	Description: Pokemon basic info view adapter
	Author: M.Wan
	Date: 11/17/2014
]]

luaClass("PokemonBasicViewAdapter")

PokemonBasicViewAdapter.layer = nil

function PokemonBasicViewAdapter:adapt(detailView)
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

	-- 资料
	local tabData = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabData:setAnchorPoint(0, 1)
	tabData:setPosition(winSize.width * 0.52, winSize.height - 20)
	layer:addChild(tabData)
	local lblData = cc.Label:createWithTTF("资料", GameConfig.DEFAULT_FONT_PATH, 22)
	lblData:setAnchorPoint(0, 0.5)
	lblData:setPosition(tabData:getContentSize().width * 0.05, tabData:getContentSize().height * 0.5)
	tabData:addChild(lblData)

	local dataBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/common/back_white.png", CCRectMake(10, 10, 30, 30))
	dataBorder:setPreferredSize(CCSizeMake(210, 35))
	dataBorder:setAnchorPoint(0, 1)
	dataBorder:setPosition(tabData:getPositionX(), tabData:getPositionY() - tabData:getContentSize().height - 10)
	layer:addChild(dataBorder)
	local lblProp = cc.Label:createWithTTF("属性 /", GameConfig.DEFAULT_FONT_PATH, 22)
	lblProp:setAnchorPoint(0, 0.5)
	lblProp:setColor(COLOR3B_BLACK)
	lblProp:setPosition(dataBorder:getContentSize().width * 0.05, dataBorder:getContentSize().height * 0.5)
	dataBorder:addChild(lblProp)

	local props = pokemon.model.property
	local beginX = lblProp:getPositionX() + lblProp:getContentSize().width + 5
	for i, prop in ipairs(props) do
		local icon = cc.Sprite:createWithSpriteFrameName("images/pokemon/icon_prop_" .. prop .. ".png")
		icon:setAnchorPoint(0, 0.5)
		icon:setPosition(beginX + (i - 1) * (icon:getContentSize().width + 5), lblProp:getPositionY())
		dataBorder:addChild(icon)
	end

	-- 特性
	local tabSpeciality = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabSpeciality:setAnchorPoint(0, 1)
	tabSpeciality:setPosition(tabData:getPositionX(), dataBorder:getPositionY() - dataBorder:getContentSize().height - 10)
	layer:addChild(tabSpeciality)
	local lblSpecialityTitle = cc.Label:createWithTTF("特性", GameConfig.DEFAULT_FONT_PATH, 22)
	lblSpecialityTitle:setAnchorPoint(0, 0.5)
	lblSpecialityTitle:setPosition(lblData:getPosition())
	tabSpeciality:addChild(lblSpecialityTitle)

	local specialityBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/common/back_white.png", CCRectMake(10, 10, 30, 30))
	specialityBorder:setPreferredSize(CCSizeMake(360, 0))
	specialityBorder:setAnchorPoint(0, 1)
	specialityBorder:setPosition(tabSpeciality:getPositionX(), tabSpeciality:getPositionY() - tabSpeciality:getContentSize().height - 10)
	layer:addChild(specialityBorder)

	local speciality = pokemon.speciality
	local specialityModel = SpecialityInfo:create(speciality)

	local lblDescription = cc.Label:createWithTTF(specialityModel.description, GameConfig.DEFAULT_FONT_PATH, 22)
	lblDescription:setAnchorPoint(0, 1)
	lblDescription:setColor(COLOR3B_BLACK)
	lblDescription:setDimensions(360 - 2 * lblProp:getPositionX(), 0)
	lblDescription:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
  	lblDescription:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_TOP)
  	specialityBorder:addChild(lblDescription)
  	specialityBorder:setPreferredSize(CCSizeMake(360, dataBorder:getContentSize().height + lblDescription:getContentSize().height))

	local lblSpeciality = cc.Label:createWithTTF(specialityModel.name, GameConfig.DEFAULT_FONT_PATH, 22)
	lblSpeciality:setAnchorPoint(0, 1)
	lblSpeciality:setColor(COLOR3B_BLACK)
	lblSpeciality:setPosition(lblProp:getPositionX(), specialityBorder:getContentSize().height - 5)
	specialityBorder:addChild(lblSpeciality)
	lblDescription:setPosition(lblSpeciality:getPositionX(), lblSpeciality:getPositionY() - lblSpeciality:getContentSize().height - 5)

	-- 训练师笔记
	local tabNote = cc.Sprite:createWithSpriteFrameName("images/pokemon/tab_back.png")
	tabNote:setAnchorPoint(0, 1)
	tabNote:setPosition(tabData:getPositionX(), specialityBorder:getPositionY() - specialityBorder:getContentSize().height - 10)
	layer:addChild(tabNote)
	local lblNoteTitle = cc.Label:createWithTTF("训练师笔记", GameConfig.DEFAULT_FONT_PATH, 22)
	lblNoteTitle:setAnchorPoint(0, 0.5)
	lblNoteTitle:setPosition(lblData:getPosition())
	tabNote:addChild(lblNoteTitle)

	local noteBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/common/back_white.png", CCRectMake(10, 10, 30, 30))
	noteBorder:setPreferredSize(CCSizeMake(360, 105))
	noteBorder:setAnchorPoint(0, 1)
	noteBorder:setPosition(tabNote:getPositionX(), tabNote:getPositionY() - tabNote:getContentSize().height - 10)
	layer:addChild(noteBorder)

	local lblPersonality = cc.Label:createWithTTF("性格 / " .. Enumerations.PERSONALITY_NAME[pokemon.personality], GameConfig.DEFAULT_FONT_PATH, 22)
	lblPersonality:setAnchorPoint(0, 1)
	lblPersonality:setColor(COLOR3B_BLACK)
	lblPersonality:setPosition(lblProp:getPositionX(), noteBorder:getContentSize().height - 5)
	noteBorder:addChild(lblPersonality)
	local lblCaptureLv = cc.Label:createWithTTF("Lv." .. pokemon.captureLevel, GameConfig.DEFAULT_FONT_PATH, 22)
	lblCaptureLv:setAnchorPoint(0, 1)
	lblCaptureLv:setColor(COLOR3B_BLACK)
	lblCaptureLv:setPosition(lblPersonality:getPositionX(), lblPersonality:getPositionY() - 32)
	noteBorder:addChild(lblCaptureLv)
	local capturePlaceStr = "Unknown"
	if pokemon.capturePlace ~= DBNULL then
		if pokemon.capturePlace > 10000 then
			capturePlaceStr = Enumerations.CAPTURE_PLACES[pokemon.capturePlace]
		else
			local mapModel = MapInfo:create(pokemon.capturePlace)
			capturePlaceStr = "在" .. mapModel.name .. "相遇"
		end
	end
	local lblCapturePlace = cc.Label:createWithTTF(capturePlaceStr, GameConfig.DEFAULT_FONT_PATH, 22)
	lblCapturePlace:setAnchorPoint(0, 1)
	lblCapturePlace:setColor(COLOR3B_BLACK)
	lblCapturePlace:setPosition(lblCaptureLv:getPositionX(), lblCaptureLv:getPositionY() - 32)
	noteBorder:addChild(lblCapturePlace)
end

function PokemonBasicViewAdapter:remove()
	if self.layer then
		self.layer:removeFromParent()
	end
end