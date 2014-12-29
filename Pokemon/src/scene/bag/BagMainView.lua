--[[
	Description: Bag main view
	Author: M.Wan
	Date: 11/27/2014
]]

class("BagMainView", psGameLayer)

-- static, record last operations
BagMainView.lastTop = 0
BagMainView.lastIndexs = { [1] = 1, [2] = 1, [3] = 1, [4] = 1, [5] = 1, [7] = 1, [8] = 1 }
BagMainView.lastSubType = 1

BagMainView.root = nil
BagMainView.itemIcon = nil
BagMainView.itemList = nil
BagMainView.lblDescription = nil
BagMainView.titleSwitch = nil
BagMainView.upArrow = nil
BagMainView.downArrow = nil

BagMainView.enterType = nil		-- 来源

BagMainView.TITLE_STRINGS = {
	"一般道具",
	"回复道具",
	"精灵球",
	"技能机器",
	"树果",
	"战斗道具",
	"重要道具",
}
BagMainView.TITLE_TYPE_MAP = {
	1, 2, 3, 4, 5, 7, 8,
}

BagMainView.NAME_LABEL_TAG = 101
BagMainView.COUNT_LABEL_TAG = 102
BagMainView.CURSOR_TAG = 103

BagMainView.__create = psGameLayer.create

function BagMainView:create(enterType)
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setCascadeOpacityEnabled(true)
	mask:retain()
	local layer = BagMainView:createWithTransitions(
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15))
		)
	layer.mask = mask
	layer:init(enterType)

	return layer
end

