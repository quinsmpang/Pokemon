--[[
	Description: menu layer controller
	Author: M.Wan
	Date: 07/04/2014
]]

class("MenuLayerController", psViewController)

require "src/view/map/MapMenuLayer"

MenuLayerController.root = nil
MenuLayerController.mapMenu = nil		-- 菜单

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
	self.root:removeFromParent()
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
	Notifier:addObserver(NotifyEvents.MapView.MapKeyboardResponse, self, self.onKeyboardEvent)
end

function MenuLayerController:removeObservers()
	log("MenuLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.MapKeyboardResponse, self)
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
	ballItem:registerScriptTapHandler(MakeScriptHandler(self, self.onBallClick))
	ballItem:setAnchorPoint(ccp(1, 1))
	ballItem:setPosition(screenSize.width - screenSize.height * 0.05 , screenSize.height * 0.95)
	ballItem:setOpacity(0)

	local menu = cc.Menu:create(ballItem)
	menu:setPosition(0, 0)
	self.root:addChild(menu)

	self:getScene():addChild(self.root)

	local enterAction = cc.Spawn:create(
		cc.FadeIn:create(0.5),
		cc.RotateBy:create(0.5, 360)
		)
	ballItem:runAction(enterAction)
end

function MenuLayerController:onBallClick()
	log("MenuLayerController:onBallClick")
	self:showMenu()
end

function MenuLayerController:onKeyboardEvent(keyCode, eventType, pressedKeys)
	log("MenuLayerController:onKeyboardEvent, eventType: [" .. eventType .. "]")
	if eventType == Enumerations.KEYBOARD_STATE.PRESSED then
		if keyCode == GameSettings.startKey then
			self:showMenu()
		end
	end
end

function MenuLayerController:showMenu()
	MapStateController:setCurrentState(Enumerations.MAP_STATE.MENU)
	local mapMenu = MapMenuLayer:create()
	self.root:addChild(mapMenu)
end