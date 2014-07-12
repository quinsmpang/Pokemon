--[[
	Description: Menu layer on the map
	Author: M.Wan
	Date: 07/06/2014
]]

class("MapMenuLayer", psModalLayer)

require "src/view/map/MapMenu"

MapMenuLayer.back = nil 			-- 背景

MapMenuLayer.keyboardListener = nil
MapMenuLayer.enableClick = nil

MapMenuLayer.__create = psModalLayer.create

function MapMenuLayer:create()
	local mapMenu = MapMenuLayer:__create()
	mapMenu:init()
	return mapMenu
end

function MapMenuLayer:init()
	local screenSize = cc.Director:getInstance():getWinSize()

	self.enableClick = false
	self:setOpacity(0.3 * 255)

	-- we need a ball to mask the ball on the map layer.
	local ballItem = cc.MenuItemSprite:create(
		cc.Sprite:createWithSpriteFrameName("images/map/pokemon_ball_normal.png"),
		cc.Sprite:createWithSpriteFrameName("images/map/pokemon_ball_selected.png")
		)
	ballItem:registerScriptTapHandler(MakeScriptHandler(self, self.onBallClick))
	-- ballItem:setAnchorPoint(ccp(1, 1))
	ballItem:setPosition(screenSize.width - screenSize.height * 0.1 , screenSize.height * 0.9)

	local menu = cc.Menu:create(ballItem)
	menu:setPosition(0, 0)
	self:addChild(menu)

	-- menu background
	self.back = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", CCRectMake(20, 20, 60, 60))
	self.back:setPreferredSize(CCSizeMake(screenSize.width * 0.18, screenSize.height * 0.75))
	self.back:setAnchorPoint(1, 1)
	self.back:setPosition(screenSize.width - screenSize.height * 0.05 , screenSize.height * 0.85)
	self:addChild(self.back)

	local listMenu = MapMenu:create()
	listMenu:reloadData()
	listMenu:ignoreAnchorPointForPosition(false)
	listMenu:setAnchorPoint(0.5, 1)
	listMenu:setPosition(self.back:getContentSize().width * 0.5, self.back:getContentSize().height * 0.95)

	self.back:addChild(listMenu)

	self.back:setScaleY(0)

	-- 注册事件
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		local kbdListener = cc.EventListenerKeyboard:create()
		kbdListener:registerScriptHandler(MakeScriptHandler(self, self.onKeyboardPressed), cc.Handler.EVENT_KEYBOARD_PRESSED)
		self.keyboardListener = kbdListener
		self:getEventDispatcher():addEventListenerWithSceneGraphPriority(kbdListener, self)

		self:registerScriptHandler(MakeScriptHandler(self, self.onSceneEvent))
	end
end

function MapMenuLayer:onComeIn()
	local enterAction = cc.Sequence:create(
		cc.ScaleTo:create(0.1, 1),
		cc.CallFunc:create(MakeScriptHandler(self, self.onComeInEnd))
		)
	self.back:runAction(enterAction)
end
function MapMenuLayer:onComeInEnd()
	self.enableClick = true
end

function MapMenuLayer:onSceneEvent(event)
	if event == "exit" then
		-- 移除监听
		self:getEventDispatcher():removeEventListener(self.keyboardListener)
	end
end

function MapMenuLayer:onBallClick()
	if not self.enableClick then
		return
	end
	self:exitMenu()
end

function MapMenuLayer:onKeyboardPressed(keyCode)
	if keyCode == GameSettings.startKey and self.enableClick then
		self:exitMenu()
	end
end

function MapMenuLayer:exitMenu()
	self.enableClick = false
	local quitAction = cc.Sequence:create(
		cc.TargetedAction:create(self.back, cc.ScaleTo:create(0.1, 1, 0)),
		cc.RemoveSelf:create(),
		cc.CallFunc:create(MakeScriptHandler(self, self.onChangeState))
		)
	self:runAction(quitAction)
end

function MapMenuLayer:onChangeState()
	MapStateController:setCurrentState(Enumerations.MAP_STATE.FREEDOM)
end