--[[
	Description: Helper class to pop dialog window
	Author: M.Wan
	Date: 06/16/2014
]]

class("DialogWindow", psModalLayer)

DialogWindow.window = nil		--窗口
DialogWindow.textLabel = nil		--消息
DialogWindow.menu = nil
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

	dialog.textLabel = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, 18)
	dialog.textLabel:setColor(ccc3(0, 0, 0))
	dialog.textLabel:setHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER)
	dialog.textLabel:setVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
	dialog.window:addChild(dialog.textLabel)

	self.menu = cc.Menu:create()

	local okLabel = cc.Label:createWithTTF("确定", GameConfig.DEFAULT_FONT_PATH, 20)
	local okLabel2 = cc.Label:createWithTTF("确定", GameConfig.DEFAULT_FONT_PATH, 21)
	okLabel:setColor(COLOR3B_BLACK)
	okLabel2:setColor(COLOR3B_BLACK)
	dialog.btnOK = cc.MenuItemSprite:create(okLabel, okLabel2)
	dialog.btnOK:registerScriptTapHandler(MakeScriptHandler(dialog, dialog.onBtnOKClick))
	self.menu:addChild(dialog.btnOK)

	local cancelLabel = cc.Label:createWithTTF("取消", GameConfig.DEFAULT_FONT_PATH, 20)
	local cancelLabel2 = cc.Label:createWithTTF("取消", GameConfig.DEFAULT_FONT_PATH, 21)
	cancelLabel:setColor(COLOR3B_BLACK)
	cancelLabel2:setColor(COLOR3B_BLACK)
	dialog.btnCancel = cc.MenuItemSprite:create(cancelLabel, cancelLabel2)
	dialog.btnCancel:registerScriptTapHandler(MakeScriptHandler(dialog, dialog.onBtnCancelClick))
	self.menu:addChild(dialog.btnCancel)

	dialog.window:addChild(self.menu)

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
	dialog.btnOK:setPosition(-winSize.width * 0.2, -(winSize.height * 0.5 - 40))
	dialog.btnCancel:setPosition(winSize.width * 0.2, -(winSize.height * 0.5 - 40))
	dialog.menu:setPosition(winSize.width * 0.5, winSize.height * 0.5)

	dialog.okScript = okScript
	dialog.cancelScript = cancelScript

	cc.Director:getInstance():getRunningScene():addChild(dialog)
end

function DialogPopHelper:popQuestionWindow(windowSize, content, okScript, cancelScript)
	local dialog = DialogWindow:createOne()
	dialog.window:setPreferredSize(windowSize)
	dialog.textLabel:setString(content)
	dialog.textLabel:setDimensions(windowSize.width - 50, windowSize.height - 80)
	dialog.textLabel:setPosition(windowSize.width * 0.5, 40 + (windowSize.height - 40) * 0.5)
	dialog.btnOK:setPosition(-windowSize.width * 0.2, -(windowSize.height * 0.5 - 40))
	dialog.btnCancel:setPosition(windowSize.width * 0.2, -(windowSize.height * 0.5 - 40))
	dialog.menu:setPosition(windowSize.width * 0.5, windowSize.height * 0.5)

	dialog.okScript = okScript
	dialog.cancelScript = cancelScript

	cc.Director:getInstance():getRunningScene():addChild(dialog)
end

function DialogPopHelper:popMessageWindow(windowSize, content, okScript)
	local dialog = DialogWindow:createOne()
	dialog.window:setPreferredSize(windowSize)
	dialog.textLabel:setString(content)
	dialog.textLabel:setDimensions(windowSize.width - 50, windowSize.height - 80)
	dialog.textLabel:setPosition(windowSize.width * 0.5, 40 + (windowSize.height - 40) * 0.5)
	dialog.btnOK:setPosition(-windowSize.width * 0.5, -(windowSize.height * 0.5 - 40))
	dialog.btnCancel:setVisible(false)
	dialog.menu:setPosition(windowSize.width * 0.5, windowSize.height * 0.5)

	dialog.okScript = okScript

	cc.Director:getInstance():getRunningScene():addChild(dialog)
end