--[[
	Description: CollectionViewController
	Author: M.Wan
	Date: 11/30/2014
]]

class("CollectionViewController", psViewController)

require "src/scene/collection/CollectionView"
require "src/scene/collection/CollectionDetailView"

CollectionViewController.mainView = nil
CollectionViewController.detailView = nil

CollectionViewController.resources = {
	"images/collection.plist",
	"images/collection.pvr.ccz",
}

function CollectionViewController:load()
	log("CollectionViewController:load")
	self:loadResources()
	self:addObservers()

	self:renderView()
end

function CollectionViewController:unload()
	log("CollectionViewController:unload")
	self:removeObservers()
	self:cleanResources()

	if self.mainView then
		self.mainView:removeFromParent()
	end
end

function CollectionViewController:loadResources()
	log("CollectionViewController:loadResources")
	LoadSpriteFrames(self.resources)
end

function CollectionViewController:cleanResources()
	log("CollectionViewController:cleanResources")
	RemoveSpriteFrames(self.resources)
end

function CollectionViewController:addObservers()
	log("CollectionViewController:addObservers")
	Notifier:addObserver(NotifyEvents.Collection.MainViewKeyResponsed, self, self.onMainViewKeyResponsed)
	Notifier:addObserver(NotifyEvents.Collection.CollectionSelectionChanged, self, self.onCollectionSelectionChanged)
	Notifier:addObserver(NotifyEvents.Collection.CollectionSelected, self, self.onCollectionSelected)
	Notifier:addObserver(NotifyEvents.Collection.DetailViewKeyResponsed, self, self.onDetailViewKeyResponsed)
end

function CollectionViewController:removeObservers()
	log("CollectionViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.Collection.MainViewKeyResponsed, self)
	Notifier:removeObserver(NotifyEvents.Collection.CollectionSelectionChanged, self)
	Notifier:removeObserver(NotifyEvents.Collection.CollectionSelected, self)
	Notifier:removeObserver(NotifyEvents.Collection.DetailViewKeyResponsed, self)
end

function CollectionViewController:renderView()
	log("CollectionViewController:renderView")
	local mainView = CollectionView:create()
	self:getScene():addChild(mainView)
	self.mainView = mainView
end

function CollectionViewController:onMainViewKeyResponsed(keyCode)
	if keyCode == GameSettings.cancelKey then
		local quitAction = cc.Sequence:create(
			cc.FadeIn:create(0.15),
			cc.CallFunc:create(MakeScriptHandler(self, self.onQuit))
			)
		self.mainView.mask:runAction(quitAction)
	end
end
function CollectionViewController:onQuit()
	self:getScene():unloadViewController(self)
end

function CollectionViewController:onCollectionSelectionChanged(oldIndex, newIndex)
	self.mainView:select(newIndex + 1)
end

function CollectionViewController:onCollectionSelected(pokemonId)
	-- show detail view
	local detailView = CollectionDetailView:create(pokemonId)
	self:getScene():addChild(detailView)
	self.detailView = detailView
end

function CollectionViewController:onDetailViewKeyResponsed(keyCode)
	if keyCode == GameSettings.cancelKey then
		local quitAction = cc.Sequence:create(
			cc.FadeIn:create(0.15),
			cc.CallFunc:create(function() self.detailView:removeFromParent() end)
			)
		self.detailView.mask:runAction(quitAction)
	elseif keyCode == GameSettings.leftKey then
		self.detailView:select((self.detailView.selectedIndex - 1 + 2) % 3 + 1)
	elseif keyCode == GameSettings.rightKey then
		self.detailView:select(self.detailView.selectedIndex % 3 + 1)
	end
end