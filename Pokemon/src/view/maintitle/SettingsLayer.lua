--[[
	Description: Settings Window
	Author: M.Wan
	Date: 05/20/2014
]]

class("SettingsLayer", psModalLayer)

SettingsLayer.window = nil			--背景窗口
SettingsLayer.musicSlider = nil 	--音乐音量Slider
SettingsLayer.effectSlider = nil	--音效音量Slider
SettingsLayer.btnDefault = nil		--恢复默认按钮
SettingsLayer.btnClose = nil		--关闭按钮

SettingsLayer.enableClick = nil		--是否可以响应事件

--const
SettingsLayer.SLIDER_TRACK_PATH = "images/maintitle/slider_fill.png"
SettingsLayer.SLIDER_PROGRESS_PATH = "images/maintitle/slider_none.png"
SettingsLayer.SLIDER_THUMB_PATH = "images/maintitle/slider_thumb.png"

function SettingsLayer:initUI()
	log("SettingsLayer:initUI")

	local screenSize = cc.Director:getInstance():getWinSize()

	-- init window
	self.window = cc.Sprite:createWithSpriteFrameName("images/maintitle/setting_window.png")
	self.window:setAnchorPoint(0.5, 0.5)
	self.window:setPosition(screenSize.width * 0.5, screenSize.height * 0.6)
	self:addChild(self.window)

	local windowSize = self.window:getContentSize()

	-- init sliders
	local sliderTrack = cc.Sprite:createWithSpriteFrameName(self.SLIDER_TRACK_PATH)
	local sliderProgress = cc.Sprite:createWithSpriteFrameName(self.SLIDER_PROGRESS_PATH)
	local sliderThumb = cc.Sprite:createWithSpriteFrameName(self.SLIDER_THUMB_PATH)
	self.musicSlider = cc.ControlSlider:create(sliderProgress, sliderTrack, sliderThumb)
	self.musicSlider:setAnchorPoint(0.5, 0.5)
	self.musicSlider:setPosition(windowSize.width * 0.55, windowSize.height * 0.6)
	self.musicSlider:setMinimumValue(0)
	self.musicSlider:setMaximumValue(1)
	self.musicSlider:setValue(GameSettings.musicVolume)
	self.musicSlider:registerControlEventHandler(MakeScriptHandler(self, self.onMusicSliderValueChanged), cc.Handler.CONTROL_VALUE_CHANGED)
	self.window:addChild(self.musicSlider)

	sliderTrack = cc.Sprite:createWithSpriteFrameName(self.SLIDER_TRACK_PATH)
	sliderProgress = cc.Sprite:createWithSpriteFrameName(self.SLIDER_PROGRESS_PATH)
	sliderThumb = cc.Sprite:createWithSpriteFrameName(self.SLIDER_THUMB_PATH)
	self.effectSlider = cc.ControlSlider:create(sliderProgress, sliderTrack, sliderThumb)
	self.effectSlider:setAnchorPoint(0.5, 0.5)
	self.effectSlider:setPosition(windowSize.width * 0.55, windowSize.height * 0.45)
	self.effectSlider:setMinimumValue(0)
	self.effectSlider:setMaximumValue(1)
	self.effectSlider:setValue(GameSettings.effectVolume)
	self.effectSlider:registerControlEventHandler(MakeScriptHandler(self, self.onEffectSliderValueChanged), cc.Handler.CONTROL_VALUE_CHANGED)
	self.window:addChild(self.effectSlider)

	-- labels
	local musicLabel = cc.Label:createWithTTF("音乐", GameConfig.DEFAULT_FONT_PATH, 20)
	musicLabel:setColor(ccc3(255, 255, 255))
	musicLabel:setAnchorPoint(0.5, 0.5)
	musicLabel:setPosition(windowSize.width * 0.25, windowSize.height * 0.6)
	self.window:addChild(musicLabel)

	local effectLabel = cc.Label:createWithTTF("音效", GameConfig.DEFAULT_FONT_PATH, 20)
	effectLabel:setColor(ccc3(255, 255, 255))
	effectLabel:setAnchorPoint(0.5, 0.5)
	effectLabel:setPosition(windowSize.width * 0.25, windowSize.height * 0.45)
	self.window:addChild(effectLabel)

	-- buttons
	local btnDefaultLabel = cc.Label:createWithTTF("默认", GameConfig.DEFAULT_FONT_PATH, 22)
	local btnBack = cc.Scale9Sprite:createWithSpriteFrameName("images/common/black_back.png", CCRectMake(1, 1, 1, 1))
	self.btnDefault = cc.ControlButton:create(btnDefaultLabel, btnBack)
	self.btnDefault:setAnchorPoint(0.5, 0.5)
	self.btnDefault:setPosition(windowSize.width * 0.35, windowSize.height * 0.28)
	self.btnDefault:registerControlEventHandler(MakeScriptHandler(self, self.onBtnDefaultClick), cc.Handler.CONTROL_TOUCH_UP_INSIDE)
	self.window:addChild(self.btnDefault)

	local btnCloseLabel = cc.Label:createWithTTF("关闭", GameConfig.DEFAULT_FONT_PATH, 22)
	btnBack = cc.Scale9Sprite:createWithSpriteFrameName("images/common/black_back.png", CCRectMake(1, 1, 1, 1))
	self.btnClose = cc.ControlButton:create(btnCloseLabel, btnBack)
	self.btnClose:setAnchorPoint(0.5, 0.5)
	self.btnClose:setPosition(windowSize.width * 0.65, windowSize.height * 0.28)
	self.btnClose:registerControlEventHandler(MakeScriptHandler(self, self.onBtnCloseClick), cc.Handler.CONTROL_TOUCH_UP_INSIDE)
	self.window:addChild(self.btnClose)

	self.window:setScale(0)
	self.enableClick = false
