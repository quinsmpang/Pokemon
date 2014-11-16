--[[
	Description: Map name board
	Author: M.Wan
	Date: 07/19/2014
]]

class("MapNameBoard", psSprite)

MapNameBoard.mapName = nil

MapNameBoard.FONT_SIZE = 20

function MapNameBoard:create(mapName)
	local board = MapNameBoard:createWithSpriteFrameName("images/map/map_name_back.png")
	board:init(mapName)
	return board
end

function MapNameBoard:init(mapName)
	self.mapName = mapName

	local label = cc.Label:createWithTTF(mapName, GameConfig.DEFAULT_FONT_PATH, self.FONT_SIZE)
	label:setColor(COLOR3B_BLACK)
	label:setPosition(self:getContentSize().width * 0.5, self:getContentSize().height * 0.5)
	self:addChild(label)

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function MapNameBoard:onNodeEvent(event)
	if event == "enter" then
		local action = cc.Sequence:create(
			cc.DelayTime:create(0.15),
			cc.MoveBy:create(0.25, ccp(0, -self:getContentSize().height)),
			cc.DelayTime:create(2),
			cc.MoveBy:create(0.25, ccp(0, self:getContentSize().width)),
			cc.RemoveSelf:create()
			)
		self:runAction(action)
	end
end