--[[
	Description: bag ui controller
	Author: M.Wan
	Date: 11/26/2014
]]

class("BagViewController", psViewController)

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
end

function BagViewController:removeObservers()
	log("BagViewController:removeObservers")
end

function BagViewController:renderView()
	log("BagViewController:renderView")
	self.inSwapState = false

	local switch = TitleSwitch:create(cc.Sprite:createWithSpriteFrameName("images/common/common_scale9_1.png"), { "aaa", "bbb", "ccc" }, GameConfig.DEFAULT_FONT_PATH)
	switch:setPosition(200, 100)
	switch:setTitleFontSize(30)
	switch:setResponseKeys(GameSettings.leftKey, GameSettings.rightKey)
	self:getScene():addChild(switch)
end