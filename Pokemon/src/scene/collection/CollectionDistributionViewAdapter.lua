--[[
	Description: Collection destribution view adapter
	Author: M.Wan
	Date: 12/9/2014
]]

luaClass("CollectionDistributionViewAdapter")

CollectionDistributionViewAdapter.pokemonModel = nil

function CollectionDistributionViewAdapter:adapt(detailView)
	assert(detailView and detailView.__className == "CollectionDetailView", "invalid argument")
	if detailView.adapter then
		detailView.detailBg:removeAllChildren()
	end
	detailView.adapter = self
end