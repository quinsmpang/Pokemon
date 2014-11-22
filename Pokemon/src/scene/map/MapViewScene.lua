--[[
	Description: map scene
	Author: M.Wan
	Date: 05/18/2014
]]

require "src/scene/map/MapLayerController"
require "src/scene/map/DialogLayerController"
require "src/scene/map/ActionController"
require "src/scene/map/ResponseController"
require "src/scene/map/EventController"
require "src/scene/map/MapStateController"
require "src/scene/pokemon/PokemonViewController"

class("MapViewScene", psGameScene)

MapViewScene.resources = {
	"images/map.plist",
	"images/map.pvr.ccz",
}

function MapViewScene:onEnter()
	log("MapViewScene:onEnter")
end

function MapViewScene:onEnterTransitionDidFinish()
	log("MapViewScene:onEnterTransitionDidFinish")
	self:loadResources()
	self:init()
end

function MapViewScene:onExit()
	log("MapViewScene:onExit")
	-- self:cleanResources()
end

function MapViewScene:loadResources()
	LoadSpriteFrames(self.resources)
end

function MapViewScene:cleanResources()
	RemoveSpriteFrames(self.resources)
end

function MapViewScene:init()
	if not self:getCoreLayer() then
		local coreLayer = CoreLayer:create()
		self:setCoreLayer(coreLayer)
		
		local mapLayerController = MapLayerController:create()
		self:loadViewController(mapLayerController)
		local dialogLayerController = DialogLayerController:create()
		self:loadViewController(dialogLayerController)
	end
end

function MapViewScene:newData(gender)
	local newPlayer = PlayerData:create(gender)
	DataCenter.currentPlayerData = newPlayer
end

function MapViewScene:loadData(data)
	-- player data
	local loadData = assert(loadstring(data[1]))()
	local playerData = PlayerData:createWithLoadData(loadData)
	DataCenter.currentPlayerData = playerData

	if data[2] then
		-- pokemons data
		local pokemons = string.split(data[2], "|")
		for _, pokemonData in ipairs(pokemons) do
			loadData = assert(loadstring(pokemonData))()
			local pokemon = Pokemon:createWithLoadData(loadData)
			DataCenter:addNewPokemon(pokemon)
		end
	end
end