--[[
	Description: main menu layer
	Author: M.Wan
	Date: 05/17/2014
]]

require "src/view/map/MapViewScene"
require "src/view/maintitle/SettingsLayer"
require "src/view/maintitle/KeysetLayer"
require "src/view/maintitle/GenderChooseLayer"

class("MainMenu", psLayer)

MainMenu.btnNewGame = nil		--新游戏按钮
MainMenu.btnLoadGame = nil		--读取存档按钮
MainMenu.btnSettings = nil		--游戏设定按钮
MainMenu.btnKeySet = nil 		--按键设定按钮
MainMenu.savesWindow = nil 		--存档窗口
MainMenu.settingsWindow = nil 	--游戏设置窗口
MainMenu.keysetWindow = nil 	--按键设置窗口

-- const values
MainMenu.BTNNEWGAME_TEXT = "新 的 旅 程"
MainMenu.BTNLOADGAME_TEXT = "继 续 旅 程"
MainMenu.BTNSETTINGS_TEXT = "游 戏 设 置"
MainMenu.BTNKEYSET_TEXT = "按 键 设 置"
MainMenu.BTN_FONTSIZE = 26
MainMenu.BTN_FONTCOLOR = ccc3(0, 120, 255)
MainMenu.BTN_SIZE = CCSizeMake(200, 50)

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
	local normalImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", capInsets)
	normalImage:setPreferredSize(self.BTN_SIZE)
	local selectedImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	selectedImage:setPreferredSize(self.BTN_SIZE)
	self.btnNewGame = cc.MenuItemSprite:create(normalImage, selectedImage)
	self.btnNewGame:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnNewGameClicked))
	local newGameMenu = cc.Menu:create(self.btnNewGame)
	newGameMenu:setPosition(screenSize.width * 0.52, screenSize.height * 0.54)
	self:addChild(newGameMenu)
	local newGameLabel = cc.Label:createWithTTF(self.BTNNEWGAME_TEXT, GameConfig.DEFAULT_FONT_PATH, self.BTN_FONTSIZE)
	newGameLabel:setCascadeOpacityEnabled(true)
	newGameLabel:setPosition(screenSize.width * 0.52, screenSize.height * 0.54)
	newGameLabel:setColor(self.BTN_FONTCOLOR)
	self:addChild(newGameLabel)

	-- load game button
	normalImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", capInsets)
	normalImage:setPreferredSize(self.BTN_SIZE)
	selectedImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	selectedImage:setPreferredSize(self.BTN_SIZE)
	self.btnLoadGame = cc.MenuItemSprite:create(normalImage, selectedImage)
	self.btnLoadGame:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnLoadGameClicked))
	local loadGameMenu = cc.Menu:create(self.btnLoadGame)
	loadGameMenu:setPosition(screenSize.width * 0.52, screenSize.height * 0.42)
	self:addChild(loadGameMenu)
	local loadGameLabel = cc.Label:createWithTTF(self.BTNLOADGAME_TEXT, GameConfig.DEFAULT_FONT_PATH, self.BTN_FONTSIZE)
	loadGameLabel:setCascadeOpacityEnabled(true)
	loadGameLabel:setPosition(screenSize.width * 0.52, screenSize.height * 0.42)
	loadGameLabel:setColor(self.BTN_FONTCOLOR)
	self:addChild(loadGameLabel)

	-- setting button
	normalImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", capInsets)
	normalImage:setPreferredSize(self.BTN_SIZE)
	selectedImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	selectedImage:setPreferredSize(self.BTN_SIZE)
	self.btnSettings = cc.MenuItemSprite:create(normalImage, selectedImage)
	self.btnSettings:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnSettingsClicked))
	local settingsMenu = cc.Menu:create(self.btnSettings)
	settingsMenu:setPosition(screenSize.width * 0.52, screenSize.height * 0.3)
	self:addChild(settingsMenu)
	local settingsLabel = cc.Label:createWithTTF(self.BTNSETTINGS_TEXT, GameConfig.DEFAULT_FONT_PATH, self.BTN_FONTSIZE)
	settingsLabel:setCascadeOpacityEnabled(true)
	settingsLabel:setPosition(screenSize.width * 0.52, screenSize.height * 0.3)
	settingsLabel:setColor(self.BTN_FONTCOLOR)
	self:addChild(settingsLabel)

	-- keyset button
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		normalImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_red.png", capInsets)
		normalImage:setPreferredSize(self.BTN_SIZE)
		selectedImage = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
		selectedImage:setPreferredSize(self.BTN_SIZE)
		self.btnKeySet = cc.MenuItemSprite:create(normalImage, selectedImage)
		self.btnKeySet:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnKeysetClicked))
		local keysetMenu = cc.Menu:create(self.btnKeySet)
		keysetMenu:setPosition(screenSize.width * 0.52, screenSize.height * 0.18)
		self:addChild(keysetMenu)
		local keysetLabel = cc.Label:createWithTTF(self.BTNKEYSET_TEXT, GameConfig.DEFAULT_FONT_PATH, self.BTN_FONTSIZE)
		keysetLabel:setCascadeOpacityEnabled(true)
		keysetLabel:setPosition(screenSize.width * 0.52, screenSize.height * 0.18)
		keysetLabel:setColor(self.BTN_FONTCOLOR)
		self:addChild(keysetLabel)

		self.btnKeySet:setVisible(false)
	end

	self.btnNewGame:setVisible(false)
	self.btnLoadGame:setVisible(false)
	self.btnSettings:setVisible(false)
end

function MainMenu:showButtons()
	self.btnNewGame:setVisible(true)
	self.btnLoadGame:setVisible(true)
	self.btnSettings:setVisible(true)

	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		self.btnKeySet:setVisible(true)
	end
end

function MainMenu:showGenderWindow()
	local genderChooseLayer = GenderChooseLayer:create()
	genderChooseLayer:initUI()
	self:addChild(genderChooseLayer)
end

-- btn callbacks
function MainMenu:onBtnNewGameClicked()
	log("MainMenu:onBtnNewGameClicked")
	GameVolumeHelper:playBtnClickSound()
	cc.SimpleAudioEngine:getInstance():stopMusic()

	local quitAction = cc.Sequence:create(
		cc.FadeOut:create(1.5),
		cc.DelayTime:create(0.5),
		cc.CallFunc:create(MakeScriptHandler(self, self.showGenderWindow))
		)
	self:runAction(quitAction)
	-- local mapViewScene = MapViewScene:create()
	-- cc.Director:getInstance():replaceScene(cc.TransitionFade:create(2, mapViewScene, ccc3(0, 0, 0)))
end

function MainMenu:onBtnLoadGameClicked()
	log("MainMenu:onBtnLoadGameClicked")
	GameVolumeHelper:playBtnClickSound()

	-- require "src/controller/pokemon/PokemonViewController"

	-- local pokemonViewController = PokemonViewController:create()
	-- local curScene = cc.Director:getInstance():getRunningScene()
	-- tolua.cast(curScene, "ps.GameScene")
	-- curScene:loadViewController(pokemonViewController)
end

function MainMenu:onBtnSettingsClicked()
	log("MainMenu:onBtnSettingsClicked")
	GameVolumeHelper:playBtnClickSound()

	self.settingsWindow = SettingsLayer:create()
	self.settingsWindow:initUI()
	self:addChild(self.settingsWindow)
end

function MainMenu:onBtnKeysetClicked()
	log("MainMenu:onBtnKeysetClicked")
	GameVolumeHelper:playBtnClickSound()

	self.keysetWindow = KeysetLayer:create()
	self.keysetWindow:initUI()
	self:addChild(self.keysetWindow)
end