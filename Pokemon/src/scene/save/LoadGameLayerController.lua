--[[
	Description: Game load game dialog controller
	Author: M.Wan
	Date: 11/23/2014
]]

class("LoadGameLayerController", psViewController)

require "src/scene/save/GameSaveManager"

LoadGameLayerController.dialog = nil
LoadGameLayerController.enterType = nil
LoadGameLayerController.infoList = nil

function LoadGameLayerController:load()
	log("LoadGameLayerController:load")
	self:addObservers()

	self:renderView()
end

function LoadGameLayerController:unload()
	self:removeObservers()

	if self.dialog then
		self.dialog:removeFromParent()
	end
end

function LoadGameLayerController:addObservers()

end

function LoadGameLayerController:removeObservers()

end

function LoadGameLayerController:renderView()
	self.dialog = ModalLayer:create()
	self.dialog:setOpacity(0)
	self.dialog:setScale(0)
	self.dialog:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
	self:getScene():addChild(self.dialog)

	self.enterType = self:getScene():getIntAttribute(GameConfig.MAINVIEW_KEY)

	local winSize = cc.Director:getInstance():getWinSize()

	local dialogBorder = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", CCRectMake(20, 20, 60, 60))
	dialogBorder:setPreferredSize(CCSizeMake(500, 450))
	dialogBorder:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.dialog:addChild(dialogBorder)

	if not IOUtils:getInstance():directoryExists("save") then
		IOUtils:getInstance():createDirectory("save")
	end

	local menu = cc.Menu:create()
	menu:setPosition(0, 0)
	dialogBorder:addChild(menu)

	self.infoList = {}
	for i = 1, 3 do
		local bExist = IOUtils:getInstance():fileExists("save/ps_save" .. i .. ".sav")

		local normalBtnBg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_aqua.png", CCRectMake(20, 20, 60, 60))
		normalBtnBg:setPreferredSize(CCSizeMake(460, 120))
		local selectedBtnBg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_yellow.png", CCRectMake(20, 20, 60, 60))
		selectedBtnBg:setPreferredSize(CCSizeMake(460, 120))
		local disableBtnBg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_gray.png", CCRectMake(20, 20, 60, 60))
		disableBtnBg:setPreferredSize(CCSizeMake(460, 120))
		local btn = cc.MenuItemSprite:create(normalBtnBg, selectedBtnBg, disableBtnBg)
		btn:setPosition(250, 380 - (i - 1) % 3 * 130)
		btn:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnClick, i))
		menu:addChild(btn, 0, i)

		if bExist then
			local info = GameSaveManager:getBasicInfo(i)
			self.infoList[i] = info

			local node = cc.Node:create()
			node:setPosition(41.67, 415 - (i - 1) % 3 * 130)
			dialogBorder:addChild(node)

			local titleMap = { "地点", "时间", "图鉴", "徽章" }
			local textMap = { "MapName", "GameTime", "Collection", "Brands" }
			for j = 1, 4 do
				local lbl = cc.Label:createWithTTF(titleMap[j] .. ": " .. info[textMap[j]], GameConfig.DEFAULT_FONT_PATH, 24)
				lbl:setAnchorPoint(0, 0.5)
				lbl:setColor(COLOR3B_RED)
				lbl:setPosition(0 + (j - 1) % 2 * 215, 0 - 65 * math.floor((j - 1) / 2))
				node:addChild(lbl)
			end
		else
			local btnLabel = cc.Label:createWithTTF("Empty", GameConfig.DEFAULT_FONT_PATH, 24)
			btnLabel:setColor(COLOR3B_BLACK)
			btnLabel:setPosition(btn:getContentSize().width * 0.5, btn:getContentSize().height * 0.5)
			if self.enterType == 2 then
				btn:setEnabled(false)
			end
			btn:addChild(btnLabel)
		end
	end

	local btnBackLabel = cc.Label:createWithTTF("返回", GameConfig.DEFAULT_FONT_PATH, 22)
	btnBackLabel:setColor(COLOR3B_BLACK)
	local btnBack = cc.Scale9Sprite:createWithSpriteFrameName("images/common/white_back.png", CCRectMake(1, 1, 1, 1))
	btnBack = cc.ControlButton:create(btnBackLabel, btnBack)
	btnBack:setAnchorPoint(0.5, 0.5)
	btnBack:setPosition(dialogBorder:getContentSize().width * 0.5, 30)
	btnBack:registerControlEventHandler(MakeScriptHandler(self, self.onBtnBackClick), cc.Handler.CONTROL_TOUCH_UP_INSIDE)
	dialogBorder:addChild(btnBack)
end

function LoadGameLayerController:onNodeEvent(event)
	if event == "enter" then
		local enterAction = cc.Sequence:create(
			cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
			cc.ScaleTo:create(0.03, 1)
			)

		self.dialog:runAction(enterAction)
	end
end

function LoadGameLayerController:onBtnClick(tag)
	log("LoadGameLayerController:onBtnClick", tag)

	if self.enterType == 1 then
		if self.infoList[tag] then
			-- 弹出确认框
			DialogPopHelper:popQuestionWindow(CCSizeMake(200, 150), "确认选择这个存档点吗？", MakeScriptHandler(self, self.onChoiceConfirm, tag), MakeScriptHandler(self, self.onChoiceCancel))
		else
			cc.SimpleAudioEngine:getInstance():stopMusic()
			self:onChoiceConfirm(tag)
		end
	elseif self.enterType == 2 then
		cc.SimpleAudioEngine:getInstance():stopMusic()

		GameSaveManager:load(tag)
	end
end

function LoadGameLayerController:onBtnBackClick(sender)
	self:getScene():unloadViewController(self)
end

function LoadGameLayerController:onChoiceConfirm(index)
	log("LoadGameLayerController:onChoiceConfirm", index)
	DataCenter.relatedSaveIndex = index
	Notifier:notify(NotifyEvents.SaveView.SaveSelected)
	self:getScene():unloadViewController(self)
end

function LoadGameLayerController:onChoiceCancel()
end