--[[
	Description: menu layer controller
	Author: M.Wan
	Date: 07/04/2014
]]

class("MenuLayerController", psViewController)

require "src/view/map/MapMenuLayer"

MenuLayerController.root = nil
MenuLayerController.mapMenu = nil		-- 菜单

MenuLayerController.isMenuOpen = nil

MenuLayerController.topViewController = nil		-- record the view controller(Pokemon, Collection, etc..)

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
	Notifier:addObserver(NotifyEvents.MapView.MenuItemSelected, self, self.onMenuItemSelected)
end

function MenuLayerController:removeObservers()
	log("MenuLayerController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.MapKeyboardResponse, self)
	Notifier:removeObserver(NotifyEvents.MapView.MenuItemSelected, self)
end

function MenuLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	self.isMenuOpen = false
	self.root = cc.Layer:create()

	-- pokemon ball
	local ballItem = cc.MenuItemSprite:create(
		cc.Sprite:createWithSpriteFrameName("images/map/pokemon_ball_normal.png"),
		cc.Sprite:createWithSpriteFrameName("images/map/pokemon_ball_selected.png")
		)
	ballItem:registerScriptTapHandler(MakeScriptHandler(self, self.onBallClick))
	-- ballItem:setAnchorPoint(ccp(1, 1))
	ballItem:setPosition(screenSize.width - screenSize.height * 0.1 , screenSize.height * 0.9)
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
			if MapStateController:getCurrentState() == Enumerations.MAP_STATE.FREEDOM then
				self:showMenu()
			end
		end
	end
end

function MenuLayerController:showMenu()
	MapStateController:setCurrentState(Enumerations.MAP_STATE.MENU)
	local mapMenu = MapMenuLayer:create()
	self.root:addChild(mapMenu)
	self.mapMenu = mapMenu
end

function MenuLayerController:onMenuItemSelected(item)
	if item.__isEnabled then
		local itemIndex = item:getShowIndex()
		if itemIndex == 0 then
			--图鉴
			if DEBUG then
				log("@@@@@@@@", DataCenter.currentPlayerData.lastStep)
			end
		elseif itemIndex == 1 then
			--精灵
			local pokemonViewController = PokemonViewController:create()
			self:getScene():loadViewController(pokemonViewController)
		elseif itemIndex == 2 then
			--背包
		elseif itemIndex == 3 then
			--通讯器
		elseif itemIndex == 4 then
			--玩家
		elseif itemIndex == 5 then
			--记录
		elseif itemIndex == 6 then
			--设置
		elseif itemIndex == 7 then
			--退出
			self.mapMenu:exitMenu()
		end
	else
		GameVolumeHelper:playUnableSound()
	end
end