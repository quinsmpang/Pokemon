--[[
	Description: game settings info
	Author: M.Wan
	Date: 05/19/2014
]]

GameSettings = {}

GameSettings.musicVolume = nil		-- 音乐声音大小
GameSettings.effectVolume = nil		-- 音效声音大小
GameSettings.Keys = nil

if targetPlatform == cc.PLATFORM_OS_WIN32 then
	GameSettings.upKey = nil
	GameSettings.downKey = nil
	GameSettings.leftKey = nil
	GameSettings.rightKey = nil
	GameSettings.confirmKey = nil
	GameSettings.cancelKey = nil
	GameSettings.startKey = nil
end

local CONFIG_PATH = "config"

function GameSettings:loadSettings()
	log("GameSettings:loadSettings")

	if not cc.FileUtils:getInstance():isFileExist(CONFIG_PATH) then
		self.musicVolume = 0.5
		self.effectVolume = 0.5

		if targetPlatform == cc.PLATFORM_OS_WIN32 then
			self.upKey = cc.KeyCode.KEY_UP_ARROW
			self.downKey = cc.KeyCode.KEY_DOWN_ARROW
			self.leftKey = cc.KeyCode.KEY_LEFT_ARROW
			self.rightKey = cc.KeyCode.KEY_RIGHT_ARROW
			self.confirmKey = 99		-- c
			self.cancelKey = 118		-- V
			self.startKey = cc.KeyCode.KEY_KP_ENTER
		end
	else
		local result = RecordHelperLua:getTableFromRecord(CONFIG_PATH)

		self.musicVolume = tonumber(result["musicVolume"])
		self.effectVolume = tonumber(result["effectVolume"])

		if targetPlatform == cc.PLATFORM_OS_WIN32 then
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
	
	self:updateKeys()
	RecordHelperLua:recordTable(CONFIG_PATH, self)
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