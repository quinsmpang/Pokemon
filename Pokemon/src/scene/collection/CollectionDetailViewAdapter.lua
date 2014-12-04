--[[
	Description: Collection detail view adapter
	Author: M.Wan
	Date: 12/5/2014
]]

luaClass("CollectionDetailViewAdapter")

CollectionDetailViewAdapter.layer = nil

function CollectionDetailViewAdapter:adapt(detailView)
	assert(detailView and detailView.__className == "CollectionDetailView", "invalid argument")
	if detailView.adapter then
		detailView.adapter:remove()
		detailView.adapter = nil
	end
	detailView.adapter = self

	local winSize = cc.Director:getInstance():getWinSize()
	local pokemon = detailView.pokemonModel

	local layer = cc.Layer:create()
	detailView:addChild(layer)
	self.layer = layer
end

function CollectionDetailViewAdapter:remove()
	if self.layer then
		self.layer:removeFromParent()
	end
end