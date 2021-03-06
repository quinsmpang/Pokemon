--[[
	Description: map direction rocker layer
	Author: M.Wan
	Date: 12/31/2014
]]

class("DirectionRockerLayer", psLayer)

-- ui
DirectionRockerLayer.rocker = nil

-- logic
DirectionRockerLayer.inRunningState = nil

DirectionRockerLayer.MOVE_EVENT = 1
DirectionRockerLayer.BTN_EVENT = 2

DirectionRockerLayer.__create = psLayer.create

function DirectionRockerLayer:create()
	local layer = DirectionRockerLayer:__create()
	layer:init()
	return layer
end

function DirectionRockerLayer:init()
	log("DirectionRockerLayer:init")

	self.inRunningState = false

	local winSize = cc.Director:getInstance():getWinSize()

	-- rocker
	local bgNode = cc.Sprite:createWithSpriteFrameName("images/common/controller_bg.png")
	local rockerNode = cc.Sprite:createWithSpriteFrameName("images/common/rocker.png")
	local rocker = DirectionController:create(bgNode, rockerNode)
	rocker:setPosition(100, 100)
	self:addChild(rocker)
	self.rocker = rocker

	-- register rocker events
	rocker:registerScriptHandler(MakeScriptHandler(self, self.onControlDirection, DirectionRockerLayer.MOVE_EVENT, Enumerations.DIRECTIONS.RIGHT), pf.Handler.DIRECTIONCONTROLLER_ON_RIGHT)
	rocker:registerScriptHandler(MakeScriptHandler(self, self.onControlDirection, DirectionRockerLayer.MOVE_EVENT, Enumerations.DIRECTIONS.LEFT), pf.Handler.DIRECTIONCONTROLLER_ON_LEFT)
	rocker:registerScriptHandler(MakeScriptHandler(self, self.onControlDirection, DirectionRockerLayer.MOVE_EVENT, Enumerations.DIRECTIONS.UP), pf.Handler.DIRECTIONCONTROLLER_ON_UP)
	rocker:registerScriptHandler(MakeScriptHandler(self, self.onControlDirection, DirectionRockerLayer.MOVE_EVENT, Enumerations.DIRECTIONS.DOWN), pf.Handler.DIRECTIONCONTROLLER_ON_DOWN)
	rocker:registerScriptHandler(MakeScriptHandler(self, self.onControlDirection, DirectionRockerLayer.MOVE_EVENT, -1), pf.Handler.DIRECTIONCONTROLLER_ON_STOP)
	rocker:setScriptDelegate()

	local menu = cc.Menu:create()
	menu:setPosition(0, 0)
	self:addChild(menu)
	-- menu button
	local normalSprite, selectedSprite
	normalSprite = cc.Sprite:createWithSpriteFrameName("images/map/btn_menu.png")
	selectedSprite = cc.Sprite:createWithSpriteFrameName("images/map/btn_menu.png")
	local btnMenu = cc.MenuItemSprite:create(normalSprite, selectedSprite)
	btnMenu:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnMenuClick))
	btnMenu:setPosition(winSize.width - 25, winSize.height - 25)
	menu:addChild(btnMenu)

	-- walking/running transfer button
	local checkedNode = cc.Sprite:createWithSpriteFrameName("images/map/btn_run.png")
	local uncheckedNode = cc.Sprite:createWithSpriteFrameName("images/map/btn_walk.png")
	local btnWalkRun = CheckedButton:create(checkedNode, uncheckedNode)
	btnWalkRun:setPosition(btnMenu:getPositionX() - 50, btnMenu:getPositionY())
	btnWalkRun:registerScriptHandler(MakeScriptHandler(self, self.onWalkStateChanged), pf.Handler.CHECKEDBUTTON_ON_CHECKED)
	btnWalkRun:registerScriptHandler(MakeScriptHandler(self, self.onWalkStateChanged), pf.Handler.CHECKEDBUTTON_ON_UNCHECKED)
	btnWalkRun:setScriptDelegate()
	self:addChild(btnWalkRun)
end

-- eventType为DirectionRockerLayer.MOVE_EVENT时, param为方向(松开则为-1)
-- eventType为DirectionRockerLayer.BTN_EVENT时, param为确认/取消 (bool)
function DirectionRockerLayer:onControlDirection(sender, eventType, param)
	Notifier:notify(NotifyEvents.MapView.RockerEvent, eventType, param)
end

function DirectionRockerLayer:onBtnMenuClick()
	Notifier:notify(NotifyEvents.MapView.MapMenuClicked)
end

function DirectionRockerLayer:onWalkStateChanged(sender)
	if sender:isChecked() then
		log("Change walk state to running.")
	else
		log("Change walk state to walking.")
	end
	self.inRunningState = sender:isChecked()
end