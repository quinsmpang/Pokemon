--[[
	Description: Save game layer
	Author: M.Wan
	Date: 11/23/2014
]]

class("SaveGameLayer", psModalLayer)

SaveGameLayer.list = nil		-- 询问框
SaveGameLayer.timeLabel = nil
SaveGameLayer.dialogLabel = nil

SaveGameLayer.ts = nil
SaveGameLayer.scheduleHandle = nil
SaveGameLayer.isSaving = nil

SaveGameLayer.__create = psModalLayer.create

function SaveGameLayer:create()
	local layer = SaveGameLayer:__create()
	layer:init()
	return layer
end

function SaveGameLayer:init()
	self.isSaving = false

	local screenSize = cc.Director:getInstance():getWinSize()

	local capInsets = CCRectMake(20, 20, 60, 60)
	local dialogWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	local windowSize = CCSizeMake(screenSize.width * 0.95, screenSize.height * 0.2)
	local windowPos = ccp(screenSize.width * 0.5, screenSize.height * 0.1)
	dialogWindow:setPreferredSize(windowSize)
	dialogWindow:setPosition(windowPos)
	self:addChild(dialogWindow)

	local infoWindow = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_orange.png", capInsets)
	infoWindow:setPreferredSize(CCSizeMake(screenSize.width * 0.65, screenSize.height * 0.7))
	infoWindow:setAnchorPoint(0, 0)
	infoWindow:setPosition(screenSize.width * 0.025, screenSize.height * 0.225)
	self:addChild(infoWindow)

	local titleMap = { "玩家", "地点", "时间", "已发现", "已捕捉", "徽章" }
	local mapModel = MapInfo:create(DataCenter.currentPlayerData.currentMapId)
	local discovered = 0
	local captured = 0
	if DataCenter.collectionData then
		for k, v in pairs(DataCenter.collectionData) do
			if v then
				captured = captured + 1
			end
			discovered = discovered + 1
		end
	end
	self.ts = TimeSpan:create(DataCenter.currentPlayerData.gameTime)
	local contentMap = { DataCenter.currentPlayerData.name, 
		mapModel.name == DBNULL and "室内" or mapModel.name, 
		self.ts:toString(),
		discovered,
		captured,
		DataCenter.badges and table.getTotalCount(DataCenter.badges) or 0
	}
	for i = 1, #titleMap do
		local lbl = cc.Label:createWithTTF(titleMap[i] .. ": " .. contentMap[i], GameConfig.DEFAULT_FONT_PATH, 24)
		lbl:setAnchorPoint(0, 0.5)
		lbl:setColor(COLOR3B_RED)
		lbl:setPosition(infoWindow:getContentSize().width * 0.1, infoWindow:getContentSize().height * (0.9 - (i - 1) * 0.16))
		infoWindow:addChild(lbl)
		if i == 3 then
			self.timeLabel = lbl
		end
	end

	local dialogLabel = cc.Label:createWithTTF("存档将会覆盖之前的进度，确认要存档吗？", GameConfig.DEFAULT_FONT_PATH, 18, CCSizeMake(700, 60))
	dialogLabel:setAnchorPoint(ccp(0, 1))
	dialogLabel:setPosition(60, 80)
	dialogLabel:setColor(COLOR3B_BLACK)
	self:addChild(dialogLabel)
	self.dialogLabel = dialogLabel

	local listMenu = CommonListMenu:create({"是", "否"}, CCSizeMake(150, 100))
	listMenu:setAnchorPoint(1, 0)
	listMenu:setPosition(screenSize.width * 0.975, screenSize.height * 0.225)
	listMenu:setItemSelectedScript(MakeScriptHandler(self, self.onListItemSelected))
	listMenu:setCancelScript(MakeScriptHandler(self, self.onCancelSelection))	-- overwrite the default behavior
	self:addChild(listMenu)
	self.list = listMenu

	self:registerScriptHandler(MakeScriptHandler(self, self.onNodeEvent))
end

function SaveGameLayer:onNodeEvent(event)
	if event == "enter" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			local kbdListener = Win32EventListenerKeyboard:createWithTarget(self)
			kbdListener:registerScriptWin32Handler(MakeScriptHandler(self, self.onKeyboardPressed), pf.Handler.WIN32_KEYBOARD_DOWN)
			Win32Notifier:getInstance():addEventListener(kbdListener)
			self.kbdListener = kbdListener
		end
		self.list:setKeyEventsSwallowed(false)		-- don't swallow the events

		self.scheduleHandle = cc.Director:getInstance():getScheduler():scheduleScriptFunc(MakeScriptHandler(self, self.onTimeTick), 1, false)
	elseif event == "exit" then
		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS and self.kbdListener then
			Win32Notifier:getInstance():removeEventListener(self.kbdListener)
			self.kbdListener = nil
		end

		if self.scheduleHandle then
  			cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.scheduleHandle)
  			self.scheduleHandle = nil
  		end
	end
end

function SaveGameLayer:onListItemSelected(menu, item)
	local index = item:getShowIndex()
	log("SaveGameLayer:onListItemSelected", index)
	if self.isSaving then
		return
	end
	if index == 0 then
		self.isSaving = true
		self.list:markExit()
		self.list = nil
		self:showSavingMessage()
		self:save()
		self.toBeClosed = true
	elseif index == 1 then
		self.toBeClosed = true
	end
end

function SaveGameLayer:showSavingMessage(process)
	process = process or 0
	local str = ""
	for i = 1, process % 3 do
		str = str .. "."
	end
	self.dialogLabel:setString("保存中" .. str)
	if self.isSaving then
		CallFunctionAsync(self, self.showSavingMessage, 0.2, (process + 1) % 3)
	else
		self.dialogLabel:setString("保存成功!")
		CallFunctionAsync(self, self.onCancelSelection, 1)
	end
end

function SaveGameLayer:save()
	require "src/scene/save/GameSaveManager"

	GameSaveManager:saveTo(DataCenter.relatedSaveIndex)
	self.isSaving = false
end

function SaveGameLayer:onCancelSelection()
	if self.isSaving then
		return
	end
	if self.list then
		self.list:removeFromParent()
	end
	self:removeFromParent()

	Notifier:notify(NotifyEvents.MapView.ShowMapMenu)
end

function SaveGameLayer:onKeyboardPressed(keyCode)
	log("SaveGameLayer:onKeyboardPressed")
	if self.isSaving then
		return
	end
	if self.toBeClosed then
		if self.list then
			self.list:removeFromParent()
		end
		self:removeFromParent()
	end
end

function SaveGameLayer:onTimeTick()
	self.ts:setTotalSeconds(self.ts:getTotalSeconds() + 1)
	self.timeLabel:setString("时间: " .. self.ts:toString())
end