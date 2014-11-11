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
	local mainView = PokemonMainView:create()
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
	end
end
function PokemonViewController:onQuit()
	self:getScene():unloadViewController(self)
end