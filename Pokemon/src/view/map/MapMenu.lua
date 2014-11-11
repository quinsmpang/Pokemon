--[[
	Description: Map menu
	Author: M.Wan
	Date: 07/06/2014
]]

class("MapMenu", psListMenu)

-- const
MapMenu.ICON_PATHS = {
	"images/map/icon_collection.png",
	"images/map/icon_pokemon.png",
	"images/map/icon_bag.png",
	"images/map/icon_contact.png",
	"images/map/icon_info.png",
	"images/map/icon_record.png",
	"images/map/icon_setting.png",
	"images/map/icon_back.png",
}
MapMenu.ITEM_STRINGS = {
	"图鉴",
	"精灵",
	"背包",
	"通讯器",
	"玩家",
	"记录",
	"设置",
	"退出",
}
MapMenu.SKIP_COLLECTION_STEP = 10
MapMenu.SKIP_PETS_STEP = 2
MapMenu.SKIP_CONTACT_STEP = 11

MapMenu.LABEL_TAG = 998
MapMenu.ARROW_TAG = 999

MapMenu.__create = psListMenu.create

function MapMenu:create()
	local menu = MapMenu:__create(#self.ITEM_STRINGS)
	menu:init()
	return menu
end

function MapMenu:init()
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
function MapMenu:itemSizeForMenu(menu)
	log("MapMenu:itemSizeForMenu")
	local screenSize = cc.Director:getInstance():getWinSize()
	return screenSize.width * 0.15, screenSize.height * 0.08
end

function MapMenu:itemAtIndex(menu, index)
	log("MapMenu:itemAtIndex", index)
	local item = menu:dequeueItem()
	if not item then
		item = ListMenuItem:create()

		local screenSize = cc.Director:getInstance():getWinSize()
		-- label
		local label = cc.Label:createWithTTF(self.ITEM_STRINGS[index + 1], GameConfig.DEFAULT_FONT_PATH, 20)
		label:setDimensions(screenSize.width * 0.1, screenSize.height * 0.08)
		label:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
		label:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
		label:setColor(ccc3(0, 0, 0))
		label:setAnchorPoint(0, 0.5)
		label:setPosition(screenSize.width * 0.065, screenSize.height * 0.04)
		label:setTag(self.LABEL_TAG)
		item:addChild(label)
		-- icon
		local icon = cc.Sprite:createWithSpriteFrameName(self.ICON_PATHS[index + 1])
		icon:setAnchorPoint(1, 0.5)
		icon:setPosition(screenSize.width * 0.06, screenSize.height * 0.04)
		item:addChild(icon)
		-- arrow
		local arrow = cc.Sprite:createWithSpriteFrameName("images/map/menu_cursor.png")
		arrow:setAnchorPoint(1, 0.5)
		arrow:setPosition(screenSize.width * 0.035, screenSize.height * 0.04)
		arrow:setTag(self.ARROW_TAG)
		arrow:setVisible(false)
		item:addChild(arrow)
	else
		local label = item:getChildByTag(self.LABEL_TAG)
		tolua.cast(label, "cc.Label")
		label:setString(self.ITEM_STRINGS[index + 1])
	end

	self:validateItem(item, index)

	return item
end

function MapMenu:countOfItemInMenu(menu)
	log("MapMenu:countOfItemInMenu", #self.ITEM_STRINGS)
	return #self.ITEM_STRINGS
end

-- ListMenu delegate
function MapMenu:itemSelected(menu, item)
	-- local itemIndex = item:getShowIndex()
	Notifier:notify(NotifyEvents.MapView.MenuItemSelected, item)
end

function MapMenu:itemFocused(menu, item)
	local cursor = item:getChildByTag(self.ARROW_TAG)
	cursor:setVisible(true)
end

function MapMenu:itemBlurred(menu, item)
	local cursor = item:getChildByTag(self.ARROW_TAG)
	cursor:setVisible(false)
end

function MapMenu:itemWillRecycle(menu, item)
	--item:removeAllChildrenWithCleanup(true)
end

function MapMenu:validateItem(item, index)
	item.__isEnabled = true
	if DataCenter.currentPlayerData.lastStep < self.SKIP_PETS_STEP then
		if index == 0 or index == 1 or index == 3 then
			item.__isEnabled = false
		end
	elseif DataCenter.currentPlayerData.lastStep < self.SKIP_COLLECTION_STEP then
		if index == 0 or index == 3 then
			item.__isEnabled = false
		end
	elseif DataSource.currentPlayerData.lastStep < self.SKIP_CONTACT_STEP then
		if index == 3 then
			item.__isEnabled = false
		end
	end

	local label = item:getChildByTag(self.LABEL_TAG)
	tolua.cast(label, "cc.Label")
	if not item.__isEnabled then
		label:setColor(ccc3(200, 200, 200))
	else
		label:setColor(ccc3(0, 0, 0))
	end
end

function MapMenu:validateAllItems()
	for i = 0, #self.ITEM_STRINGS - 1 do
		local item = self:getItemAtIndex(i)
		self:validateItem(item, i)
	end
end