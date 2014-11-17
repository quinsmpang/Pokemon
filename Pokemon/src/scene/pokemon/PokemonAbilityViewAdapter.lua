--[[
	Description: Pokemon ability view adapter
	Author: M.Wan
	Date: 11/18/2014
]]

luaClass("PokemonAbilityViewAdapter")

PokemonAbilityViewAdapter.layer = nil

function PokemonAbilityViewAdapter:adapt(detailView)
	assert(detailView and detailView.__className == "PokemonDetailView", "invalid argument")
	if detailView.adapter then
		detailView.adapter:remove()
		detailView.adapter = nil
	end
	detailView.adapter = self
end

function PokemonAbilityViewAdapter:remove()
	if self.layer then
		self.layer:removeFromParent()
	end
end