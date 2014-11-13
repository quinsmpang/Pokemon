--[[
	Description: pokemon ui controller
	Author: M.Wan
	Date: 08/31/2014
]]

class("PokemonViewController", psViewController)

require "src/view/pokemon/PokemonMainView"

PokemonViewController.mainView = nil

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
end

function PokemonViewController:removeObservers()
	log("PokemonViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.PokemonView.MainViewKeyResponsed, self)
end

function PokemonViewController:renderView()
	log("PokemonViewController:renderView")
	local enterType = self:getScene():getIntAttribute(GameConfig.POKEMON_KEY)
	enterType = enterType or 1
	log("Pokemon view enter type: " .. enterType)

	local mainView = PokemonMainView:create(enterType)
	self:getScene():addChild(mainView)
	self.mainView = mainView
end

function PokemonViewController:onMainViewKeyResponsed(keyCode)
	if keyCode == GameSettings.cancelKey then
		local quitAction = cc.Sequence:create(
			cc.FadeIn:create(0.15),
			cc.CallFunc:create(MakeScriptHandler(self, self.onQuit))
			)
		self.mainView.mask:runAction(quitAction)
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
		if enterType == 1 then
			-- 精灵查看
			local list = CommonListMenu:create(self.LIST_STRS, CCSizeMake(175, 200))
			list:setItemSelectedScript(MakeScriptHandler(self, self.onViewPokemonItemSelected))
			list:setAnchorPoint(1, 0)
			list:setPosition(cc.Director:getInstance():getWinSize().width, 0)
			self.viewPokemonList = list
			self:getScene():addChild(list)
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

function PokemonViewController:onViewPokemonItemSelected(menu, item)
	local index = item:getShowIndex()
	log("PokemonViewController:onViewPokemonItemSelected", index)
	if index == 0 then
	elseif index == 1 then
	elseif index == 2 then
	elseif index == 3 then
		-- you must remove the listener here, otherwise it may cause an invalid pointer of current listener
		if self.viewPokemonList then
			self.viewPokemonList:markExit(true)
		end
	end
end