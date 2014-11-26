--[[
	Description: bag ui controller
	Author: M.Wan
	Date: 11/26/2014
]]

class("BagViewController", psViewController)

require "src/scene/bag/BagMainView"

BagViewController.mainView = nil

BagViewController.inSwapState = nil		-- 是否处于交换道具位置的状态

BagViewController.resources = {
	"images/item.plist",
	"images/item.pvr.ccz",
}

function BagViewController:load()
	log("BagViewController:load")
	self:loadResources()
	self:addObservers()

	self:renderView()
end

function BagViewController:unload()
	log("BagViewController:unload")
	self:removeObservers()
	self:cleanResources()

	if self.mainView then
		self.mainView:removeFromParent()
	end
end

function BagViewController:loadResources()
	log("BagViewController:loadResources")
	LoadSpriteFrames(self.resources)
end

function BagViewController:cleanResources()
	log("BagViewController:cleanResources")
	RemoveSpriteFrames(self.resources)
end

function BagViewController:addObservers()
	log("BagViewController:addObservers")
	Notifier:addObserver(NotifyEvents.Bag.TitleChanged, self, self.onTitleChanged)
end

function BagViewController:removeObservers()
	log("BagViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.Bag.TitleChanged, self)
end

function BagViewController:renderView()
	log("BagViewController:renderView")

	local enterType = self:getScene():getIntAttribute(GameConfig.BAG_KEY)
	enterType = enterType or Enumerations.BAG_VIEW_SCENE_TYPE.VIEW_ITEMS
	log("bag view enter type: " .. enterType)

	local bagMainView = BagMainView:create(enterType)
	self:getScene():addChild(bagMainView)
	self.mainView = bagMainView
	
	self.inSwapState = false
end

function BagViewController:onTitleChanged(oldIndex, newIndex)
	log("BagViewController:onTitleChanged", oldIndex, newIndex)
end