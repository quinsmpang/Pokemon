--[[
	Description: pokemon ui controller
	Author: M.Wan
	Date: 08/31/2014
]]

class("PokemonViewController", psViewController)

PokemonViewController.resources = {
	"images/pokemon.plist",
	"images/pokemon.pvr.ccz",
	"images/pokemons1.plist",
	"images/pokemons1.pvr.ccz",
	"images/pokemons2.plist",
	"images/pokemons2.pvr.ccz",
	"images/pokemons3.plist",
	"images/pokemons3.pvr.ccz",
	"images/pokemons4.plist",
	"images/pokemons4.pvr.ccz",
	"images/pokemons5.plist",
	"images/pokemons5.pvr.ccz",
	"images/pokemons6.plist",
	"images/pokemons6.pvr.ccz",
	"images/pokemons7.plist",
	"images/pokemons7.pvr.ccz",
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
	self.root:getEventDispatcher():removeEventListener(self.touchEventListener)
	self.root:removeFromParent()
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
	Notifier:addObserver(NotifyEvents.MapView.ActionEnded, self, self.onActionEnded)
	Notifier:addObserver(NotifyEvents.MapView.DialogKeyboardResponse, self, self.onKeyboardEvent)
	Notifier:addObserver(NotifyEvents.MapView.ResponseBegan, self, self.onResponseBegan)
end

function PokemonViewController:removeObservers()
	log("PokemonViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionEnded, self)
	Notifier:removeObserver(NotifyEvents.MapView.DialogKeyboardResponse, self)
	Notifier:removeObserver(NotifyEvents.MapView.ResponseBegan, self)
end

function PokemonViewController:renderView()
end