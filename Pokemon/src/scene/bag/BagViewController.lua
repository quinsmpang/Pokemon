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
	Notifier:addObserver(NotifyEvents.Bag.MainViewKeyResponsed, self, self.onMainViewKeyResponsed)
	Notifier:addObserver(NotifyEvents.Bag.ItemSelected, self, self.onItemSelected)
end

function BagViewController:removeObservers()
	log("BagViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.Bag.TitleChanged, self)
	Notifier:removeObserver(NotifyEvents.Bag.MainViewKeyResponsed, self)
	Notifier:removeObserver(NotifyEvents.Bag.ItemSelected, self)
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

function BagViewController:onTitleChanged(oldIndex, newIndex, subType)
	log("BagViewController:onTitleChanged", oldIndex, newIndex, subType)
	BagMainView.lastSubType = subType
	BagMainView.lastIndexs[subType] = newIndex
	self.mainView:reloadItems()
end

function BagViewController:onMainViewKeyResponsed(keyCode)
	log("BagViewController:onMainViewKeyResponsed", keyCode)
	if keyCode == GameSettings.cancelKey then
		if self.inSwapState then
			-- self:endExchange()
			-- self.mainView:cancelExchange()
		else
			local quitAction = cc.Sequence:create(
				cc.FadeIn:create(0.15),
				cc.CallFunc:create(MakeScriptHandler(self, self.onQuit))
				)
			self.mainView.mask:runAction(quitAction)
		end
	end
end
function BagViewController:onQuit()
	self:getScene():unloadViewController(self)
end

function BagViewController:onItemSelected(selectedIndex)
	log("BagViewController:onItemSelected", selectedIndex)
	-- local list = CommonListMenu:create({"使用"}, CCSizeMake(175, 200))
	-- list:setItemSelectedScript(MakeScriptHandler(self, self.onViewPokemonItemSelected))
	-- list:setAnchorPoint(1, 0)
	-- list:setPosition(cc.Director:getInstance():getWinSize().width, 0)
	-- self:getScene():addChild(list)
end