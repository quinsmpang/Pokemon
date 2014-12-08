--[[
	Description: Collection size view adapter
	Author: M.Wan
	Date: 12/7/2014
]]

luaClass("CollectionSizeViewAdapter")

CollectionSizeViewAdapter.pokemonModel = nil
CollectionSizeViewAdapter.bg = nil

function CollectionSizeViewAdapter:adapt(detailView)
	assert(detailView and detailView.__className == "CollectionDetailView", "invalid argument")
	if detailView.adapter then
		detailView.detailBg:removeAllChildren()
	end
	detailView.adapter = self

	local detailBg = detailView.detailBg
	local pokemonModel = detailView.pokemonModel
	local bgSize = detailBg:getContentSize()
	self.pokemonModel = pokemonModel

	local capInsets = CCRectMake(2, 2, 6, 6)
	local bg = cc.Scale9Sprite:createWithSpriteFrameName("images/collection/shallow_gray.png", capInsets)
	bg:setPreferredSize(CCSizeMake(bgSize.width * 0.84, bgSize.height * 0.8))
	bg:setPosition(bgSize.width * 0.5, bgSize.height * 0.5)
	detailBg:addChild(bg)

	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemons.rc", string.format("%03d.png", pokemonModel.id), GameConfig.ZIP_PASSWORD)
	local spPokemon = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	spPokemon:setAnchorPoint(0.5, 0)
	-- spPokemon:setScale(3)
	spPokemon:setColor(COLOR3B_BLACK)
	spPokemon:setPosition(bg:getContentSize().width * 0.35, bg:getContentSize().height * 0.1)
	bg:addChild(spPokemon)

	local genderStr = DataCenter.currentPlayerData.gender == Enumerations.GENDER.MALE and "male" or "female"
	local spTrainer = cc.Sprite:createWithSpriteFrameName("images/common/" .. genderStr .. "_hero.png")
	spTrainer:setAnchorPoint(0.5, 0)
	spTrainer:setColor(COLOR3B_BLACK)
	spTrainer:setPosition(bg:getContentSize().width * 0.7, bg:getContentSize().height * 0.1)
	bg:addChild(spTrainer)

	local pokemonHeight = pokemonModel.height
	local trainerHeight = 1.6
	-- 当精灵的高度超出训练师高度一定比例(越出背景边界时), 缩放训练师比例, 让精灵比例占满高度
	local defaultTimes = spTrainer:getContentSize().height / spPokemon:getContentSize().height
	if trainerHeight < pokemonHeight then
		local times = pokemonHeight / trainerHeight
		defaultTimes = defaultTimes * times
		if spPokemon:getContentSize().height * defaultTimes > bg:getContentSize().height * 0.85 then
			defaultTimes = defaultTimes * bg:getContentSize().height * 0.85 / (spPokemon:getContentSize().height * defaultTimes)
			spTrainer:setScale(defaultTimes / times)
		end
	else
		defaultTimes = defaultTimes * pokemonHeight / trainerHeight
	end
	spPokemon:setScale(defaultTimes)
end