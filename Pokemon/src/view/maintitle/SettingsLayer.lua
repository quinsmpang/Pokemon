--[[
	Description: Settings Window
	Author: M.Wan
	Date: 05/20/2014
]]

class("SettingsLayer", psModalLayer)

SettingsLayer.window = nil			--背景窗口
SettingsLayer.musicSlider = nil 	--音乐音量Slider
SettingsLayer.effectSlider = nil	--音效音量Slider
SettingsLayer.enableClick = nil		--是否可以响应事件

--const
SettingsLayer.SLIDER_TRACK_PATH = "images/maintitle/slider_fill.png"
SettingsLayer.SLIDER_PROGRESS_PATH = "images/maintitle/slider_none.png"
SettingsLayer.SLIDER_THUMB_PATH = "images/maintitle/slider_thumb.png"

function SettingsLayer:initUI()
	log("SettingsLayer:initUI")

	local screenSize = cc.Director:getInstance():getWinSize()

	-- init window
	self.window = cc.Sprite:createWithSpriteFrameName("images/maintitle/window.png")
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
	self.musicSlider:setMaximumValue(100)
	self.musicSlider:setValue(GameSettings.musicVolume * 100)
	self.musicSlider:registerControlEventHandler(MakeScriptHandler(self, self.onMusicSliderValueChanged), 256)
	self.window:addChild(self.musicSlider)

	sliderTrack = cc.Sprite:createWithSpriteFrameName(self.SLIDER_TRACK_PATH)
	sliderProgress = cc.Sprite:createWithSpriteFrameName(self.SLIDER_PROGRESS_PATH)
	sliderThumb = cc.Sprite:createWithSpriteFrameName(self.SLIDER_THUMB_PATH)
	self.effectSlider = cc.ControlSlider:create(sliderProgress, sliderTrack, sliderThumb)
	self.effectSlider:setAnchorPoint(0.5, 0.5)
	self.effectSlider:setPosition(windowSize.width * 0.55, windowSize.height * 0.45)
	self.effectSlider:setMinimumValue(0)
	self.effectSlider:setMaximumValue(100)
	self.effectSlider:setValue(GameSettings.effectVolume * 100)
	self.window:addChild(self.effectSlider)

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
	GameSettings:saveSettings()
end

function SettingsLayer:onMusicSliderValueChanged()
	log("SettingsLayer:onMusicSliderValueChanged")
	local currentValue = self.musicSlider:getValue()
	cc.SimpleAudioEngine:getInstance():setMusicVolume(currentValue)
end
function SettingsLayer:onEffectSliderValueChanged()
	log("onEffectSliderValueChanged")
	local currentValue = self.effectSlider:getValue()
	cc.SimpleAudioEngine:getInstance():setEffectVolumn(currentValue)
end