function BagMainView:init(enterType)
	enterType = enterType or Enumerations.BAG_VIEW_SCENE_TYPE.VIEW_ITEMS
	self.enterType = enterType

	local modalLayer = ModalLayer:create()
	self:addChild(modalLayer)
	self.root = modalLayer

	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/item/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.root:addChild(bg)

	local lblTip = cc.Label:createWithTTF("【按取消键返回】", GameConfig.DEFAULT_FONT_PATH, 14)
	lblTip:setColor(COLOR3B_BLACK)
	lblTip:setPosition(80, 450)
	self.root:addChild(lblTip)

	local bag = cc.Sprite:createWithSpriteFrameName("images/item/bag_icon.png")
	bag:setPosition(70, 280)
	self.root:addChild(bag)

	-- 描述框
	local descriptionBorder = cc.Sprite:createWithSpriteFrameName("images/item/description_back.png")
	descriptionBorder:setPosition(210, 113)
	self.root:addChild(descriptionBorder)

	-- 描述
	local lblDescription = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, 20)
	lblDescription:setColor(COLOR3B_BLACK)
	lblDescription:setDimensions(335, 170)
	lblDescription:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
  	lblDescription:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_TOP)
  	lblDescription:setPosition(descriptionBorder:getContentSize().width * 0.5, descriptionBorder:getContentSize().height * 0.5)
  	descriptionBorder:addChild(lblDescription)
  	self.lblDescription = lblDescription

  	-- 图标框
  	local capInsets = CCRectMake(10, 10, 136, 96)
  	local iconBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/common/common_scale9_1.png", capInsets)
  	iconBorder:setPreferredSize(CCSizeMake(80, 80))
	iconBorder:setPosition(170, 250)
	self.root:addChild(iconBorder)

  	-- 图标
  	local data = ZipHelper:getInstance():getFileDataInZip("images/item_icon.rc", "1001.png", GameConfig.ZIP_PASSWORD)
	local icon = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	icon:setPosition(iconBorder:getContentSize().width * 0.5, iconBorder:getContentSize().height * 0.5)
	icon:setScale(1.5)
	iconBorder:addChild(icon)
	icon:setVisible(false)
	self.itemIcon = icon

	-- 道具框
	local itemBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/item/items_back.png")
	itemBorder:setPosition(600, 240)
	self.root:addChild(itemBorder)

	-- 道具list
	local itemList = ListMenu:create(16)
	itemList:setPosition(itemBorder:getContentSize().width * 0.5, itemBorder:getContentSize().height * 0.5)
	itemBorder:addChild(itemList)

	itemList:registerScriptHandler(MakeScriptHandler(self, self.countOfItemInMenu), pf.Handler.LISTMENU_COUNT_OF_ITEMS)
	itemList:registerScriptHandler(MakeScriptHandler(self, self.itemAtIndex), pf.Handler.LISTMENU_ITEM_AT_INDEX)
	itemList:registerScriptHandler(MakeScriptHandler(self, self.itemSizeForMenu), pf.Handler.LISTMENU_ITEM_SIZE_FOR_MENU)
	itemList:setScriptDataSource()

	itemList:registerScriptHandler(MakeScriptHandler(self, self.itemSelected), pf.Handler.LISTMENU_ITEM_SELECTED)
	itemList:registerScriptHandler(MakeScriptHandler(self, self.itemFocused), pf.Handler.LISTMENU_ITEM_FOCUSED)
	itemList:registerScriptHandler(MakeScriptHandler(self, self.itemBlurred), pf.Handler.LISTMENU_ITEM_BLURRED)
	itemList:registerScriptHandler(MakeScriptHandler(self, self.itemWillRecycle), pf.Handler.LISTMENU_ITEM_WILL_RECYCLE)
	itemList:setScriptDelegate()

	itemList:setResponseKeyCodes(GameSettings.upKey, GameSettings.downKey, GameSettings.confirmKey)
	itemList:setEventsSwallowed(false)

	-- selected item change event
	-- itemList.onSelectedItemChanged = function(instance, oldIndex, newIndex)
	-- 	Notifier:notify(NotifyEvents.Bag.ItemSelectionChanged, oldIndex, newIndex, self.TITLE_TYPE_MAP[self.titleSwitch:getCurrentIndex() + 1])
	-- end
	self.itemList = itemList

	-- 精灵球
	local ballIcon = cc.Sprite:createWithSpriteFrameName("images/item/pokemon_ball.png")
	ballIcon:setPosition(180, 440)
	self.root:addChild(ballIcon)

	-- 标题控件
  	local titleBg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/common_scale9_1.png", capInsets)
  	titleBg:setPreferredSize(CCSizeMake(200, 40))
	local titleSwitch = TitleSwitch:create(titleBg, self.TITLE_STRINGS, GameConfig.DEFAULT_FONT_PATH)
	titleSwitch:setTitleFontSize(22)
	titleSwitch:setTitleColor(COLOR3B_BLACK)
	titleSwitch:setResponseKeys(GameSettings.leftKey, GameSettings.rightKey)
	titleSwitch:setDuration(0.25)
	titleSwitch:setEventsSwallowed(false)
	titleSwitch:setAnchorPoint(0.5, 0.5)
	titleSwitch:setPosition(300, 440)
	if BagMainView.lastSubType then
		for k, v in pairs(self.TITLE_TYPE_MAP) do
			if v == BagMainView.lastSubType then
				titleSwitch:setCurrentIndex(k - 1)
				break
			end
		end
	end
	self.root:addChild(titleSwitch)
	-- register title changed event
	titleSwitch.onTitleChanged = function(titleBg, oldIndex, newIndex)
		Notifier:notify(NotifyEvents.Bag.TitleChanged, oldIndex, newIndex, self.TITLE_TYPE_MAP[newIndex + 1])
	end
	self.titleSwitch = titleSwitch

	-- arrows
	local posMap = { ccp(600, 460), ccp(200, 440), ccp(600, 25), ccp(400, 440) }
	local actionMap = {
		cc.Sequence:create(cc.MoveTo:create(0.5, ccp(600, 470)), cc.MoveTo:create(0.5, ccp(600, 460))),
		cc.Sequence:create(cc.MoveTo:create(0.5, ccp(190, 440)), cc.MoveTo:create(0.5, ccp(200, 440))),
		cc.Sequence:create(cc.MoveTo:create(0.5, ccp(600, 15)), cc.MoveTo:create(0.5, ccp(600, 25))),
		cc.Sequence:create(cc.MoveTo:create(0.5, ccp(410, 440)), cc.MoveTo:create(0.5, ccp(400, 440))),
	}
	local arrow = nil
	local spawnAry = {}
	for i = 1, 4 do
		arrow = cc.Sprite:createWithSpriteFrameName("images/common/arrow.png")
		arrow:setPosition(posMap[i])
		arrow:setRotation(180 - (i - 1) * 90)
		self.root:addChild(arrow)
		table.insert(spawnAry, cc.TargetedAction:create(arrow, actionMap[i]))
		if i == 1 then
			self.upArrow = arrow
		elseif i == 3 then
			self.downArrow = arrow
		end
	end
	self.root:runAction(cc.RepeatForever:create(cc.Spawn:create(spawnAry)))

	-- items list handle
	self:reloadItems()

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	if self.mask then
		self.root:addChild(self.mask, 999)
		self.mask:release()
	end
end

function BagMainView:onNodeEvent(event)
	if event == "enter" then
		self.mask:runAction(cc.FadeOut:create(0.15))

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

