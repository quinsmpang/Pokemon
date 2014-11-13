--[[
	Description: Pokemon main view
	Author: M.Wan
	Date: 10/26/2014
]]

class("PokemonMainView", psGameLayer)

PokemonMainView.selection = nil		-- 选中框
PokemonMainView.pokemonCells = nil

PokemonMainView.enterType = nil		-- 界面用途
PokemonMainView.pokemonList = nil	-- 深拷贝过来的精灵数据，需要重排序，濒死的要排在最后
PokemonMainView.selectedIndex = nil

PokemonMainView.SELECTION_ZORDER = 100

PokemonMainView.ENTER_TYPE = {
	VIEW_POKEMON = 1,	-- 查看精灵信息
	USE_ITEM = 2,		-- 使用道具
	CARRY_ITEM = 3,		-- 携带道具
}

PokemonMainView.__create = psGameLayer.create

function PokemonMainView:create(enterType)
	-- 本身无法修改opacity, 只好借助一个遮罩层来模拟FadeIn和FadeOut的效果
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setCascadeOpacityEnabled(true)
	mask:retain()
	local layer = PokemonMainView:createWithTransitions(
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15))
		)
	layer.mask = mask
	layer:init(enterType)

	return layer
end

function PokemonMainView:init(enterType)
	enterType = enterType or self.ENTER_TYPE.VIEW_POKEMON
	self.enterType = enterType

	local modalLayer = ModalLayer:create()
	self:addChild(modalLayer)
	self.root = modalLayer

	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/pokemon/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.root:addChild(bg)

	local spPokemon = cc.Sprite:createWithSpriteFrameName("images/pokemon/pokemon_title.png")
	spPokemon:setPosition(winSize.width * 0.8, winSize.height * 0.9)
	self.root:addChild(spPokemon)

	local lblTip = cc.Label:createWithTTF("【按取消键返回】", GameConfig.DEFAULT_FONT_PATH, 14)
	lblTip:setColor(COLOR3B_BLACK)
	lblTip:setPosition(winSize.width * 0.12, winSize.height * 0.88)
	self.root:addChild(lblTip)

	self:showPokemons()

	self.selection = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/select_border.png", CCRectMake(10, 10, 30, 30))
	self.selection:setPreferredSize(CCSizeMake(winSize.width * 0.4, winSize.height * 0.18))
	self.root:addChild(self.selection)

	self:selectPokemon(1)

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	if self.mask then
		self.root:addChild(self.mask, 999)
		self.mask:release()
	end
end

function PokemonMainView:onNodeEvent(event)
	if event == "enter" then
		self.mask:runAction(cc.FadeOut:create(0.15))

		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		end
	elseif event == "exit" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
			self.kbdListener = nil
		end
	end
end

function PokemonMainView:onKeyboardPressed(keyCode)
	Notifier:notify(NotifyEvents.PokemonView.MainViewKeyResponsed, keyCode)
end

function PokemonMainView:selectPokemon(index)
	if index == self.selectedIndex then
		return
	end

	local selectCell = self.pokemonCells[index]
	if selectCell then
		self.selection:setPosition(selectCell:getPosition())
		self.selectedIndex = index
	end
end

function PokemonMainView:shift(offset)
	local newIndex = self.selectedIndex + offset
	if newIndex < 1 then
		newIndex = 1
	elseif newIndex > #self.pokemonList then
		newIndex = #self.pokemonList
	end

	self:selectPokemon(newIndex)
end

function PokemonMainView:showPokemons()
	assert(type(DataCenter.carriedPokemons) == "table", "Invalid data")

	self.pokemonList = {}
	self.pokemonCells = {}
	table.shallowCopy(self.pokemonList, DataCenter.carriedPokemons)
	-- resort pokemon list, todo

	local winSize = cc.Director:getInstance():getWinSize()
	for i = 0, 5 do
		local cell = self:createPokemonCell(i)
		cell:setPosition(winSize.width * (i % 2 * 0.44 + 0.28), winSize.height * (0.7 - math.floor(i / 2) * 0.2))
		self.root:addChild(cell)
		table.insert(self.pokemonCells, cell)
	end
end

