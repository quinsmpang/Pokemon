--[[
	Description: Bag main view
	Author: M.Wan
	Date: 11/27/2014
]]

class("BagMainView", psGameLayer)

BagMainView.root = nil

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
	lblDescription:setAnchorPoint(0, 1)
	lblDescription:setColor(COLOR3B_BLACK)
	lblDescription:setDimensions(335, 130)
	lblDescription:setHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT)
  	lblDescription:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_TOP)
  	lblDescription:setPosition(43, 175)
  	self.root:addChild(lblDescription)

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
	iconBorder:addChild(icon)

	-- 道具框
	local itemBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/item/items_back.png")
	itemBorder:setPosition(600, 240)
	self.root:addChild(itemBorder)

	-- 道具list

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
	titleSwitch:setAnchorPoint(0.5, 0.5)
	titleSwitch:setPosition(300, 440)
	self.root:addChild(titleSwitch)
	-- register title changed event
	titleBg.onTitleChanged = function(titleBg, oldIndex, newIndex)
		Notifier:notify(NotifyEvents.Bag.TitleChanged, oldIndex, newIndex)
	end

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
	end
	self.root:runAction(cc.RepeatForever:create(cc.Spawn:create(spawnAry)))

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))

	if self.mask then
		self.root:addChild(self.mask, 999)
		self.mask:release()
	end
end

function BagMainView:onNodeEvent(event)
	if event == "enter" then
		self.mask:runAction(cc.FadeOut:create(0.15))
	end
end