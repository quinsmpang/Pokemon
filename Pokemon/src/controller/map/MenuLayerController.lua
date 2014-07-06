--[[
	Description: menu layer controller
	Author: M.Wan
	Date: 07/04/2014
]]

class("MenuLayerController", psViewController)

MenuLayerController.root = nil
MenuLayerController.menu = nil		-- 菜单

MenuLayerController.resources = {
}

function MenuLayerController:load()
	log("MenuLayerController:load")
	self:loadResources()
	self:addObservers()
	self:renderView()
end

function MenuLayerController:unload()
	log("MenuLayerController:unload")
	self:cleanResources()
	self:removeObservers()
end

function MenuLayerController:loadResources()
	log("MenuLayerController:loadResources")
	LoadSpriteFrames(self.resources)
end

function MenuLayerController:cleanResources()
	RemoveSpriteFrames(self.resources)
end

function MenuLayerController:addObservers()
	log("MenuLayerController:addObservers")
end

function MenuLayerController:removeObservers()
	log("MenuLayerController:removeObservers")
end

function MenuLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	self.root = cc.Layer:create()

	-- pokemon ball
	local ballItem = cc.MenuItemSprite:create(
		cc.Sprite:createWithSpriteFrameName("images/map/pokemon_ball_normal.png"),
		cc.Sprite:createWithSpriteFrameName("images/map/pokemon_ball_selected.png")
		)
	if not TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		ballItem:registerScriptTapHandler(MakeScriptHandler(self, self.onBallClick))
	end
	ballItem:setPosition(screenSize.width * 0.9, screenSize.height * 0.9)
	local menu = cc.Menu:create(ballItem)
	menu:setPosition(0, 0)
	self.root:addChild(menu)

	self:getScene():addChild(self.root)
end

function MenuLayerController:onBallClick()
	
end

function MenuLayerController:showMenu()
	
end