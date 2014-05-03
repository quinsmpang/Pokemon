--[[
	Description: MainViewController
	Author: M.Wan
	Date: 05/03/2014
]]

class("MainViewController", psViewController)

MainViewController.infoLabel = nil		-- 游戏说明文字
MainViewController.mainLayer = nil		-- 游戏主界面层
MainViewController.background = nil		-- 背景
MainViewController.touchLabel = nil		-- touch 文字
MainViewController.mainMenu = nil		-- 游戏主菜单

-- const values
MainViewController.GAME_INFO_TEXT = "本作仅供学习交流  请勿用于商业用途\n源码已在GitHub上托管"
MainViewController.GAME_TOUCH_TEXT = "Touch Anywhere To Start"

function MainViewController:load()
	self:renderView()
end

function MainViewController:unload()
	
end

function MainViewController:renderView()
	local coreLayer = psCoreLayer:create()

	local mainViewScene = self:getScene()
	mainViewScene:setCoreLayer(coreLayer)

	local screenSize = cc.Director:getInstance():getWinSize()

	-- info text
	local gameInfoText = cc.LabelTTF:create(self.GAME_INFO_TEXT, "Consolas", 24)
	gameInfoText:setAnchorPoint(0.5, 0.5)
	gameInfoText:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	gameInfoText:setVisible(false)
	coreLayer:addChild(gameInfoText)

	self.infoLabel = gameInfoText

	-- main layer
	self.mainLayer = psGameLayer:create()
	self.mainLayer:setVisible(false)
	coreLayer:addChild(self.mainLayer)

	-- background
	local back = cc.Sprite:create("images/maintitle/title.jpg")
	back:setAnchorPoint(0.5, 0.5)
	back:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	self.mainLayer:addChild(back)

	self.background = back

	-- touch text
	local touchText = cc.LabelTTF:create(self.GAME_TOUCH_TEXT, "Consolas", 20)
	touchText:setAnchorPoint(0.5, 0.5)
	touchText:setPosition(screenSize.width * 0.5, screenSize.height * 0.3)
	touchText:setColor(ccc3(0, 0, 0))
	self.mainLayer:addChild(touchText)

	self.touchLabel = touchText

	self:run()
end

function MainViewController:run()
	self.infoLabel:runAction(cc.Sequence:create(
		cc.DelayTime:create(1),
		cc.FadeOut:create(0),
		cc.Spawn:create(
			cc.FadeIn:create(0.5),
			cc.CallFunc:create(MakeScriptHandler(self, self.showNode, self.infoLabel))
			),
		cc.DelayTime:create(2),
		cc.FadeOut:create(0.5),
		cc.RemoveSelf:create(true)
		))
	self.mainLayer:runAction(cc.Sequence:create(
		cc.DelayTime:create(4.5),
		cc.FadeOut:create(0),
		cc.Spawn:create(
			cc.TargetedAction:create(self.background, cc.FadeIn:create(0.5)),
			cc.TargetedAction:create(self.touchLabel, cc.FadeIn:create(0.5)),
			cc.CallFunc:create(MakeScriptHandler(self, self.showNode, self.mainLayer))
			),
		cc.CallFunc:create(MakeScriptHandler(self, self.runTouchLabelActoin))
		))
end
function MainViewController:showNode(node)
	node:setVisible(true)
end
function MainViewController:runTouchLabelActoin()
	self.touchLabel:runAction(cc.RepeatForever:create(
		cc.Sequence:create(
			cc.FadeOut:create(0.5),
			cc.FadeIn:create(0.5)
			)
		))
end