--[[
	Description: Dynamic menu list control, common
	Author: M.Wan
	Date: 11/12/2014
]]

class("CommonListMenu", psListMenu)

CommonListMenu.stringList = nil

CommonListMenu.__create = psListMenu.create

-- param list is a table with shown strings.
function CommonListMenu:create(list)
	local menu = CommonListMenu:__create()
	menu:init(list)
	return menu
end

function CommonListMenu:init(list)
	self.stringList = list

	self:registerScriptHandler(MakeScriptHandler(self, self.countOfItemInMenu), pf.Handler.LISTMENU_COUNT_OF_ITEMS)
	self:registerScriptHandler(MakeScriptHandler(self, self.itemAtIndex), pf.Handler.LISTMENU_ITEM_AT_INDEX)
	self:registerScriptHandler(MakeScriptHandler(self, self.itemSizeForMenu), pf.Handler.LISTMENU_ITEM_SIZE_FOR_MENU)
	self:setScriptDataSource()

	self:registerScriptHandler(MakeScriptHandler(self, self.itemSelected), pf.Handler.LISTMENU_ITEM_SELECTED)
	self:registerScriptHandler(MakeScriptHandler(self, self.itemFocused), pf.Handler.LISTMENU_ITEM_FOCUSED)
	self:registerScriptHandler(MakeScriptHandler(self, self.itemBlurred), pf.Handler.LISTMENU_ITEM_BLURRED)
	self:registerScriptHandler(MakeScriptHandler(self, self.itemWillRecycle), pf.Handler.LISTMENU_ITEM_WILL_RECYCLE)
	self:setScriptDelegate()

	self:setResponseKeyCodes(GameSettings.upKey, GameSettings.downKey, GameSettings.confirmKey)
end

-- DataSource interface
function CommonListMenu:itemSizeForMenu(menu)
end

function CommonListMenu:itemAtIndex(menu, index)
end

function CommonListMenu:countOfItemInMenu(menu)
end

-- ListMenu delegate
function CommonListMenu:itemSelected(menu, item)
end

function CommonListMenu:itemFocused(menu, item)
end

function CommonListMenu:itemBlurred(menu, item)
end

function CommonListMenu:itemWillRecycle(menu, item)
end