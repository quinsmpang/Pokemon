--[[
	Description: New name window
	Author: M.Wan
	Date: 06/11/2014
]]

class("NewNameLayer", psModalLayer)

NewNameLayer.window = nil		--背景窗口
NewNameLayer.txtName = nil		--姓名输入框
NewNameLayer.btnConfirm = nil	--确认按钮

NewNameLayer.enableClick = nil

NewNameLayer.TAG = {
	MENU = 1,
		BTN_CONFIRM = 11,
}

function NewNameLayer:initUI()
	log("NewNameLayer:initUI")

	self.enableClick = false

	self.window = ScriptCCBReader:readCCB("ccb/NewNameLayer.ccbi", self)
	self.window:setPosition(0, 0)
	self.window:setScale(0)
	self:addChild(self.window)

	-- textbox
	self.txtName = ccui.TextField:create("请输入您的名字", GameConfig.DEFAULT_FONT_PATH, 20)
	self.txtName:setMaxLengthEnabled(true)
	self.txtName:setMaxLength(15)
	self.txtName:setColor(ccc3(0, 0, 0))
	self.txtName:setPosition(400, 230)
	self:addChild(self.txtName)

	-- confirm button
	self.btnConfirm = self.window:getChildByTag(self.TAG.MENU):getChildByTag(self.TAG.BTN_CONFIRM)
	self.btnConfirm:registerScriptTapHandler(MakeScriptHandler(self, self.onBtnConfirmClick))
end

function NewNameLayer:onComeIn()
	local enterAction = cc.Sequence:create(
		cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
		cc.ScaleTo:create(0.03, 1),
		cc.CallFunc:create(MakeScriptHandler(self, self.onComeInEnd))
		)

	self.window:runAction(enterAction)
end
function NewNameLayer:onComeInEnd()
	self.enableClick = true
end

function NewNameLayer:onGoOut()
end

function NewNameLayer:onBtnConfirmClick()
	log("NewNameLayer:onBtnConfirmClick")
end