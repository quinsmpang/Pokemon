--[[
	Description: Keyset Window
	Author: M.Wan
	Date: 05/24/2014
]]

class("KeysetLayer", psModalLayer)

KeysetLayer.window = nil		--背景窗口
KeysetLayer.border = nil		--窗口边框
KeysetLayer.btnConfirm = nil	--确定按钮
KeysetLayer.btnCancel = nil		--取消按钮
KeysetLayer.panelList = nil		--所有按键Panel的集合

KeysetLayer.isWaitingForKey = nil		--是否正在等待用户按键
KeysetLayer.availableKeys = nil
KeysetLayer.enableClick = nil		--是否允许用户点击

TAG = {
	WINDOW = 1,
	UP_PANEL = 2,
	DOWN_PANEL = 3,
	LEFT_PANEL = 4,
	RIGHT_PANEL = 5,
	A_PANEL = 6,
	B_PANEL = 7,
	START_PANEL = 8,
	KEY_LABEL = 11
}

function KeysetLayer:initUI()
	log("KeysetLayer:initUI")

	self.isWaitingForKey = false
	self.enableClick = false
	-- init available keys which can set.
	local tmpDict = {}
	for k, v in pairs(cc.KeyCode) do
		tmpDict[v] = k
	end

	self.availableKeys = {}
	self.availableKeys[cc.KeyCode.KEY_RETURN] = "Enter"
	self.availableKeys[cc.KeyCode.KEY_CTRL] = "Ctrl"
	self.availableKeys[cc.KeyCode.KEY_ALT] = "Alt"
	self.availableKeys[cc.KeyCode.KEY_INSERT] = "Insert"
	self.availableKeys[cc.KeyCode.KEY_HOME] = "Home"
	self.availableKeys[cc.KeyCode.KEY_PG_UP] = "PgUp"
	self.availableKeys[cc.KeyCode.KEY_DELETE] = "Delete"
	self.availableKeys[cc.KeyCode.KEY_END] = "End"
	self.availableKeys[cc.KeyCode.KEY_PG_DOWN] = "PgDown"
	self.availableKeys[cc.KeyCode.KEY_LEFT_ARROW] = "←"
	self.availableKeys[cc.KeyCode.KEY_RIGHT_ARROW] = "→"
	self.availableKeys[cc.KeyCode.KEY_UP_ARROW] = "↑"
	self.availableKeys[cc.KeyCode.KEY_DOWN_ARROW] = "↓"
	self.availableKeys[cc.KeyCode.KEY_KP_MINUS] = "KP_MINUS"
	self.availableKeys[cc.KeyCode.KEY_KP_PLUS] = "KP_PLUS"
	self.availableKeys[cc.KeyCode.KEY_KP_MULTIPLY] = "KP_MULTIPLY"
	self.availableKeys[cc.KeyCode.KEY_KP_DIVIDE] = "KP_DIVIDE"
	self.availableKeys[cc.KeyCode.KEY_KP_ENTER] = "KP_ENTER"
	for i = cc.KeyCode.KEY_KP_DELETE, cc.KeyCode.KEY_KP_PG_UP do
		self.availableKeys[i] = string.sub(tmpDict[i], 5, #tmpDict[i])
	end
	self.availableKeys[cc.KeyCode.KEY_SPACE] = "空格"
	for i = 48, 57 do
		self.availableKeys[i] = tostring(i - 48)
	end
	self.availableKeys[65] = "A"
	self.availableKeys[66] = "B"
	self.availableKeys[67] = "C"
	self.availableKeys[68] = "D"
	self.availableKeys[69] = "E"
	self.availableKeys[70] = "F"
	self.availableKeys[71] = "G"
	self.availableKeys[72] = "H"
	self.availableKeys[73] = "I"
	self.availableKeys[74] = "J"
	self.availableKeys[75] = "K"
	self.availableKeys[76] = "L"
	self.availableKeys[77] = "M"
	self.availableKeys[78] = "N"
	self.availableKeys[79] = "O"
	self.availableKeys[80] = "P"
	self.availableKeys[81] = "Q"
	self.availableKeys[82] = "R"
	self.availableKeys[83] = "S"
	self.availableKeys[84] = "T"
	self.availableKeys[85] = "U"
	self.availableKeys[86] = "V"
	self.availableKeys[87] = "W"
	self.availableKeys[88] = "X"
	self.availableKeys[89] = "Y"
	self.availableKeys[90] = "Z"
	self.availableKeys[160] = "L_SHIFT"
	self.availableKeys[161] = "R_SHIFT"
	self.availableKeys[162] = "L_CTRL"
	self.availableKeys[163] = "R_CTRL"

	-- init ui
	self.window = ScriptCCBReader:readCCB("ccb/KeysetLayer.ccbi", self)
	self.window:setPosition(0, 0)
	self.window:setScale(0)
	self:addChild(self.window)

	self.border = self.window:getChildByTag(TAG.WINDOW)
	tolua.cast(self.border, "cc.Scale9Sprite")

	-- set panel list
	self.panelList = {}
	for i = 2, 8 do
		table.insert(self.panelList, self.window:getChildByTag(i))
	end

	-- set key labels
	assert(#self.panelList == 7, "Incorrect panel count")

	for i, panel in ipairs(self.panelList) do
		self:setKeyString(i, panel)
	end
end

function KeysetLayer:setKeyString(index, panel)
	local keyCode = GameSettings.Keys[index]
	if self.availableKeys[keyCode] then
		local label = panel:getChildByTag(TAG.KEY_LABEL)
		print(label)
		tolua.cast(label, "cc.Label")
		label:setString(self.availableKeys[keyCode])
	end
end

function KeysetLayer:onComeIn()
	local enterAction = cc.Sequence:create(
		cc.EaseIn:create(cc.ScaleTo:create(0.15, 1.1), 2),
		cc.ScaleTo:create(0.03, 1),
		cc.CallFunc:create(MakeScriptHandler(self, self.onComeInEnd))
		)

	self.window:runAction(enterAction)
end
function KeysetLayer:onComeInEnd()
	self.enableClick = true
end

function KeysetLayer:onGoOut()
end