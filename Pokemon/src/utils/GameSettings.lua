--[[
	Description: game settings info
	Author: M.Wan
	Date: 05/19/2014
]]

GameSettings = {}

GameSettings.musicVolume = nil		-- 音乐声音大小
GameSettings.effectVolume = nil		-- 音效声音大小
GameSettings.Keys = nil

if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
	-- 按键信息
	GameSettings.upKey = nil
	GameSettings.downKey = nil
	GameSettings.leftKey = nil
	GameSettings.rightKey = nil
	GameSettings.confirmKey = nil
	GameSettings.cancelKey = nil
	GameSettings.startKey = nil
end

function GameSettings:loadSettings()
	log("GameSettings:loadSettings")

	if not IOUtils:getInstance():fileExists(GameConfig.CONFIG_PATH) then
		log("config file doesn't exist, init default settings.")
		self.musicVolume = 0.5
		self.effectVolume = 0.5

		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			self.upKey = pf.Win32KeyCode.VK_UP
			self.downKey = pf.Win32KeyCode.VK_DOWN
			self.leftKey = pf.Win32KeyCode.VK_LEFT
			self.rightKey = pf.Win32KeyCode.VK_RIGHT
			self.confirmKey = pf.Win32KeyCode.VK_C
			self.cancelKey = pf.Win32KeyCode.VK_V
			self.startKey = pf.Win32KeyCode.VK_RETURN
		end
	else
		log("config file found, load settings.")
		local result = RecordHelperLua:getTableFromRecord(GameConfig.CONFIG_PATH)

		self.musicVolume = tonumber(result["musicVolume"])
		self.effectVolume = tonumber(result["effectVolume"])

		if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
			self.upKey = tonumber(result["upKey"])
			self.downKey = tonumber(result["downKey"])
			self.leftKey = tonumber(result["leftKey"])
			self.rightKey = tonumber(result["rightKey"])
			self.confirmKey = tonumber(result["confirmKey"])
			self.cancelKey = tonumber(result["cancelKey"])
			self.startKey = tonumber(result["startKey"])
		end
	end

	self.Keys = {
		self.upKey,
		self.downKey,
		self.leftKey,
		self.rightKey,
		self.confirmKey,
		self.cancelKey,
		self.startKey
	}

	cc.SimpleAudioEngine:getInstance():setMusicVolume(self.musicVolume)
	cc.SimpleAudioEngine:getInstance():setEffectsVolume(self.effectVolume)
	log(string.format("MusicVolume: %.2f, EffectVolume: %.2f", self.musicVolume, self.effectVolume))
end

function GameSettings:saveSettings()
	log("GameSettings:saveSettings")
	
	if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
		self:updateKeys()
	end
	RecordHelperLua:recordTable(GameConfig.CONFIG_PATH, self)
end

function GameSettings:updateKeys()
	self.upKey = self.Keys[1]
	self.downKey = self.Keys[2]
	self.leftKey = self.Keys[3]
	self.rightKey = self.Keys[4]
	self.confirmKey = self.Keys[5]
	self.cancelKey = self.Keys[6]
	self.startKey = self.Keys[7]
end