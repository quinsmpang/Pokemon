--[[
	Description: pokemon ui controller
	Author: M.Wan
	Date: 08/31/2014
]]

class("PokemonViewController", psViewController)

require "src/view/pokemon/PokemonMainView"

PokemonViewController.mainView = nil

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
	local coreLayer = self:getScene():getCoreLayer()
	coreLayer:popLayer()
	self:cleanResources()
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
	Notifier:addObserver(NotifyEvents.PokemonView.BtnClick, self, self.onMainViewBtnClick)
end

function PokemonViewController:removeObservers()
	log("PokemonViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.PokemonView.BtnClick, self)
end

function PokemonViewController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local mainView = PokemonMainView:create()
	coreLayer:pushLayer(mainView)
	self.mainView = mainView
end

function PokemonViewController:onMainViewBtnClick(tag, sender)
	if tag == PokemonMainView.TAG.BTN_EXIT then
		self:getScene():unloadViewController(self)
		MapStateController:setCurrentState(Enumerations.MAP_STATE.MENU)
	end
end