--[[
	Description: Game load game dialog
	Author: M.Wan
	Date: 11/23/2014
]]

class("LoadGameLayerController", psViewController)

LoadGameLayerController.dialog = nil

function LoadGameLayerController:load()
	log("LoadGameLayerController:load")
	self:addObservers()

	self:renderView()
end

function LoadGameLayerController:unload()
	self:removeObservers()

	if self.dialog then
		self.dialog:removeFromParent()
	end
end

function LoadGameLayerController:addObservers()

end

function LoadGameLayerController:removeObservers()

end

function LoadGameLayerController:renderView()
	self.dialog = ModalLayer:create()
	self:getScene():addChild(self.dialog)

	local winSize = cc.Director:getInstance():getWinSize()

	local dialogBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", CCRectMake(20, 20, 60, 60))
	dialogBorder:setPreferredSize(CCSizeMake(500, 450))
	dialogBorder:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.dialog:addChild(dialogBorder)
end