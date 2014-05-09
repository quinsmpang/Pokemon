--[[
	Description: MainViewController
	Author: M.Wan
	Date: 05/03/2014
]]

class("MainViewController", psViewController)

MainViewController.infoLabel = nil		-- 游戏说明文字
MainViewController.mainLayer = nil		-- 游戏主界面层
MainViewController.mainView = nil		-- ccb主界面层
MainViewController.mainMenu = nil		-- 游戏主菜单

-- const values
MainViewController.GAME_INFO_TEXT = "本作仅供学习交流  请勿用于商业用途\n源码已在GitHub上托管"
MainViewController.GAME_TOUCH_TEXT = "Touch Anywhere To Start"

TAG = {
	TOUCHLABEL = 1,
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

	local ccbMainView = ScriptCCBReader:readCCB("ccb/MainTitle.ccbi", self)
	ccbMainView:setScale(2)
	ccbMainView:setAnchorPoint(0, 0)
	ccbMainView:setPosition(0, 0)
	-- set cascade opacity, otherwise the opacity property of parent node won't affect the opacity of children.
	ccbMainView:setCascadeOpacityEnabled(true)
	ccbMainView:setOpacity(0)
	self.mainView = ccbMainView
	tolua.cast(self.mainView, "cc.Layer")
	self.mainLayer:addChild(ccbMainView)

	self.touchLabel = ccbMainView:getChildByTag(TAG.TOUCHLABEL)
	self.touchLabel:setSystemFontName("Consolas")
	tolua.cast(self.touchLabel, "cc.Label")

	self:run()
end

function MainViewController:run()
	self.infoLabel:runAction(cc.Sequence:create(
		cc.DelayTime:create(1),
		cc.FadeIn:create(0.5),
		cc.DelayTime:create(2),
		cc.TargetedAction:create(self.infoLabel, cc.FadeOut:create(0.5))
		))
	self.mainView:runAction(cc.Sequence:create(
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