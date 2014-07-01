--[[
	Description: CollectionViewController
	Author: Frank.Z
	Date: 06/29/2014
]]

class("CollectionViewController", psViewController)

function CollectionViewController:load()
	log("CollectionViewController:load")
	self:renderView()
end

function CollectionViewController:renderView()
	log("CollectionViewController:renderView")
	local coreLayer = self:getScene():getCoreLayer()

	--local screenSize = cc.Director:getInstance():getWinSize()

	local ccbCollectionView = ScriptCCBReader:readCCB("ccb/CollectionView.ccbi", self)
	coreLayer:addChild(ccbCollectionView)
end