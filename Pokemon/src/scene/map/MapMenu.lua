--[[
	Description: Map menu
	Author: M.Wan
	Date: 07/06/2014
]]

if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
class("MapMenu", psListMenu)
else
class("MapMenu", psTableView)
end

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
MapMenu.SKIP_COLLECTION_STEP = 4
MapMenu.SKIP_PETS_STEP = 2
MapMenu.SKIP_CONTACT_STEP = 11

MapMenu.LABEL_TAG = 998
MapMenu.ARROW_TAG = 999
MapMenu.ICON_TAG = 1000

if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
MapMenu.__create = psListMenu.create
else
MapMenu.__create = psTableView.create
end

local winSize = cc.Director:getInstance():getWinSize()

function MapMenu:create()
	local menu = nil
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		menu = MapMenu:__create(#self.ITEM_STRINGS)
	else
		menu = MapMenu:__create(CCSizeMake(winSize.width * 0.15, winSize.height * 0.64))
	end
	menu:init()
	return menu
end

function MapMenu:init()
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
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
	else
		self:registerScriptHandler(MakeScriptHandler(self, self.tableCellSizeForIndex), cc.Handler.TABLECELL_SIZE_FOR_INDEX)
		self:registerScriptHandler(MakeScriptHandler(self, self.tableCellAtIndex), cc.Handler.TABLECELL_AT_INDEX)
		self:registerScriptHandler(MakeScriptHandler(self, self.tableNumsOfCells), cc.Handler.TABLEVIEW_NUMS_OF_CELLS)
		-- self:setDataSource()		create的时候已经自动设置了数据源了

		self:registerScriptHandler(MakeScriptHandler(self, self.tableCellTouched), cc.Handler.TABLECELL_TOUCHED)
		self:registerScriptHandler(MakeScriptHandler(self, self.tableCellHighlight), cc.Handler.TABLECELL_HIGHLIGHT)
		self:registerScriptHandler(MakeScriptHandler(self, self.tableCellUnhighlight), cc.Handler.TABLECELL_UNHIGHLIGHT)
		self:registerScriptHandler(MakeScriptHandler(self, self.tableCellWillRecycle), cc.Handler.TABLECELL_WILL_RECYCLE)
		self:setDelegate()

		self:setVerticalFillOrder(cc.TABLEVIEW_FILL_TOPDOWN)
		self:setBounceable(false)
	end
	self:reloadData()
end

if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
------------------ Win32 Delegates ------------------

-- DataSource interface
function MapMenu:itemSizeForMenu(menu)
	local screenSize = cc.Director:getInstance():getWinSize()
	return screenSize.width * 0.15, screenSize.height * 0.08
end

function MapMenu:itemAtIndex(menu, index)
	local item = menu:dequeueItem()
	local label = nil
	if not item then
		item = ListMenuItem:create()

		local screenSize = cc.Director:getInstance():getWinSize()
		-- label
		label = cc.Label:createWithTTF(self.ITEM_STRINGS[index + 1], GameConfig.DEFAULT_FONT_PATH, 20)
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
		icon:setTag(self.ICON_TAG)
		item:addChild(icon)
		-- arrow
		local arrow = cc.Sprite:createWithSpriteFrameName("images/map/menu_cursor.png")
		arrow:setAnchorPoint(1, 0.5)
		arrow:setPosition(screenSize.width * 0.035, screenSize.height * 0.04)
		arrow:setTag(self.ARROW_TAG)
		arrow:setVisible(false)
		item:addChild(arrow)
	else
		label = item:getChildByTag(self.LABEL_TAG)
		tolua.cast(label, "cc.Label")
		label:setString(self.ITEM_STRINGS[index + 1])

		local icon = item:getChildByTag(self.ICON_TAG)
		tolua.cast(icon, "cc.Sprite")
		icon:setSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame(self.ICON_PATHS[index + 1]))

		item:getChildByTag(self.ARROW_TAG):setVisible(false)
	end

	local isEnabled = self:validateItem(index)
	if not isEnabled then
		label:setColor(ccc3(200, 200, 200))
	else
		label:setColor(ccc3(0, 0, 0))
	end
	item.__isEnabled = isEnabled

	return item
