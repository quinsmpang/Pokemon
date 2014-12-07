--[[
	Description: Collection detail view
	Author: M.Wan
	Date: 12/3/2014
]]

class("CollectionDetailView", psGameLayer)

require "src/scene/collection/CollectionDetailViewAdapter"
require "src/scene/collection/CollectionSizeViewAdapter"

CollectionDetailView.root = nil

CollectionDetailView.btns = nil
CollectionDetailView.selection = nil
CollectionDetailView.detailBg = nil

CollectionDetailView.pokemonModel = nil
CollectionDetailView.selectedIndex = nil

CollectionDetailView.adapter = nil

CollectionDetailView.__create = psGameLayer.create

function CollectionDetailView:create(pokemonId)
	local mask = cc.LayerColor:create(ccc4(0, 0, 0, 255))
	mask:setCascadeOpacityEnabled(true)
	mask:retain()
	local layer = CollectionDetailView:createWithTransitions(
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeOut:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15)),
		cc.TargetedAction:create(mask, cc.FadeIn:create(0.15))
		)
	layer.mask = mask
	layer:init(pokemonId)

	return layer
end

function CollectionDetailView:init(pokemonId)
	self.pokemonModel = PetInfo:create(pokemonId)

	local modalLayer = ModalLayer:create()
	self:addChild(modalLayer)
	self.root = modalLayer

	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/collection/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.root:addChild(bg)

	local lblTip = cc.Label:createWithTTF("【按取消键返回】", GameConfig.DEFAULT_FONT_PATH, 14)
	lblTip:setAnchorPoint(1, 1)
	lblTip:setPosition(winSize.width * 0.95, winSize.height * 0.95)
	self.root:addChild(lblTip)

	-- four tabs
	self.btns = {}
	local btnTexts = { "详 情", "分 布", "体 型" }
	local capInsets = CCRectMake(10, 10, 80, 80)
	local btnSize = CCSizeMake(150, 50)
	for i = 1, #btnTexts do
		local sp = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_aqua.png", capInsets)
		sp:setPreferredSize(btnSize)
		sp:setPosition(winSize.width * (0.2 + (i - 1) * 0.2), winSize.height * 0.92)
		self.root:addChild(sp)
		table.insert(self.btns, sp)

		local btnText = cc.Label:createWithTTF(btnTexts[i], GameConfig.DEFAULT_FONT_PATH, 24)
		btnText:setColor(COLOR3B_BLACK)
		btnText:setPosition(sp:getContentSize().width * 0.5, sp:getContentSize().height * 0.5)
		sp:addChild(btnText)
	end

	local selection = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red_transparent.png", capInsets)
	selection:setPreferredSize(btnSize)
	self.root:addChild(selection)
	self.selection = selection

	local detailBg = cc.Sprite:createWithSpriteFrameName("images/collection/scroll.png")
	detailBg:setPosition(winSize.width * 0.5, winSize.height * 0.45)
	self.root:addChild(detailBg)
	self.detailBg = detailBg

	self:select(1)

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	if self.mask then
		self.root:addChild(self.mask, 999)
		self.mask:release()
	end
end

function CollectionDetailView:onNodeEvent(event)
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

function CollectionDetailView:onKeyboardPressed(keyCode)
	Notifier:notify(NotifyEvents.Collection.DetailViewKeyResponsed, keyCode)
end

function CollectionDetailView:select(index)
	if self.selectedIndex == index then
		return
	end

	local adapter = nil
	if index == 1 then
		-- 详情
		adapter = CollectionDetailViewAdapter:new()
		adapter:adapt(self)
	elseif index == 2 then
		-- 分布todo
	elseif index == 3 then
		-- 体型
		adapter = CollectionSizeViewAdapter:new()
		adapter:adapt(self)
	end

	self.selection:setPosition(self.btns[index]:getPosition())
	self.selectedIndex = index
end