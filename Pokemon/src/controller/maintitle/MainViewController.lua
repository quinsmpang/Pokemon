--[[
	Description: MainViewController
	Author: M.Wan
	Date: 05/03/2014
]]

require "src/view/maintitle/MainMenu"

class("MainViewController", psViewController)

MainViewController.resources = {
	"images/maintitle.plist",
	"images/maintitle.pvr.ccz",
}

MainViewController.infoLabel = nil		-- 游戏说明文字
MainViewController.mainView = nil		-- 主界面view (ccb)
MainViewController.mainMenuView = nil 		-- 主菜单view

MainViewController.isRunningAction = nil
MainViewController.state = nil 		--当前的状态 (主界面/菜单界面)

-- const values
MainViewController.GAME_INFO_TEXT = "本作仅供学习交流  请勿用于商业用途\n源码已在GitHub上托管"
MainViewController.TITLE_MUSIC = "audio/scene/title.mp3"
MainViewController.STATE_MAINVIEW = 1
MainViewController.STATE_MAINMENU = 2

MainViewController.TAG = {
	TOUCHLABEL = 1,
}

function MainViewController:load()
	log("MainViewController:load")
	self:loadResources()
	self:renderView()
end

function MainViewController:unload()
	log("MainViewController:unload")
	self:cleanResources()
end

function MainViewController:loadResources()
	log("MainViewController:loadResources")
	cc.SimpleAudioEngine:getInstance():preloadMusic(self.TITLE_MUSIC)
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():addSpriteFrames(self.resources[i], self.resources[i + 1])
	end
end

function MainViewController:cleanResources()
	log("MainViewController:cleanResources")
	for i = 1, #self.resources, 2 do
		cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile(self.resources[i])
	end
	--cc.SpriteFrameCache:getInstance():removeSpriteFramesFromTexture("images/maintitle.pvr.ccz")
end

function MainViewController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	-- info text
	local gameInfoText = cc.Label:createWithTTF(self.GAME_INFO_TEXT, GameConst.DEFAULT_FONT_PATH, 24)
	gameInfoText:setAnchorPoint(0.5, 0.5)
	gameInfoText:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
	-- label bug, you have to cascade opacity first and then set opacity.
	gameInfoText:setCascadeOpacityEnabled(true)
	gameInfoText:setOpacity(0)
	coreLayer:addChild(gameInfoText)

	self.infoLabel = gameInfoText

	-- main view
	local ccbMainView = ScriptCCBReader:readCCB("ccb/MainTitle.ccbi", self)
	ccbMainView:setAnchorPoint(0, 0)
	ccbMainView:setPosition(0, 0)
	-- set cascade opacity, otherwise the opacity property of parent node won't affect the opacity of children.
	ccbMainView:setCascadeOpacityEnabled(true)
	ccbMainView:setOpacity(0)
	self.mainView = ccbMainView
	tolua.cast(self.mainView, "cc.Layer")
	coreLayer:addChild(ccbMainView)

	self.touchLabel = ccbMainView:getChildByTag(self.TAG.TOUCHLABEL)
	tolua.cast(self.touchLabel, "cc.Label")
	self.touchLabel:setSystemFontName("Consolas")

	-- main menu view
	self.mainMenuView = MainMenu:create()
	self.mainMenuView:initUI()

	coreLayer:addChild(self.mainMenuView)

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
		cc.CallFunc:create(MakeScriptHandler(self, self.playBackgroundMusic)),
		cc.FadeIn:create(0.5),
		cc.CallFunc:create(MakeScriptHandler(self, self.registerMainViewEvents)),
		cc.CallFunc:create(MakeScriptHandler(self, self.runTouchLabelAction))
		))
end
function MainViewController:playBackgroundMusic()
	cc.SimpleAudioEngine:getInstance():playMusic(self.TITLE_MUSIC, true)
end
function MainViewController:runTouchLabelAction()
	self.touchLabel:runAction(cc.RepeatForever:create(
		cc.Sequence:create(
			cc.FadeOut:create(0.5),
			cc.FadeIn:create(0.5)
			)
		))
end
function MainViewController:registerMainViewEvents()
	-- change state
	self.state = self.STATE_MAINVIEW

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(MakeScriptHandler(self, self.onMainViewTouch), cc.Handler.EVENT_TOUCH_BEGAN)

	self.mainView:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self.mainView)
end

function MainViewController:onMainViewTouch(touch, event)
	if self.isRunningAction then
		return true
	end

	log("MainViewController:onMainViewTouch")

	self:readyToEnterMainMenu()

	return true
end

function MainViewController:readyToEnterMainMenu()
	self.isRunningAction = true

	--cc.SimpleAudioEngine:getInstance():stopMusic(true)
	cc.SimpleAudioEngine:getInstance():playEffect("audio/pm/493.wav")

	self.mainView:runAction(cc.Sequence:create(
		cc.FadeOut:create(0.5),
		cc.CallFunc:create(MakeScriptHandler(self, self.enterMainMenu))
		))

	-- check if there is save directory
	if not IOUtils:getInstance():fileOrDirectoryExist("save") then
		--IOUtils:getInstance():createDirectory("save")
	end
end

function MainViewController:enterMainMenu()
	--change state
	self.state = self.STATE_MAINMENU

	self.mainView:removeFromParent()

	-- load main menu
	self.mainMenuView:runAction(cc.Sequence:create(
		cc.DelayTime:create(0.5),
		cc.CallFunc:create(MakeScriptHandler(self.mainMenuView, self.mainMenuView.showButtons)),
		cc.FadeIn:create(0.5),
		cc.CallFunc:create(MakeScriptHandler(self, self.runActionOver))
		))
end
function MainViewController:runActionOver()
	self.isRunningAction = false
end