--[[
	Description: battle dialog controller
	Author: M.Wan
	Date: 1/15/2015
]]

class("BattleDialogController", psViewController)

BattleDialogController.root = nil
BattleDialogController.dialogWindow = nil

function BattleDialogController:load()
	log("BattleDialogController:load")
	self:addObservers()
	self:renderView()
end

function BattleDialogController:unload()
	log("BattleDialogController:unload")
	self:removeObservers()
end

function BattleDialogController:addObservers()

end

function BattleDialogController:removeObservers()

end

function BattleDialogController:renderView()
	local winSize = cc.Director:getInstance():getWinSize()

	self.root = cc.Layer:create()
	self:getScene():addChild(self.root)

	-- dialog window initialization
	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	local windowSize = CCSizeMake(winSize.width * 0.95, winSize.height * 0.2)
	local windowPos = ccp(winSize.width * 0.5, winSize.height * 0.1)
	dialogWindow:setPreferredSize(windowSize)
	dialogWindow:setPosition(windowPos)

	self.dialogWindow = dialogWindow
	self.root:addChild(dialogWindow)
end