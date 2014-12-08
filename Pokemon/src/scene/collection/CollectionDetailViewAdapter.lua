--[[
	Description: Collection detail view adapter
	Author: M.Wan
	Date: 12/5/2014
]]

luaClass("CollectionDetailViewAdapter")

CollectionDetailViewAdapter.pokemonModel = nil
CollectionDetailViewAdapter.bg2 = nil

function CollectionDetailViewAdapter:adapt(detailView)
	assert(detailView and detailView.__className == "CollectionDetailView", "invalid argument")
	if detailView.adapter then
		detailView.detailBg:removeAllChildren()
	end
	detailView.adapter = self

	local winSize = cc.Director:getInstance():getWinSize()
	local detailBg = detailView.detailBg
	local pokemonModel = detailView.pokemonModel
	local bgSize = detailBg:getContentSize()
	self.pokemonModel = pokemonModel

	local capInsets = CCRectMake(2, 2, 6, 6)
	local bg1 = cc.Scale9Sprite:createWithSpriteFrameName("images/collection/shallow_gray.png", capInsets)
	bg1:setPreferredSize(CCSizeMake(bgSize.width * 0.3, bgSize.height * 0.8))
	bg1:setAnchorPoint(0, 0.5)
	bg1:setPosition(bgSize.width * 0.08, bgSize.height * 0.5)
	detailBg:addChild(bg1)

	local bg2 = cc.Scale9Sprite:createWithSpriteFrameName("images/collection/shallow_gray.png", capInsets)
	bg2:setPreferredSize(CCSizeMake(bgSize.width * 0.52, bgSize.height * 0.8))
	bg2:setAnchorPoint(1, 0.5)
	bg2:setPosition(bgSize.width * 0.92, bgSize.height * 0.5)
	detailBg:addChild(bg2)
	self.bg2 = bg2

	local spPokemon = cc.Sprite:create()
	spPokemon:setPosition(bg1:getContentSize().width * 0.5, bg1:getContentSize().height * 0.5)
	spPokemon:setScale(1.6)
	bg1:addChild(spPokemon)

	local animation = nil
	if CollectionAnimationCache.animationCache[pokemonModel.id] then
		-- 有缓存则读取
		animation = CollectionAnimationCache.animationCache[pokemonModel.id]:clone()	-- 注意, 这里不需要autorelease, 在clone方法中已经帮你做了
		spPokemon:runAction(cc.RepeatForever:create(animation))
	else
		-- 首次读取gif并缓存
		local num = math.floor(pokemonModel.id / 100) + 1
		local data = ZipHelper:getInstance():getFileDataInZip(string.format("images/pokemon_gif%d.rc", num), string.format("%03d.gif", pokemonModel.id), GameConfig.ZIP_PASSWORD)
		local frames = ImageUtils:getInstance():getGifFrames(data)
		local animation = ImageUtils:getInstance():createAnimationByFrames(frames, 0.1)
		CollectionAnimationCache:cache(pokemonModel.id, animation)
		spPokemon:runAction(cc.RepeatForever:create(animation))
	end

	self:showPokemonDetails()
end

function CollectionDetailViewAdapter:showPokemonDetails()
	local lblName = cc.Label:createWithTTF(string.format("No.%03d  %s", self.pokemonModel.id, self.pokemonModel.name), GameConfig.DEFAULT_FONT_PATH, 18)
	lblName:setColor(COLOR3B_BLACK)
	lblName:setAnchorPoint(0, 0.5)
	lblName:setPosition(self.bg2:getContentSize().width * 0.05, self.bg2:getContentSize().height * 0.95)
	self.bg2:addChild(lblName)

	local lblType = cc.Label:createWithTTF(self.pokemonModel.type .. "口袋妖怪", GameConfig.DEFAULT_FONT_PATH, 18)
	lblType:setColor(COLOR3B_BLACK)
	lblType:setAnchorPoint(0, 0.5)
	lblType:setPosition(lblName:getPositionX(), lblName:getPositionY() - self.bg2:getContentSize().height * 0.1)
	self.bg2:addChild(lblType)

	local lblHW = cc.Label:createWithTTF(string.format("身高: %.1fm\t体重: %.1fkg", self.pokemonModel.height, self.pokemonModel.weight), GameConfig.DEFAULT_FONT_PATH, 18)
	lblHW:setColor(COLOR3B_BLACK)
	lblHW:setAnchorPoint(0, 0.5)
	lblHW:setPosition(lblType:getPositionX(), lblType:getPositionY() - self.bg2:getContentSize().height * 0.1)
	self.bg2:addChild(lblHW)

	local lblRacialTitle = cc.Label:createWithTTF("种族值:", GameConfig.DEFAULT_FONT_PATH, 18)
	lblRacialTitle:setColor(COLOR3B_BLACK)
	lblRacialTitle:setAnchorPoint(0, 0.5)
	lblRacialTitle:setPosition(lblHW:getPositionX(), lblHW:getPositionY() - self.bg2:getContentSize().height * 0.1)
	self.bg2:addChild(lblRacialTitle)

	-- racial values
	local racialTitles = { "HP:", "物攻:", "物防:", "特攻:", "特防:", "速度:" }
	local lbl = nil
	for i = 1, 6 do
		lbl = cc.Label:createWithTTF(racialTitles[i] .. self.pokemonModel.racial[i], GameConfig.DEFAULT_FONT_PATH, 18)
		lbl:setColor(COLOR3B_BLACK)
		lbl:setAnchorPoint(0, 0.5)
		lbl:setPosition(self.bg2:getContentSize().width * (0.12 + (i - 1) % 3 * 0.28), lblRacialTitle:getPositionY() - self.bg2:getContentSize().height * 0.1 * (math.floor((i - 1) / 3) + 1))
		self.bg2:addChild(lbl)
	end

	local lblDescription = cc.Label:createWithTTF(self.pokemonModel.description, GameConfig.DEFAULT_FONT_PATH, 18)
	lblDescription:setDimensions(self.bg2:getContentSize().width * 0.9, self.bg2:getContentSize().height * 0.4)
	lblDescription:setColor(COLOR3B_BLACK)
	lblDescription:setAnchorPoint(0, 1)
	lblDescription:setPosition(lblRacialTitle:getPositionX(), lblRacialTitle:getPositionY() - self.bg2:getContentSize().height * 0.3)
	self.bg2:addChild(lblDescription)
end