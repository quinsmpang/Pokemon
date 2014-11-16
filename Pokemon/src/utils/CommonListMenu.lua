--[[
	Description: Dynamic menu list control, common
	Author: M.Wan
	Date: 11/12/2014
]]

class("CommonListMenu", psLayer)

-- ui
CommonListMenu.listMenu = nil	-- ListMenu control

CommonListMenu.stringList = nil		-- 内容列表
CommonListMenu.borderSize = nil		-- 外框尺寸
CommonListMenu.itemSelectedScript = nil
CommonListMenu.toBeClosed = nil
CommonListMenu.cancelScript = nil

CommonListMenu.LABEL_TAG = 998
CommonListMenu.ARROW_TAG = 999

CommonListMenu.__create = psLayer.create

-- param list is a table with shown strings.
function CommonListMenu:create(list, borderSize)
	local menu = CommonListMenu:__create()
	menu:init(list, borderSize)
	return menu
end

function CommonListMenu:init(list, borderSize)
	self.stringList = list
	self.borderSize = borderSize
	self.toBeClosed = false

	local winSize = cc.Director:getInstance():getWinSize()

	local root = ModalLayer:create()
	root:setOpacity(0)
	self:addChild(root)

	local bg = cc.Scale9Sprite:createWithSpriteFrameName("images/pokemon/selection_border.png", CCRectMake(20, 20, 196, 257))
	bg:setPreferredSize(borderSize)
	bg:setAnchorPoint(0, 0)
	bg:setPosition(0, 0)
	root:addChild(bg)

	self.listMenu = ListMenu:create(#self.stringList)
	self.listMenu:registerScriptHandler(MakeScriptHandler(self, self.countOfItemInMenu), pf.Handler.LISTMENU_COUNT_OF_ITEMS)
	self.listMenu:registerScriptHandler(MakeScriptHandler(self, self.itemAtIndex), pf.Handler.LISTMENU_ITEM_AT_INDEX)
	self.listMenu:registerScriptHandler(MakeScriptHandler(self, self.itemSizeForMenu), pf.Handler.LISTMENU_ITEM_SIZE_FOR_MENU)
	self.listMenu:setScriptDataSource()

	self.listMenu:registerScriptHandler(MakeScriptHandler(self, self.itemSelected), pf.Handler.LISTMENU_ITEM_SELECTED)
	self.listMenu:registerScriptHandler(MakeScriptHandler(self, self.itemFocused), pf.Handler.LISTMENU_ITEM_FOCUSED)
	self.listMenu:registerScriptHandler(MakeScriptHandler(self, self.itemBlurred), pf.Handler.LISTMENU_ITEM_BLURRED)
	self.listMenu:registerScriptHandler(MakeScriptHandler(self, self.itemWillRecycle), pf.Handler.LISTMENU_ITEM_WILL_RECYCLE)
	self.listMenu:setScriptDelegate()

	self.listMenu:setResponseKeyCodes(GameSettings.upKey, GameSettings.downKey, GameSettings.confirmKey)

	self.listMenu:setPosition(bg:getContentSize().width * 0.5, bg:getContentSize().height * 0.5)
	bg:addChild(self.listMenu)

	self:ignoreAnchorPointForPosition(false)
	self:setContentSize(bg:getContentSize())
	self:setAnchorPoint(0.5, 0.5)

	self.listMenu:reloadData()

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function CommonListMenu:setCancelScript(script)
	self.cancelScript = script
end

function CommonListMenu:onNodeEvent(event)
	if event == "enter" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		end
	elseif event == "exit" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
			self.kbdListener = nil
		end
	end
end

function CommonListMenu:onKeyboardPressed(keyCode)
	if self.toBeClosed then
		self:removeFromParent()
	elseif keyCode == GameSettings.cancelKey then
		if self.cancelScript then
			self.cancelScript()
		else
			self:removeFromParent()
		end
	end
end

function CommonListMenu:setItemSelectedScript(script)
	assert(type(script) == "function", "invalid param")
	self.itemSelectedScript = script
end

function CommonListMenu:markExit()
	self.toBeClosed = true
end

-- DataSource interface
function CommonListMenu:itemSizeForMenu(menu)
	local winSize = cc.Director:getInstance():getWinSize()
	return self.borderSize.width, winSize.height * 0.08
end

function CommonListMenu:itemAtIndex(menu, index)
	log("CommonListMenu:itemAtIndex", index)
	local item = menu:dequeueItem()
	if not item then
		item = ListMenuItem:create()

		local screenSize = cc.Director:getInstance():getWinSize()
		-- label
		local label = cc.Label:createWithTTF(self.stringList[index + 1], GameConfig.DEFAULT_FONT_PATH, 20)
		label:setDimensions(screenSize.width * 0.1, screenSize.height * 0.08)
		label:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
		label:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
		label:setColor(ccc3(0, 0, 0))
		label:setAnchorPoint(0, 0.5)
		label:setPosition(screenSize.width * 0.065, screenSize.height * 0.04)
		label:setTag(self.LABEL_TAG)
		item:addChild(label)
		-- arrow
		local arrow = cc.Sprite:createWithSpriteFrameName("images/pokemon/menu_cursor.png")
		arrow:setAnchorPoint(1, 0.5)
		arrow:setPosition(screenSize.width * 0.05, screenSize.height * 0.04)
		arrow:setTag(self.ARROW_TAG)
		arrow:setVisible(false)
		item:addChild(arrow)
	else
		local label = item:getChildByTag(self.LABEL_TAG)
		tolua.cast(label, "cc.Label")
		label:setString(self.stringList[index + 1])
	end

	return item
end

function CommonListMenu:countOfItemInMenu(menu)
	return #self.stringList
end

-- ListMenu delegate
function CommonListMenu:itemSelected(menu, item)
	if self.itemSelectedScript then
		self.itemSelectedScript(menu, item)
	end
end

function CommonListMenu:itemFocused(menu, item)
	local cursor = item:getChildByTag(self.ARROW_TAG)
	cursor:setVisible(true)
end

function CommonListMenu:itemBlurred(menu, item)
	local cursor = item:getChildByTag(self.ARROW_TAG)
	cursor:setVisible(false)
end

function CommonListMenu:itemWillRecycle(menu, item)
end