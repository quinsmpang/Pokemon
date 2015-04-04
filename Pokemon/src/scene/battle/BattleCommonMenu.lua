--[[
	Description: battle common menu with 4 options
	Author: M.Wan
	Date: 4/2/2015
]]

class("BattleCommonMenu", psNode)

BattleCommonMenu.bg = nil
BattleCommonMenu.btns = nil
BattleCommonMenu.cursor = nil

BattleCommonMenu.contentList = nil
BattleCommonMenu.selectedIndex = nil
BattleCommonMenu.selectedIndexChangedScript = nil

BattleCommonMenu.LABEL_SIZE = 18
BattleCommonMenu.LABEL_COLOR = ccc3(0, 0, 0)

BattleCommonMenu.__create = psNode.create

local winSize = cc.Director:getInstance():getWinSize()

function BattleCommonMenu:create(contentList)
	local ret = BattleCommonMenu:__create()
	ret:init(contentList)
	return ret
end

function BattleCommonMenu:init(contentList)
	self.contentList = contentList

	local capInsets = CCRectMake(20, 20, 60, 60)
	local bg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", capInsets)
	bg:setPreferredSize(CCSizeMake(winSize.width * 0.32, winSize.height * 0.21))
	bg:setPosition(bg:getContentSize().width * 0.5, bg:getContentSize().height * 0.5)
	self:addChild(bg)
	self:setContentSize(bg:getContentSize())
	self:setAnchorPoint(0.5, 0.5)

	self.btns = {}
	for i = 1, 4 do
		local lbl = self:_createLabel(contentList[i])
		lbl:setPosition(bg:getContentSize().width * (0.25 + 0.45 * ((i - 1) % 2)), bg:getContentSize().height * (0.7 - 0.4 * math.floor((i - 1) / 2)))
		bg:addChild(lbl)
		self.btns[i] = lbl
	end

	self.cursor = cc.Sprite:createWithSpriteFrameName("images/common/menu_cursor.png")
	bg:addChild(self.cursor)

	self:select(1)
end

function BattleCommonMenu:select(index)
	if self.selectedIndex == index then
		return
	end
	local oldIndex = self.selectedIndex
	self.selectedIndex = index
	self.cursor:setPosition(self.btns[index]:getPositionX() - 20, self.btns[index]:getPositionY())
	if self.selectedIndexChangedScript then
		self.selectedIndexChangedScript(oldIndex, index)
	end
end

function BattleCommonMenu:setIndexChangedScript(script)
	assert(type(script) == "nil" or type(script) == "function", "Invalid script.")
	self.selectedIndexChangedScript = script
end

function BattleCommonMenu:cursorUp()
	local newIndex = self.selectedIndex - 2
	if newIndex >= 1 then
		self:select(newIndex)
	end
end

function BattleCommonMenu:cursorDown()
	local newIndex = self.selectedIndex + 2
	if newIndex <= #self.contentList then
		self:select(newIndex)
	end
end

function BattleCommonMenu:cursorLeft()
	local newIndex = self.selectedIndex - 1
	if newIndex >= 1 then
		self:select(newIndex)
	end
end

function BattleCommonMenu:cursorRight()
	local newIndex = self.selectedIndex + 1
	if newIndex <= #self.contentList then
		self:select(newIndex)
	end
end

function BattleCommonMenu:_createLabel(text)
	local lbl = cc.Label:createWithTTF(text or "--", GameConfig.DEFAULT_FONT_PATH, self.LABEL_SIZE)
	lbl:setAnchorPoint(ccp(0, 0.5))
	lbl:setColor(self.LABEL_COLOR)
	return lbl
end