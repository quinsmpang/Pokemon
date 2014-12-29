--[[
	Description: The window to choose gender
	Author: M.Wan
	Date: 06/16/2014
]]

class("GenderChooseLayer", psModalLayer)

require "src/scene/map/MapViewScene"

GenderChooseLayer.window = nil		--背景窗口
GenderChooseLayer.maleSprite = nil		--男性精灵
GenderChooseLayer.femaleSprite = nil	--女性精灵

GenderChooseLayer.choice = nil		--最终选择
GenderChooseLayer.enableClick = nil

GenderChooseLayer.TAG = {
	SPRITE_MALE = 1,
	SPRITE_FEMALE = 2,
	TITLE_LABEL = 3,
}

function GenderChooseLayer:initUI()
	log("GenderChooseLayer:initUI")

	self.enableClick = false

	local winSize = cc.Director:getInstance():getWinSize()

	self.window = ScriptCCBReader:readCCB("ccb/GenderChooseLayer.ccbi", self)
	self.window:ignoreAnchorPointForPosition(false)
	self.window:setAnchorPoint(0.5, 0.5)
	self.window:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self.window:setScale(0)
	self:addChild(self.window)

	self.maleSprite = self.window:getChildByTag(self.TAG.SPRITE_MALE)
	self.femaleSprite = self.window:getChildByTag(self.TAG.SPRITE_FEMALE)
end

function GenderChooseLayer:onComeIn()
	local enterAction = cc.Sequence:create(
		cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
		cc.ScaleTo:create(0.03, 1),
		cc.CallFunc:create(MakeScriptHandler(self, self.onComeInEnd))
		)

	self.window:runAction(enterAction)
end
function GenderChooseLayer:onComeInEnd()
	self.enableClick = true
end

function GenderChooseLayer:onGoOut()
end

function GenderChooseLayer:onModalTouchBegan(x, y)
	if not self.enableClick then
		return
	end

	local sprites = { self.maleSprite, self.femaleSprite }
	for i, sprite in ipairs(sprites) do
		if ContainsPoint(sprite:getBoundingBox(), ccp(x, y)) then
			if i == 1 then
				-- male
				log("Choose a male")
				self.choice = Enumerations.GENDER.MALE
				DialogPopHelper:popQuestionWindow(CCSizeMake(200, 150), "您是一名男孩?", MakeScriptHandler(self, self.onChoiceConfirm), MakeScriptHandler(self, self.onChoiceCancel))
			else
				-- female
				log("Choose a female")
				self.choice = Enumerations.GENDER.FEMALE
				DialogPopHelper:popQuestionWindow(CCSizeMake(200, 150), "您是一名女孩?", MakeScriptHandler(self, self.onChoiceConfirm), MakeScriptHandler(self, self.onChoiceCancel))
			end
		end
	end
end

function GenderChooseLayer:onChoiceConfirm()
	log("GenderChooseLayer:onChoiceConfirm")

	local mapScene = MapViewScene:create()
	mapScene:newData(self.choice)
	cc.Director:getInstance():replaceScene(cc.TransitionFade:create(2, mapScene))
end

function GenderChooseLayer:onChoiceCancel()
	log("GenderChooseLayer:onChoiceCancel")
end