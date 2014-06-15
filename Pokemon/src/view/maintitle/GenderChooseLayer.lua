--[[
	Description: The window to choose gender
	Author: M.Wan
	Date: 06/16/2014
]]

class("GenderChooseLayer", psModalLayer)

GenderChooseLayer.window = nil		--背景窗口
GenderChooseLayer.maleSprite = nil		--男性精灵
GenderChooseLayer.femaleSprite = nil	--女性精灵

GenderChooseLayer.enableClick = nil

GenderChooseLayer.TAG = {
	SPRITE_MALE = 1,
	SPRITE_FEMALE = 2,
}

function GenderChooseLayer:initUI()
	log("GenderChooseLayer:initUI")
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