function PokemonMainView:createPokemonCell(index)
	local winSize = cc.Director:getInstance():getWinSize()

	local cell = nil
	if self.pokemonList[index + 1] then
		local pokemon = self.pokemonList[index + 1]
		if pokemon.currentHp > 0 then
			cell = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_aqua.png", CCRectMake(10, 10, 30, 30))
		else
			cell = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_rose.png", CCRectMake(10, 10, 30, 30))
		end
		cell:setPreferredSize(CCSizeMake(winSize.width * 0.4, winSize.height * 0.18))

		local data = ZipHelper:getInstance():getFileDataInZip("images/pokemon_icon.rc", string.format("%03d.gif", pokemon.id), GameConfig.ZIP_PASSWORD)
		local frames = ImageUtils:getInstance():getGifFrames(data)

		local hpRate = pokemon.currentHp / pokemon.basicData.hp
		local dt = 0.1
		local hpFrameName = "images/pokemon/hp_green.png"
		if hpRate <= 0 then
			dt = 0.8
		elseif hpRate <= 0.1 then
			dt = 0.5
			hpFrameName = "images/pokemon/hp_red.png"
		elseif hpRate <= 0.5 then
			dt = 0.2
			hpFrameName = "images/pokemon/hp_yellow.png"
		end
		local animate = ImageUtils:getInstance():createAnimationByFrames(frames, dt)
		local action = cc.RepeatForever:create(animate)
		local sp = cc.Sprite:create()
		sp:setPosition(cell:getContentSize().width * 0.12, cell:getContentSize().height * 0.6)
		sp:setScale(2)
		cell:addChild(sp)
		sp:runAction(action)

		-- 名称
		local lblName = cc.Label:createWithTTF(pokemon.model.name, GameConfig.DEFAULT_FONT_PATH, 17)
		lblName:enableShadow()
		lblName:setPosition(cell:getContentSize().width * 0.22, cell:getContentSize().height * 0.65)
		lblName:setAnchorPoint(ccp(0, 0.5))
		lblName:setDimensions(150, 20)
		lblName:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
     	lblName:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
		cell:addChild(lblName)

		-- 等级
		local lblLv = cc.Label:createWithTTF("Lv " .. pokemon.level, GameConfig.DEFAULT_FONT_PATH, 17)
		lblLv:enableShadow()
		lblLv:setPosition(cell:getContentSize().width * 0.22, cell:getContentSize().height * 0.35)
		lblLv:setAnchorPoint(ccp(0, 0.5))
		lblLv:setDimensions(100, 20)
		lblLv:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
     	lblLv:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
		cell:addChild(lblLv)

		-- 性别
		local spGender = cc.Sprite:createWithSpriteFrameName(pokemon.gender == 0 and "images/pokemon/icon_male.png" or "images/pokemon/icon_female.png")
		spGender:setPosition(cell:getContentSize().width * 0.42, cell:getContentSize().height * 0.31)
		cell:addChild(spGender)

		-- hp槽
		local hpBack = cc.Sprite:createWithSpriteFrameName("images/pokemon/hp_back.png")
		hpBack:setPosition(cell:getContentSize().width * 0.75, cell:getContentSize().height * 0.6)
		cell:addChild(hpBack)
		local spHp = cc.Sprite:createWithSpriteFrameName(hpFrameName)
		local hpBar = cc.ProgressTimer:create(spHp)
		hpBar:setPosition(hpBack:getPosition())
		hpBar:setType(cc.PROGRESS_TIMER_TYPE_BAR)
		-- 从左边中间开始
		hpBar:setMidpoint(ccp(0, 0.5))
		-- 只控制水平方向长短
		hpBar:setBarChangeRate(ccp(1, 0))
		hpBar:setPercentage(hpRate * 100)
		cell:addChild(hpBar)

		-- hp label
		local lblHp = cc.Label:createWithTTF(pokemon.currentHp .. "/" .. pokemon.basicData.hp, GameConfig.DEFAULT_FONT_PATH, 18)
		lblHp:enableShadow()
		lblHp:setPosition(cell:getContentSize().width * 0.95, cell:getContentSize().height * 0.35)
		lblHp:setAnchorPoint(1, 0.5)
		lblHp:setDimensions(100, 20)
		lblHp:setHorizontalAlignment(cc.TEXT_ALIGNMENT_RIGHT)
     	lblHp:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
     	cell:addChild(lblHp)

     	-- 异常状态
     	if pokemon.status > 0 then
     		local spStatus = cc.Sprite:createWithSpriteFrameName("images/pokemon/icon_state_" .. pokemon.status .. ".png")
     		spStatus:setPosition(cell:getContentSize().width * 0.58, cell:getContentSize().height * 0.33)
     		cell:addChild(spStatus)
     	end
	else
		cell = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_gray.png", CCRectMake(10, 10, 30, 30))
		cell:setPreferredSize(CCSizeMake(winSize.width * 0.4, winSize.height * 0.18))

		local label = cc.Label:createWithTTF("无携带精灵", GameConfig.DEFAULT_FONT_PATH, 20)
		label:enableShadow()
		label:setPosition(cell:getContentSize().width * 0.5, cell:getContentSize().height * 0.5)
		cell:addChild(label)
	end

	return cell
end