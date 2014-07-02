--[[
	Description: collection scene
	Author: Frank.Z
	Date: 06/29/2014
]]

require "src/controller/collection/CollectionViewController"

class("CollectionScene", psGameScene)

function CollectionScene:onEnter()
	log("CollectionScene:onEnter")
	local coreLayer = CoreLayer:create()
	self:setCoreLayer(coreLayer)
	
	local collectionViewController = CollectionViewController:create()
	self:loadViewController(collectionViewController)
end

function CollectionScene:onExit()
	log("CollectionScene:onExit")
end