function BagMainView:onKeyboardPressed(keyCode)
	Notifier:notify(NotifyEvents.Bag.MainViewKeyResponsed, keyCode)
end

function BagMainView:generateItemsList(subType)
	log("BagMainView:generateItemsList", subType)
	local list = {}

	if DataCenter.currentBagData and DataCenter.currentBagData[subType] then
		for _, v in ipairs(DataCenter.currentBagData[subType]) do
			local itemId = v[1]
			local model = ItemInfo:create(itemId)
			table.insert(list, { model.name, v[2] })
		end
	end

	return list
end

function BagMainView:reloadItems()
	log("BagMainView:reloadItems")
	-- 清空图标和描述信息
	self.itemIcon:setVisible(false)
	self.lblDescription:setString("")
	self.itemsData = self:generateItemsList(BagMainView.lastSubType)
	self.itemList:reloadData()
	self.upArrow:setVisible(self.itemList:isTopOverflowed())
	self.downArrow:setVisible(self.itemList:isBottomOverflowed())
end

function BagMainView:select(itemIndex)
	log("BagMainView:select", itemIndex)
	local curSubType = self.TITLE_TYPE_MAP[self.titleSwitch:getCurrentIndex() + 1]
	local itemId = DataCenter.currentBagData[curSubType][itemIndex][1]
	-- update icon and description
	local data = ZipHelper:getInstance():getFileDataInZip("images/item_icon.rc", itemId .. ".png", GameConfig.ZIP_PASSWORD)
	local frame = ImageUtils:getInstance():createSpriteFrameWithBinaryData(data)
	self.itemIcon:setSpriteFrame(frame)
	self.itemIcon:setVisible(true)

	local model = ItemInfo:create(itemId)
	self.lblDescription:setString(model.description)
end

-- DataSource interface
function BagMainView:itemSizeForMenu(menu)
	return 360, 24
end

function BagMainView:itemAtIndex(menu, index)
	log("BagMainView:itemAtIndex", index)
	local item = menu:dequeueItem()
	if not item then
		item = ListMenuItem:create()

		local screenSize = cc.Director:getInstance():getWinSize()
		-- name label
		local lblName = cc.Label:createWithTTF(self.itemsData[index + 1][1], GameConfig.DEFAULT_FONT_PATH, 22)
		lblName:setColor(ccc3(0, 0, 0))
		lblName:setAnchorPoint(0, 0.5)
		lblName:setPosition(40, 12)
		lblName:setTag(self.NAME_LABEL_TAG)
		item:addChild(lblName)
		-- count label
		local lblCount = cc.Label:createWithTTF("x " .. self.itemsData[index + 1][2], GameConfig.DEFAULT_FONT_PATH, 22)
		lblCount:setColor(ccc3(0, 0, 0))
		lblCount:setAnchorPoint(1, 0.5)
		lblCount:setPosition(340, 12)
		lblCount:setTag(self.COUNT_LABEL_TAG)
		item:addChild(lblCount)
		-- arrow
		local arrow = cc.Sprite:createWithSpriteFrameName("images/common/menu_cursor.png")
		arrow:setAnchorPoint(1, 0.5)
		arrow:setPosition(35, 12)
		arrow:setTag(self.CURSOR_TAG)
		arrow:setVisible(false)
		item:addChild(arrow)
	else
		local lblName = item:getChildByTag(self.NAME_LABEL_TAG)
		tolua.cast(lblName, "cc.Label")
		lblName:setString(self.itemsData[index + 1][1])
		local lblCount = item:getChildByTag(self.COUNT_LABEL_TAG)
		tolua.cast(lblCount, "cc.Label")
		lblCount:setString("x " .. self.itemsData[index + 1][2])
	end

	return item
end

function BagMainView:countOfItemInMenu(menu)
	log("BagMainView:countOfItemInMenu", #self.itemsData)
	return #self.itemsData
end

-- ListMenu delegate
function BagMainView:itemSelected(menu, item)
	Notifier:notify(NotifyEvents.Bag.ItemSelected, menu:getIndexInAllItems())
end

function BagMainView:itemFocused(menu, item)
	local cursor = item:getChildByTag(self.CURSOR_TAG)
	cursor:setVisible(true)
	self:select(menu:getIndexInAllItems() + 1)
end

function BagMainView:itemBlurred(menu, item)
	local cursor = item:getChildByTag(self.CURSOR_TAG)
	cursor:setVisible(false)
end

function BagMainView:itemWillRecycle(menu, item)
end