end

function SettingsLayer:onComeIn()
	local enterAction = cc.Sequence:create(
		cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
		cc.ScaleTo:create(0.03, 1),
		cc.CallFunc:create(MakeScriptHandler(self, self.onComeInEnd))
		)

	self.window:runAction(enterAction)
end
function SettingsLayer:onComeInEnd()
	self.enableClick = true
end

function SettingsLayer:onGoOut()
end

function SettingsLayer:onMusicSliderValueChanged()
	if not self.enableClick then
		return
	end
	log("SettingsLayer:onMusicSliderValueChanged")
	local currentValue = self.musicSlider:getValue()
	cc.SimpleAudioEngine:getInstance():setMusicVolume(currentValue)
end
function SettingsLayer:onEffectSliderValueChanged()
	if not self.enableClick then
		return
	end
	log("SettingsLayer:onEffectSliderValueChanged")
	local currentValue = self.effectSlider:getValue()
	cc.SimpleAudioEngine:getInstance():setEffectsVolume(currentValue)
end

function SettingsLayer:onBtnDefaultClick()
	if not self.enableClick then
		return
	end
	log("SettingsLayer:onBtnDefaultClick")

	GameVolumeHelper:playBtnClickSound()

	self.musicSlider:setValue(0.5)
	self.effectSlider:setValue(0.5)
	cc.SimpleAudioEngine:getInstance():setMusicVolume(0.5)
	cc.SimpleAudioEngine:getInstance():setEffectsVolume(0.5)
end
function SettingsLayer:onBtnCloseClick()
	if not self.enableClick then
		return
	end
	log("SettingsLayer:onBtnCloseClick")

	GameVolumeHelper:playBtnClickSound()
	
	GameSettings.musicVolume = self.musicSlider:getValue()
	GameSettings.effectVolume = self.effectSlider:getValue()
	GameSettings:saveSettings()
	self.enableClick = false
	local quitAction = cc.Sequence:create(
		cc.EaseOut:create(cc.ScaleTo:create(0.15, 0), 2),
		cc.TargetedAction:create(self, cc.RemoveSelf:create())
		)

	self.window:runAction(quitAction)
end