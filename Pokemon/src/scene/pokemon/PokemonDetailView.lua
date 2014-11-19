--[[
	Description: Pokemon detail view
	Author: M.Wan
	Date: 11/16/2014
]]

class("PokemonDetailView", psGameLayer)

require "src/scene/pokemon/PokemonBasicViewAdapter"
require "src/scene/pokemon/PokemonAbilityViewAdapter"
require "src/scene/pokemon/PokemonSkillViewAdapter"

PokemonDetailView.relatedPokemon = nil
PokemonDetailView.selectedIndex = nil

PokemonDetailView.menu = nil		-- list menu
PokemonDetailView.tab1 = nil
PokemonDetailView.lblTab1 = nil
PokemonDetailView.tab2 = nil
PokemonDetailView.lblTab2 = nil
PokemonDetailView.tab3 = nil
PokemonDetailView.lblTab3 = nil
PokemonDetailView.border1 = nil
PokemonDetailView.lblContent1 = nil
PokemonDetailView.border2 = nil
PokemonDetailView.lblContent2 = nil
PokemonDetailView.border3 = nil
PokemonDetailView.lblContent3 = nil

PokemonDetailView.adapter = nil		-- 当前适配器

PokemonDetailView.LIST_STRS = {
	"精灵资料",
	"能力信息",
	"技能信息",
	"种族信息",
}

PokemonDetailView.__create = psGameLayer.create

function PokemonDetailView:create(pokemon)
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setCascadeOpacityEnabled(true)
	mask:retain()
	local layer = PokemonDetailView:createWithTransitions(
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15))
		)
	layer.mask = mask
	layer:init(pokemon)

	return layer
end

function PokemonDetailView:init(pokemon)
	self.relatedPokemon = pokemon

	local root = ModalLayer:create()
	self:addChild(root)

	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/pokemon/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self:addChild(bg)

	local list = CommonListMenu:create(self.LIST_STRS, CCSizeMake(175, 200))
	list:setAnchorPoint(0, 1)
	list:setItemSelectedScript(MakeScriptHandler(self, self.onMenuItemSelected))
	list:setItemChangedScript(MakeScriptHandler(self, self.onMenuItemChanged))
	list:setPosition(0, winSize.height)
	list:setCancelScript(MakeScriptHandler(self, self.quit))
	self:addChild(list)
	self.menu = list

	local pokemonBg = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_gray.png", CCRectMake(10, 10, 31, 31))
	pokemonBg:setPreferredSize(CCSizeMake(225, 325))
	pokemonBg:setAnchorPoint(ccp(0, 1))
	pokemonBg:setPosition(185, winSize.height - 20)
	self:addChild(pokemonBg)

	-- no
	local lblNo = self:createCommonLabel("No." .. pokemon.model.id)
	lblNo:setPosition(10, pokemonBg:getContentSize().height - 10)
	pokemonBg:addChild(lblNo)

	local whiteBg = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/back_white.png", CCRectMake(10, 10, 31, 31))
	whiteBg:setPreferredSize(CCSizeMake(200, 200))
	whiteBg:setPosition(pokemonBg:getContentSize().width * 0.5, pokemonBg:getContentSize().height * 0.58)
	pokemonBg:addChild(whiteBg)

	-- pokemon image
	local formatStr = pokemon.isShining and "%03d_s.png" or "%03d.png"
	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemons.rc", string.format(formatStr, pokemon.id), GameConfig.ZIP_PASSWORD)
	local sp = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	sp:setPosition(whiteBg:getContentSize().width * 0.5, whiteBg:getContentSize().height * 0.5)
	sp:setScale(2.2)
	whiteBg:addChild(sp)

	-- pokmeon name
	local lblName = self:createCommonLabel(pokemon.model.name)
	lblName:setAnchorPoint(0.5, 0.5)
	lblName:setPosition(pokemonBg:getContentSize().width * 0.5, pokemonBg:getContentSize().height * 0.2)
	pokemonBg:addChild(lblName)

	-- pokemon ball
	local spBall = cc.Sprite:createWithSpriteFrameName("images/pokemon/pokemon_ball_" .. pokemon.ballId .. ".png")
	spBall:setPosition(pokemonBg:getContentSize().width * 0.35, pokemonBg:getContentSize().height * 0.08)
	pokemonBg:addChild(spBall)

	-- level
	local lblLv = self:createCommonLabel("Lv." .. pokemon.level)
	lblLv:setPosition(pokemonBg:getContentSize().width * 0.48, pokemonBg:getContentSize().height * 0.08)
	lblLv:setAnchorPoint(0, 0.5)
	pokemonBg:addChild(lblLv)

	local lblTip = cc.Label:createWithTTF("【按取消键返回】", GameConfig.DEFAULT_FONT_PATH, 14)
	lblTip:setAnchorPoint(0, 0)
	lblTip:setColor(COLOR3B_BLACK)
	lblTip:setPosition(winSize.width * 0.02, winSize.height * 0.02)
	self:addChild(lblTip)

	self:select(1)

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	if self.mask then
		self:addChild(self.mask, 999)
		self.mask:release()
	end
end

function PokemonDetailView:onNodeEvent(event)
	if event == "enter" then
		self.mask:runAction(cc.FadeOut:create(0.15))
	end
end

function PokemonDetailView:select(index)
	if self.selectedIndex == index then
		return
	end

	if index == 1 then
		local adapter = PokemonBasicViewAdapter:new()
		adapter:adapt(self)
	elseif index == 2 then
		local adapter = PokemonAbilityViewAdapter:new()
		adapter:adapt(self)
	elseif index == 3 then
		local adapter = PokemonSkillViewAdapter:new()
		adapter:adapt(self)
	end
	self.selectedIndex = index
end

function PokemonDetailView:quit()
	local quitAction = cc.Sequence:create(
		cc.FadeIn:create(0.15),
		cc.CallFunc:create(MakeScriptHandler(self, self.onQuit))
		)
	self.mask:runAction(quitAction)
end
function PokemonDetailView:onQuit()
	self.menu:markExit(true)
	self:removeFromParent()
end

function PokemonDetailView:onMenuItemSelected(menu, item)
	Notifier:notify(NotifyEvents.PokemonView.DetailMenuItemSelected, menu, item)
end

function PokemonDetailView:onMenuItemChanged(oldIndex, newIndex)
	Notifier:notify(NotifyEvents.PokemonView.DetailMenuItemChanged, oldIndex, newIndex)
end

function PokemonDetailView:createCommonLabel(text, color)
	color = color or COLOR3B_WHITE

	local lbl = cc.Label:createWithTTF(text, GameConfig.DEFAULT_FONT_PATH, 22)
	lbl:setColor(color)
	lbl:setAnchorPoint(ccp(0, 1))
	lbl:enableShadow()
	return lbl
end