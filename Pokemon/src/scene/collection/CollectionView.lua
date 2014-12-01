--[[
	Description: Collection main view
	Author: M.Wan
	Date: 11/30/2014
]]

class("CollectionView", psGameLayer)

CollectionView.lastIndex = 1

CollectionView.root = nil

CollectionView.unknownIcon = nil
CollectionView.pokemonIcon = nil
CollectionView.lblDescription = nil
CollectionView.collectionList = nil

CollectionView.NAME_LABEL_TAG = 1001
CollectionView.BALL_TAG = 1002
CollectionView.SELECTION_TAG = 1003

CollectionView.__create = psGameLayer.create

function CollectionView:create()
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setCascadeOpacityEnabled(true)
	mask:retain()
	local layer = CollectionView:createWithTransitions(
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15))
		)
	layer.mask = mask
	layer:init()

	return layer
end

function CollectionView:init()
	local modalLayer = ModalLayer:create()
	self:addChild(modalLayer)
	self.root = modalLayer

	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/collection/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.root:addChild(bg)

	local lblTip = cc.Label:createWithTTF("【按取消键返回】", GameConfig.DEFAULT_FONT_PATH, 14)
	lblTip:setColor(COLOR3B_BLACK)
	lblTip:setPosition(90, 435)
	self.root:addChild(lblTip)

	local infoBack = cc.Sprite:createWithSpriteFrameName("images/common/common_scale9_1.png")
	infoBack:setPosition(112, 355)
	self.root:addChild(infoBack)

	local bgLbl = cc.Label:createWithTTF("全国图鉴", GameConfig.DEFAULT_FONT_PATH, 16)
	bgLbl:setAnchorPoint(0, 0.5)
	bgLbl:setColor(COLOR3B_BLACK)
	bgLbl:setPosition(infoBack:getContentSize().width * 0.15, infoBack:getContentSize().height * 0.8)
	infoBack:addChild(bgLbl)

	local lblDiscover = cc.Label:createWithTTF("已发现: " .. DataCenter:getDiscoverCount(), GameConfig.DEFAULT_FONT_PATH, 16)
	lblDiscover:setAnchorPoint(0, 0.5)
	lblDiscover:setColor(COLOR3B_BLACK)
	lblDiscover:setPosition(infoBack:getContentSize().width * 0.15, infoBack:getContentSize().height * 0.5)
	infoBack:addChild(lblDiscover)

	local lblCapture = cc.Label:createWithTTF("已捕获: " .. DataCenter:getCaptureCount(), GameConfig.DEFAULT_FONT_PATH, 16)
	lblCapture:setAnchorPoint(0, 0.5)
	lblCapture:setColor(COLOR3B_BLACK)
	lblCapture:setPosition(infoBack:getContentSize().width * 0.15, infoBack:getContentSize().height * 0.2)
	infoBack:addChild(lblCapture)

	local pokemonBack = cc.Sprite:createWithSpriteFrameName("images/collection/pokemon_back.png")
	pokemonBack:setPosition(345, 320)
	self.root:addChild(pokemonBack)

	local unknownIcon = cc.Sprite:createWithSpriteFrameName("images/collection/unknown_pokemon.png")
	unknownIcon:setScale(2)
	unknownIcon:setPosition(pokemonBack:getContentSize().width * 0.5, pokemonBack:getContentSize().height * 0.65)
	pokemonBack:addChild(unknownIcon)
	self.unknownIcon = unknownIcon

	local descriptionBack = cc.Sprite:createWithSpriteFrameName("images/collection/description_back.png")
	descriptionBack:setPosition(345, 115)
	self.root:addChild(descriptionBack)

	local lblDescription = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, 18)
	lblDescription:setDimensions(descriptionBack:getContentSize().width * 0.9, descriptionBack:getContentSize().height * 0.8)
	lblDescription:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
  	lblDescription:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_TOP)
	lblDescription:setColor(COLOR3B_BLACK)
	lblDescription:setPosition(descriptionBack:getContentSize().width * 0.5, descriptionBack:getContentSize().height * 0.5)
	descriptionBack:addChild(lblDescription)
	self.lblDescription = lblDescription

	local collectionBack = cc.Sprite:createWithSpriteFrameName("images/collection/collection_back.png")
	collectionBack:setPosition(640, 240)
	self.root:addChild(collectionBack)

	-- 道具list
	local collectionList = ListMenu:create(18)
	collectionList:setPosition(collectionBack:getContentSize().width * 0.5, collectionBack:getContentSize().height * 0.5)
	collectionBack:addChild(collectionList)

	collectionList:registerScriptHandler(MakeScriptHandler(self, self.countOfItemInMenu), pf.Handler.LISTMENU_COUNT_OF_ITEMS)
	collectionList:registerScriptHandler(MakeScriptHandler(self, self.itemAtIndex), pf.Handler.LISTMENU_ITEM_AT_INDEX)
	collectionList:registerScriptHandler(MakeScriptHandler(self, self.itemSizeForMenu), pf.Handler.LISTMENU_ITEM_SIZE_FOR_MENU)
	collectionList:setScriptDataSource()

	collectionList:registerScriptHandler(MakeScriptHandler(self, self.itemSelected), pf.Handler.LISTMENU_ITEM_SELECTED)
	collectionList:registerScriptHandler(MakeScriptHandler(self, self.itemFocused), pf.Handler.LISTMENU_ITEM_FOCUSED)
	collectionList:registerScriptHandler(MakeScriptHandler(self, self.itemBlurred), pf.Handler.LISTMENU_ITEM_BLURRED)
	collectionList:registerScriptHandler(MakeScriptHandler(self, self.itemWillRecycle), pf.Handler.LISTMENU_ITEM_WILL_RECYCLE)
	collectionList:setScriptDelegate()

	collectionList:setResponseKeyCodes(GameSettings.upKey, GameSettings.downKey, GameSettings.confirmKey)
	collectionList:setEventsSwallowed(false)

	-- selected item change event
	collectionList.onSelectedItemChanged = function(instance, oldIndex, newIndex)
		Notifier:notify(NotifyEvents.Collection.CollectionSelectionChanged, oldIndex, newIndex)
	end
	self.collectionList = collectionList

	self:reloadCollections()

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	if self.mask then
		self.root:addChild(self.mask, 999)
		self.mask:release()
	end
