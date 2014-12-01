--[[
	Description: CollectionViewController
	Author: M.Wan
	Date: 11/30/2014
]]

class("CollectionViewController", psViewController)

require "src/scene/collection/CollectionView"

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
end

function CollectionViewController:removeObservers()
	log("CollectionViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.Collection.MainViewKeyResponsed, self)
	Notifier:removeObserver(NotifyEvents.Collection.CollectionSelectionChanged, self)
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