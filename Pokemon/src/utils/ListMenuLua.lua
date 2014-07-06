--[[
	Description: More encapsulated ListMenu in lua
	Author: M.Wan
	Date: 07/06/2014
]]

class("ListMenuLua", psListMenu)

ListMenuLua.__create = psListMenu.create

function ListMenuLua:create(rowCount)
	local menu = ListMenuLua:__create(rowCount)
	menu:init()
	return menu
end

function ListMenuLua:init()
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
function ListMenuLua:itemSizeForMenu(menu)
	return 0, 0
end

function ListMenuLua:itemAtIndex(menu, index)
	return menu:dequeueCell()
end

function ListMenuLua:countOfItemInMenu(menu)
	return 0
end

-- ListMenu delegate
function ListMenuLua:itemSelected(menu, item)
	
end

function ListMenuLua:itemFocused(menu, item)
	
end

function ListMenuLua:itemBlurred(menu, item)
	
end

function ListMenuLua:itemWillRecycle(menu, item)
	
end