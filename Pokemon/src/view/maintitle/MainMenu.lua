--[[
	Description: main menu layer
	Author: M.Wan
	Date: 05/17/2014
]]

class("MainMenu", psLayer)

MainMenu.btnNewGame = nil		--新游戏按钮
MainMenu.btnLoadGame = nil		--读取存档按钮
MainMenu.btnSettings = nil		--设定按钮
MainMenu.savesWindow = nil 		--存档窗口
MainMenu.settingsWindow = nil 	--设置窗口

-- const values
MainMenu.BTNNEWGAME_TEXT = "新 的 旅 程"
MainMenu.BTNLOADGAME_TEXT = "继 续 旅 程"
MainMenu.BTNSETTINGS_TEXT = "游 戏 设 置"
MainMenu.BTN_FONTNAME = "Arial"
MainMenu.BTN_FONTSIZE = 26
MainMenu.BTN_FONTCOLOR = ccc3(0, 120, 255)
MainMenu.BTN_TEXT_POSITION_X = 260

-- static method
function MainMenu:initUI()
	log("MainMenu:initUI")
	self:setCascadeOpacityEnabled(true)
	self:setOpacity(0)

	local screenSize = cc.Director:getInstance():getWinSize()

	-- background
	local back = cc.Sprite:createWithSpriteFrameName("images/maintitle/menu_back.jpg")
	back:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	self:addChild(back)

	-- new game button
	local capInsets = CCRectMake(20, 20, 60, 60)
	local normalImage = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_red.png", capInsets)
	normalImage:setPreferredSize(CCSizeMake(500, 50))
	local selectedImage = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_aqua.png", capInsets)
	selectedImage:setPreferredSize(CCSizeMake(500, 50))
	self.btnNewGame = cc.MenuItemSprite:create(normalImage, selectedImage)
	self.btnNewGame:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnNewGameClicked))
	local newGameMenu = cc.Menu:create(self.btnNewGame)
	newGameMenu:setPosition(screenSize.width * 0.5, screenSize.height * 0.85)
	self:addChild(newGameMenu)
	local newGameLabel = cc.Label:createWithSystemFont(self.BTNNEWGAME_TEXT, self.BTN_FONTNAME, self.BTN_FONTSIZE)
	newGameLabel:setCascadeOpacityEnabled(true)
	newGameLabel:setPosition(self.BTN_TEXT_POSITION_X, screenSize.height * 0.85)
	newGameLabel:setColor(self.BTN_FONTCOLOR)
	self:addChild(newGameLabel)

	-- load game button
	normalImage = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_orange.png", capInsets)
	normalImage:setPreferredSize(CCSizeMake(500, 50))
	selectedImage = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_aqua.png", capInsets)
	selectedImage:setPreferredSize(CCSizeMake(500, 50))
	self.btnLoadGame = cc.MenuItemSprite:create(normalImage, selectedImage)
	self.btnLoadGame:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnLoadGameClicked))
	local loadGameMenu = cc.Menu:create(self.btnLoadGame)
	loadGameMenu:setPosition(screenSize.width * 0.5, screenSize.height * 0.65)
	self:addChild(loadGameMenu)
	local loadGameLabel = cc.Label:createWithSystemFont(self.BTNLOADGAME_TEXT, self.BTN_FONTNAME, self.BTN_FONTSIZE)
	loadGameLabel:setCascadeOpacityEnabled(true)
	loadGameLabel:setPosition(self.BTN_TEXT_POSITION_X, screenSize.height * 0.65)
	loadGameLabel:setColor(self.BTN_FONTCOLOR)
	self:addChild(loadGameLabel)

	-- setting button
	normalImage = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_yellow.png", capInsets)
	normalImage:setPreferredSize(CCSizeMake(500, 50))
	selectedImage = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_aqua.png", capInsets)
	selectedImage:setPreferredSize(CCSizeMake(500, 50))
	self.btnSettings = cc.MenuItemSprite:create(normalImage, selectedImage)
	self.btnSettings:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnSettingsClicked))
	local settingsMenu = cc.Menu:create(self.btnSettings)
	settingsMenu:setPosition(screenSize.width * 0.5, screenSize.height * 0.45)
	self:addChild(settingsMenu)
	local settingsLabel = cc.Label:createWithSystemFont(self.BTNSETTINGS_TEXT, self.BTN_FONTNAME, self.BTN_FONTSIZE)
	settingsLabel:setCascadeOpacityEnabled(true)
	settingsLabel:setPosition(self.BTN_TEXT_POSITION_X, screenSize.height * 0.45)
	settingsLabel:setColor(self.BTN_FONTCOLOR)
	self:addChild(settingsLabel)

	self.btnNewGame:setVisible(false)
	self.btnLoadGame:setVisible(false)
	self.btnSettings:setVisible(false)
end

function MainMenu:showButtons()
	self.btnNewGame:setVisible(true)
	self.btnLoadGame:setVisible(true)
	self.btnSettings:setVisible(true)
end

-- btn callbacks
function MainMenu:onBtnNewGameClicked()
	log("MainMenu:onBtnNewGameClicked")
end

function MainMenu:onBtnLoadGameClicked()
	log("MainMenu:onBtnLoadGameClicked")
end

function MainMenu:onBtnSettingsClicked()
	log("MainMenu:onBtnSettingsClicked")
end