end

function MapMenu:countOfItemInMenu(menu)
	return #self.ITEM_STRINGS
end

-- ListMenu delegate
function MapMenu:itemSelected(menu, item)
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
	local cursor = item:getChildByTag(self.ARROW_TAG)
	cursor:setVisible(false)
end

else
------------------ Mobile platform Delegates ------------------

-- DataSource interface
function MapMenu:tableCellSizeForIndex(view, index)
	local screenSize = cc.Director:getInstance():getWinSize()
	-- 我真fuck了 为何这里的size是宽高反着传递的 md调试了半天 by M.Wan
	return screenSize.height * 0.08, screenSize.width * 0.15
end

function MapMenu:tableCellAtIndex(view, index)
	local item = view:dequeueCell()
	local label = nil
	if not item then
		item = cc.TableViewCell:create()

		local screenSize = cc.Director:getInstance():getWinSize()
		-- icon
		local icon = cc.Sprite:createWithSpriteFrameName(self.ICON_PATHS[index + 1])
		icon:setAnchorPoint(1, 0.5)
		icon:setPosition(screenSize.width * 0.06, screenSize.height * 0.04)
		icon:setTag(self.ICON_TAG)
		item:addChild(icon)
		-- label
		label = cc.Label:createWithTTF(self.ITEM_STRINGS[index + 1], GameConfig.DEFAULT_FONT_PATH, 20)
		label:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
		label:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
		label:setColor(ccc3(0, 0, 0))
		label:setAnchorPoint(0, 0.5)
		label:setPosition(screenSize.width * 0.065, screenSize.height * 0.04)
		label:setTag(self.LABEL_TAG)
		item:addChild(label)
	else
		label = item:getChildByTag(self.LABEL_TAG)
		tolua.cast(label, "cc.Label")
		label:setString(self.ITEM_STRINGS[index + 1])

		local icon = item:getChildByTag(self.ICON_TAG)
		tolua.cast(icon, "cc.Sprite")
		icon:setSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame(self.ICON_PATHS[index + 1]))
	end

	local isEnabled = self:validateItem(index)
	if not isEnabled then
		label:setColor(ccc3(200, 200, 200))
	else
		label:setColor(ccc3(0, 0, 0))
	end
	item.__isEnabled = isEnabled

	return item
end

function MapMenu:tableNumsOfCells(view)
	return #self.ITEM_STRINGS
end

-- TableView delegate
function MapMenu:tableCellTouched(view, cell)
	Notifier:notify(NotifyEvents.MapView.MenuItemSelected, cell)
end

function MapMenu:tableCellHighlight(view, cell)
	if cell.__isEnabled then
		local label = cell:getChildByTag(self.LABEL_TAG)
		label:setColor(ccc3(255, 0, 0))
	end
end

function MapMenu:tableCellUnhighlight(view, cell)
	if cell.__isEnabled then
		local label = cell:getChildByTag(self.LABEL_TAG)
		label:setColor(ccc3(0, 0, 0))
	end
end

function MapMenu:tableCellWillRecycle(view, cell)
end

end

------------------ Public Methods ------------------

function MapMenu:validateItem(index)
	local isEnabled = true
	if DataCenter.currentPlayerData.lastStep < self.SKIP_PETS_STEP then
		if index == 0 or index == 1 or index == 3 then
			isEnabled = false
		end
	elseif DataCenter.currentPlayerData.lastStep < self.SKIP_COLLECTION_STEP then
		if index == 0 or index == 3 then
			isEnabled = false
		end
	elseif DataCenter.currentPlayerData.lastStep < self.SKIP_CONTACT_STEP then
		if index == 3 then
			isEnabled = false
		end
	end

	return isEnabled
end