end

function CollectionView:onNodeEvent(event)
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

function CollectionView:onKeyboardPressed(keyCode)
	Notifier:notify(NotifyEvents.Collection.MainViewKeyResponsed, keyCode)
end

function CollectionView:reloadCollections()
	self.collectionList:reloadData()
end

function CollectionView:select(itemIndex)
	log("CollectionView:select", itemIndex)
	self.lblDescription:setString("???")
	if DataCenter.collectionData[itemIndex] ~= nil then
		local pokemonModel = PetInfo:create(itemIndex)
		self.unknownIcon:setVisible(false)
		if DataCenter.collectionData[itemIndex] then
			self.lblDescription:setString(pokemonModel.description)
		end
		-- pokemon icon
		local data = ZipHelper:getInstance():getFileDataInZip("images/pokemon_gif.rc", string.format("%03d.gif", pokemonModel.id), GameConfig.ZIP_PASSWORD)
		local frames = ImageUtils:getInstance():getGifFrames(data)
		local animate = ImageUtils:getInstance():createAnimationByFrames(frames, 0.1)
		if not self.pokemonIcon then
			self.pokemonIcon = cc.Sprite:create()
			self.pokemonIcon:setPosition(self.unknownIcon:getPosition())
			self.unknownIcon:getParent():addChild(self.pokemonIcon)
		end
		self.pokemonIcon:runAction(cc.RepeatForever:create(animate))
		self.pokemonIcon:setVisible(true)
	else
		self.unknownIcon:setVisible(true)
		if self.pokemonIcon then
			self.pokemonIcon:stopAllActions()
			self.pokemonIcon:setVisible(false)
		end
	end
end

-- DataSource interface
function CollectionView:itemSizeForMenu(menu)
	return 220, 20
end

function CollectionView:itemAtIndex(menu, index)
	log("CollectionView:itemAtIndex", index)
	local name = "???" 
	local captured = nil
	if DataCenter.collectionData[index + 1] ~= nil then
		local pokemonModel = PetInfo:create(index + 1)
		name = pokemonModel.name
		captured = DataCenter.collectionData[index + 1]
	end
	local item = menu:dequeueItem()
	if not item then
		item = ListMenuItem:create()

		-- selection
		local selection = cc.Scale9Sprite:createWithSpriteFrameName("images/collection/selection_back_yellow.png", CCRectMake(5, 5, 197, 19))
		selection:setPreferredSize(CCSizeMake(215, 19))
		selection:setAnchorPoint(0, 0.5)
		selection:setPosition(2.5, 10)
		selection:setTag(self.SELECTION_TAG)
		item:addChild(selection)
		selection:setVisible(false)
		-- name label
		local lblName = cc.Label:createWithTTF(string.format("No.%03d  %s", index + 1, name), GameConfig.DEFAULT_FONT_PATH, 18)
		lblName:setColor(ccc3(0, 0, 0))
		lblName:setAnchorPoint(0, 0.5)
		lblName:setPosition(40, 10)
		lblName:setTag(self.NAME_LABEL_TAG)
		item:addChild(lblName)
		-- capture ball
		local ball = cc.Sprite:createWithSpriteFrameName("images/collection/ball_owning.png")
		ball:setAnchorPoint(0, 0.5)
		ball:setPosition(10, 10)
		ball:setTag(self.BALL_TAG)
		item:addChild(ball)
		ball:setVisible(false)
		if captured then
			ball:setVisible(true)
		end
	else
		local lblName = item:getChildByTag(self.NAME_LABEL_TAG)
		tolua.cast(lblName, "cc.Label")
		lblName:setString(string.format("No.%03d  %s", index + 1, name))
		local ball = item:getChildByTag(self.BALL_TAG)
		if captured then
			ball:setVisible(true)
		end
	end

	return item
end

function CollectionView:countOfItemInMenu(menu)
	return 649
end

-- ListMenu delegate
function CollectionView:itemSelected(menu, item)
	Notifier:notify(NotifyEvents.Collection.CollectionSelected, menu:getIndexInAllItems())
end

function CollectionView:itemFocused(menu, item)
	local selection = item:getChildByTag(self.SELECTION_TAG)
	selection:setVisible(true)
	self:select(menu:getIndexInAllItems() + 1)
end

function CollectionView:itemBlurred(menu, item)
	local selection = item:getChildByTag(self.SELECTION_TAG)
	selection:setVisible(false)
end

function CollectionView:itemWillRecycle(menu, item)
	local ball = item:getChildByTag(self.BALL_TAG)
	ball:setVisible(false)
end