--[[
	Description: dialogue layer controller
	Author: M.Wan
	Date: 06/07/2014
]]

class("DialogLayerController", psViewController)

DialogLayerController.root = nil		-- root layer(pf.GameLayer)
DialogLayerController.dialogWindow = nil	-- dialog window
DialogLayerController.dialogLabel = nil		-- dialog text
DialogLayerController.dialogIndice = nil	-- indice for continuing talking

-- logic 
DialogLayerController.currentDialogId = nil		-- current dialog id
DialogLayerController.enableClick = nil			-- whether can player operate

-- const values
DialogLayerController.DIALOG_WINDOW_SIZE = CCSizeMake(780, 100)
DialogLayerController.DIALOG_WINDOW_POSITION = ccp(400, 50)
DialogLayerController.DIALOG_TEXT_FONT_SIZE = 18
DialogLayerController.DIALOG_TEXT_DIMENSION = CCSizeMake(700, 60)
DialogLayerController.DIALOG_TEXT_POSITION = ccp(60, 80)
DialogLayerController.DIALOG_TEXT_COLOR = ccc3(0, 0, 0)
DialogLayerController.DIALOG_INDICE_POSITION = ccp(750, 10)

function DialogLayerController:load()
	log("DialogLayerController:load")
	self:loadResources()
	self:renderView()
end

function DialogLayerController:unload()
	log("DialogLayerController:unload")
	self:cleanResources()
end

function DialogLayerController:loadResources()
	log("DialogLayerController:loadResources")
	cc.SpriteFrameCache:getInstance():addSpriteFrames("images/common.plist", "images/common.pvr.ccz")
	cc.SpriteFrameCache:getInstance():addSpriteFrames("images/dialog.plist", "images/dialog.pvr.ccz")
end

function DialogLayerController:cleanResources()
	log("DialogLayerController:cleanResources")
	cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile("images/common.plist")
	cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile("images/dialog.plist")
end

function DialogLayerController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()

	self.root = psGameLayer:create()
	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(MakeScriptHandler(self, self.generateNextDialog), cc.Handler.EVENT_TOUCH_BEGAN)
	self.root:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self.root)

	-- dialog window initialization
	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/maintitle/border_orange.png", capInsets)
	dialogWindow:setPreferredSize(self.DIALOG_WINDOW_SIZE)
	dialogWindow:setPosition(self.DIALOG_WINDOW_POSITION)

	self.dialogWindow = dialogWindow
	self.root:addChild(dialogWindow)

	-- dialog label initialization
	local dialogLabel = cc.Label:createWithTTF("", GameConst.DEFAULT_FONT_PATH, self.DIALOG_TEXT_FONT_SIZE, self.DIALOG_TEXT_DIMENSION)
	dialogLabel:setAnchorPoint(ccp(0, 1))
	dialogLabel:setPosition(self.DIALOG_TEXT_POSITION)
	dialogLabel:setColor(self.DIALOG_TEXT_COLOR)

	self.dialogLabel = dialogLabel
	self.root:addChild(dialogLabel)

	-- dialog indice
	local dialogIndice = cc.Sprite:createWithSpriteFrameName("images/dialog/dialog_indice.png")
	dialogIndice:setAnchorPoint(ccp(0, 0))
	dialogIndice:setPosition(self.DIALOG_INDICE_POSITION)
	dialogIndice:setVisible(false)
	-- run blink action
	local indiceAction = cc.Sequence:create(
			cc.FadeOut:create(0.2),
			cc.FadeIn:create(0.2)
		)
	dialogIndice:runAction(cc.RepeatForever:create(indiceAction))

	self.dialogIndice = dialogIndice
	self.root:addChild(dialogIndice)

	coreLayer:pushLayer(self.root)

	self.enableClick = false
	self.currentDialogId = 0

	self:generateNextDialog()
end

function DialogLayerController:generateNextDialog()
	log("DialogLayerController:generateNextDialog")
	log("current dialog id: " .. self.currentDialogId)
	self.enableClick = false
	self.currentDialogId = self.currentDialogId + 1
	local currentDialog = GameDBHelper:queryDialogById(self.currentDialogId)

	self:showTextOneByOne(currentDialog.dialog)
end

function DialogLayerController:showTextOneByOne(text)
	self.dialogLabel:setString(text)
	self.dialogIndice:setVisible(true)
	self.enableClick = true
end