--[[
	Description: MainViewController
	Author: M.Wan
	Date: 05/03/2014
]]

class("MainViewController", psViewController)

MainViewController.infoLabel = nil		-- 游戏说明文字
MainViewController.mainLayer = nil		-- 游戏主界面层
MainViewController.mainMenu = nil		-- 游戏主菜单

-- const values
MainViewController.GAME_INFO_TEXT = "本作仅供学习交流  请勿用于商业用途\n源码已在GitHub上托管"
MainViewController.GAME_TOUCH_TEXT = "Touch Anywhere To Start"

TAG = {
	MAINVIEW = 1,
		TOUCHLABEL = 11,
}

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
	local gameInfoText = cc.Label:createWithSystemFont(self.GAME_INFO_TEXT, "Consolas", 24)
	gameInfoText:setAnchorPoint(0.5, 0.5)
	gameInfoText:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	-- label bug, you have to cascade opacity first and then set opacity.
	gameInfoText:setCascadeOpacityEnabled(true)
	gameInfoText:setOpacity(0)
	coreLayer:addChild(gameInfoText)

	self.infoLabel = gameInfoText

	-- main layer
	self.mainLayer = psGameLayer:create()
	coreLayer:pushLayer(self.mainLayer)

	-- background
	local back = cc.Sprite:create("images/maintitle/back.jpg")
	back:setAnchorPoint(0.5, 0.5)
	back:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	self.mainLayer:addChild(back)

	-- touch text
	local touchText = cc.Label:createWithSystemFont(self.GAME_TOUCH_TEXT, "Consolas", 20)
	touchText:setAnchorPoint(0.5, 0.5)
	touchText:setPosition(screenSize.width * 0.5, screenSize.height * 0.3)
	touchText:setColor(ccc3(0, 0, 0))
	self.mainLayer:addChild(touchText)

	self.touchLabel = touchText

	-- set cascade opacity, otherwise the opacity property of parent node won't affect the opacity of children.
	self.mainLayer:setCascadeOpacityEnabled(true)
	self.mainLayer:setOpacity(0)

	self:run()
end

function MainViewController:run()
	self.infoLabel:runAction(cc.Sequence:create(
		cc.DelayTime:create(1),
		cc.FadeIn:create(0.5),
		cc.DelayTime:create(2),
		cc.TargetedAction:create(self.infoLabel, cc.FadeOut:create(0.5))
		))
	self.mainLayer:runAction(cc.Sequence:create(
		cc.DelayTime:create(4.5),
		cc.FadeIn:create(0.5),
		cc.CallFunc:create(MakeScriptHandler(self, self.registerMainLayerEvents)),
		cc.CallFunc:create(MakeScriptHandler(self, self.runTouchLabelAction))
		))
end
function MainViewController:runTouchLabelAction()
	self.touchLabel:runAction(cc.RepeatForever:create(
		cc.Sequence:create(
			cc.FadeOut:create(0.5),
			cc.FadeIn:create(0.5)
			)
		))
end
function MainViewController:registerMainLayerEvents()
	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(MakeScriptHandler(self, self.onMainViewTouch), cc.Handler.EVENT_TOUCH_BEGAN)

	self.mainLayer:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self.mainLayer)
end

function MainViewController:onMainViewTouch(touch, event)
	log("touched")
end