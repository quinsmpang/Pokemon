--[[
	Description: Helper class to pop dialog window
	Author: M.Wan
	Date: 06/16/2014
]]

class("DialogWindow", psModalLayer)

DialogWindow.window = nil		--窗口
DialogWindow.textLabel = nil		--消息
DialogWindow.btnOK = nil
DialogWindow.btnCancel = nil

DialogWindow.okScript = nil		--确认按钮回调
DialogWindow.cancelScript = nil	--取消按钮回调

DialogWindow.enableClick = nil

function DialogWindow:createOne()
	local screenSize = cc.Director:getInstance():getWinSize()

	local dialog = DialogWindow:create()

	dialog:setOpacity(0)
	dialog.enableClick = false

	dialog.window = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", CCRectMake(20, 20, 60, 60))
	dialog.window:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

	dialog:addChild(dialog.window)

	dialog.textLabel = cc.Label:createWithTTF("", GameConst.DEFAULT_FONT_PATH, 18)
	dialog.textLabel:setColor(ccc3(0, 0, 0))
	dialog.textLabel:setHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER)
	dialog.textLabel:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
	dialog.window:addChild(dialog.textLabel)

	local okLabel = cc.Label:createWithTTF("确定", GameConst.DEFAULT_FONT_PATH, 20)
	okLabel:setColor(COLOR3B_BLACK)
	local whiteBack = cc.Scale9Sprite:createWithSpriteFrameName("images/common/white_back.png", CCRectMake(1, 1, 1, 1))
	dialog.btnOK = cc.ControlButton:create(okLabel, whiteBack)
	dialog.btnOK:setColor(ccc3(0, 0, 0))
	dialog.btnOK:registerControlEventHandler(MakeScriptHandler(dialog, dialog.onBtnOKClick), cc.Handler.CONTROL_TOUCH_UP_INSIDE)
	dialog.window:addChild(dialog.btnOK)

	local cancelLabel = cc.Label:createWithTTF("取消", GameConst.DEFAULT_FONT_PATH, 20)
	cancelLabel:setColor(COLOR3B_BLACK)
	whiteBack = cc.Scale9Sprite:createWithSpriteFrameName("images/common/white_back.png", CCRectMake(1, 1, 1, 1))
	dialog.btnCancel = cc.ControlButton:create(cancelLabel, whiteBack)
	dialog.btnCancel:setColor(ccc3(0, 0, 0))
	dialog.btnCancel:registerControlEventHandler(MakeScriptHandler(dialog, dialog.onBtnCancelClick), cc.Handler.CONTROL_TOUCH_UP_INSIDE)
	dialog.window:addChild(dialog.btnCancel)

	return dialog
end

function DialogWindow:onComeIn()
	local enterAction = cc.Sequence:create(
		cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
		cc.ScaleTo:create(0.03, 1),
		cc.CallFunc:create(MakeScriptHandler(self, self.onComeInEnd))
		)

	self.window:runAction(enterAction)
end
function DialogWindow:onComeInEnd()
	self.enableClick = true
end

function DialogWindow:onGoOut()
end

function DialogWindow:onBtnOKClick()
	if not self.enableClick then
		return
	end

	log("DialogWindow:onBtnOKClick")
	if self.okScript then
		self.okScript()
	end
	local quitAction = cc.Sequence:create(
		cc.EaseOut:create(cc.ScaleTo:create(0.15, 0), 2),
		cc.TargetedAction:create(self, cc.RemoveSelf:create())
		)

	self.window:runAction(quitAction)
end

function DialogWindow:onBtnCancelClick()
	if not self.enableClick then
		return
	end
	
	log("DialogWindow:onBtnCancelClick")
	if self.cancelScript then
		self.cancelScript()
	end
	local quitAction = cc.Sequence:create(
		cc.EaseOut:create(cc.ScaleTo:create(0.15, 0), 2),
		cc.TargetedAction:create(self, cc.RemoveSelf:create())
		)

	self.window:runAction(quitAction)
end

-- helper class
DialogPopHelper = {}

DialogPopHelper.DEFAULT_WINDOW_SIZE = CCSizeMake(300, 200)
DialogPopHelper.DEFAULT_LABEL_DIMENSIONS = CCSizeMake(250, 120)

function DialogPopHelper:quickPop(content, okScript, cancelScript)
	local dialog = DialogWindow:createOne()
	dialog.window:setPreferredSize(self.DEFAULT_WINDOW_SIZE)
	local winSize = self.DEFAULT_WINDOW_SIZE
	dialog.textLabel:setString(content)
	dialog.textLabel:setDimensions(self.DEFAULT_LABEL_DIMENSIONS.width, self.DEFAULT_LABEL_DIMENSIONS.height)
	dialog.textLabel:setPosition(winSize.width * 0.5, 40 + 80)
	dialog.btnOK:setPosition(winSize.width * 0.3, 40)
	dialog.btnCancel:setPosition(winSize.width * 0.7, 40)

	cc.Director:getInstance():getRunningScene():addChild(dialog)
end

function DialogPopHelper:popQuestionWindow(windowSize, content, okScript, cancelScript)
	local dialog = DialogWindow:createOne()
	dialog.window:setPreferredSize(windowSize)
	dialog.textLabel:setString(content)
	dialog.textLabel:setDimensions(windowSize.width - 50, windowSize.height - 80)
	dialog.textLabel:setPosition(windowSize.width * 0.5, 40 + (windowSize.height - 40) * 0.5)
	dialog.btnOK:setPosition(windowSize.width * 0.3, 40)
	dialog.btnCancel:setPosition(windowSize.width * 0.7, 40)

	cc.Director:getInstance():getRunningScene():addChild(dialog)
end

function DialogPopHelper:popMessageWindow(windowSize, content, okScript)
	local dialog = DialogWindow:createOne()
	dialog.window:setPreferredSize(windowSize)
	dialog.textLabel:setString(content)
	dialog.textLabel:setDimensions(windowSize.width - 50, windowSize.height - 80)
	dialog.textLabel:setPosition(windowSize.width * 0.5, 40 + (windowSize.height - 40) * 0.5)
	dialog.btnOK:setPosition(windowSize.width * 0.5, 40)
	dialog.btnCancel:setVisible(false)

	cc.Director:getInstance():getRunningScene():addChild(dialog)
end