--[[
	Description: pokemon ui controller
	Author: M.Wan
	Date: 08/31/2014
]]

class("PokemonViewController", psViewController)

require "src/scene/pokemon/PokemonMainView"
require "src/scene/pokemon/PokemonDetailView"

PokemonViewController.mainView = nil
PokemonViewController.detailView = nil

PokemonViewController.inExchangeState = nil		-- 是否处于交换精灵的状态

PokemonViewController.LIST_STRS = {
	"查看强度",
	"交换位置",
	"携带物品",
	"返回",
}

PokemonViewController.resources = {
	"images/pokemon.plist",
	"images/pokemon.pvr.ccz",
}

function PokemonViewController:load()
	log("PokemonViewController:load")
	self:loadResources()
	self:addObservers()

	self:renderView()
end

function PokemonViewController:unload()
	log("PokemonViewController:unload")
	self:removeObservers()
	self:cleanResources()

	self.mainView:removeFromParent()
end

function PokemonViewController:loadResources()
	log("PokemonViewController:loadResources")
	LoadSpriteFrames(self.resources)
end

function PokemonViewController:cleanResources()
	log("PokemonViewController:cleanResources")
	RemoveSpriteFrames(self.resources)
end

function PokemonViewController:addObservers()
	log("PokemonViewController:addObservers")
	Notifier:addObserver(NotifyEvents.PokemonView.MainViewKeyResponsed, self, self.onMainViewKeyResponsed)
	Notifier:addObserver(NotifyEvents.PokemonView.ExchangePokemonPosition, self, self.onExchangePokemonPosition)
	Notifier:addObserver(NotifyEvents.PokemonView.DetailMenuItemSelected, self, self.onDetailMenuItemSelected)
	Notifier:addObserver(NotifyEvents.PokemonView.DetailMenuItemChanged, self, self.onDetailMenuItemChanged)
end

function PokemonViewController:removeObservers()
	log("PokemonViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.PokemonView.MainViewKeyResponsed, self)
	Notifier:removeObserver(NotifyEvents.PokemonView.ExchangePokemonPosition, self)
	Notifier:removeObserver(NotifyEvents.PokemonView.DetailMenuItemSelected, self)
	Notifier:removeObserver(NotifyEvents.PokemonView.DetailMenuItemChanged, self)
end

function PokemonViewController:renderView()
	log("PokemonViewController:renderView")
	local enterType = self:getScene():getIntAttribute(GameConfig.POKEMON_KEY)
	enterType = enterType or Enumerations.POKEMON_VIEW_SCENE_TYPE.VIEW_STATUS
	log("Pokemon view enter type: " .. enterType)

	local mainView = PokemonMainView:create(enterType)
	self:getScene():addChild(mainView)
	self.mainView = mainView

	self.inExchangeState = false
end

function PokemonViewController:onMainViewKeyResponsed(keyCode)
	if keyCode == GameSettings.cancelKey then
		if self.inExchangeState then
			self:endExchange()
			self.mainView:cancelExchange()
		else
			local quitAction = cc.Sequence:create(
				cc.FadeIn:create(0.15),
				cc.CallFunc:create(MakeScriptHandler(self, self.onQuit))
				)
			self.mainView.mask:runAction(quitAction)
		end
	elseif keyCode == GameSettings.upKey then
		self.mainView:shift(-2)
	elseif keyCode == GameSettings.downKey then
		self.mainView:shift(2)
	elseif keyCode == GameSettings.leftKey then
		self.mainView:shift(-1)
	elseif keyCode == GameSettings.rightKey then
		self.mainView:shift(1)
	elseif keyCode == GameSettings.confirmKey then
		-- 弹出列表，根据enterType不同 会不同
		local enterType = self:getScene():getIntAttribute(GameConfig.POKEMON_KEY)
		if enterType == Enumerations.POKEMON_VIEW_SCENE_TYPE.VIEW_STATUS then
			-- 精灵查看
			if self.inExchangeState then
				-- 交换位置
				self.mainView:exchangePokemonPosition()
				CallFunctionAsync(self, self.endExchange, 1)
			else
				-- 弹出列表
				local list = CommonListMenu:create(self.LIST_STRS, CCSizeMake(175, 200))
				list:setItemSelectedScript(MakeScriptHandler(self, self.onViewPokemonItemSelected))
				list:setAnchorPoint(1, 0)
				list:setPosition(cc.Director:getInstance():getWinSize().width, 0)
				self.viewPokemonList = list
				self:getScene():addChild(list)
			end
		elseif enterType == 2 then
			-- 使用道具
		elseif enterType == 3 then
			-- 携带道具
		end
	end
end
function PokemonViewController:onQuit()
	self:getScene():unloadViewController(self)
end
function PokemonViewController:endExchange()
	self.inExchangeState = false
end

function PokemonViewController:onViewPokemonItemSelected(menu, item)
	local index = item:getShowIndex()
	log("PokemonViewController:onViewPokemonItemSelected", index)
	if index == 0 then
		-- 查看强度
		local detailView = PokemonDetailView:create(self.mainView:getSelectedPokemon())
		self:getScene():addChild(detailView)
		self.detailView = detailView
	elseif index == 1 then
		-- 交换位置
		self.mainView:readyToExchangePosition()
		self.inExchangeState = true
		if self.viewPokemonList then
			self.viewPokemonList:markExit(true)
		end
	elseif index == 2 then
		-- 携带物品
	elseif index == 3 then
		-- 返回
		-- you must remove the listener here, otherwise it may cause an invalid pointer of current listener
		if self.viewPokemonList then
			self.viewPokemonList:markExit(true)
		end
	end
end

function PokemonViewController:onExchangePokemonPosition(index1, index2)
	DataCenter.carriedPokemons[index1], DataCenter.carriedPokemons[index2] = DataCenter.carriedPokemons[index2], DataCenter.carriedPokemons[index1]
end

function PokemonViewController:onDetailMenuItemSelected(menu, item)
	local index = item:getShowIndex()
	log("PokemonViewController:onDetailMenuItemSelected", index)
	if index == 2 then
		-- 技能信息
		local adapter = self.detailView.adapter
		adapter:activate()
	end
end

function PokemonViewController:onDetailMenuItemChanged(oldIndex, newIndex)
	log("PokemonViewController:onDetailMenuItemChanged", oldIndex, newIndex)
	if self.detailView then
		self.detailView:select(newIndex + 1)
	end
end