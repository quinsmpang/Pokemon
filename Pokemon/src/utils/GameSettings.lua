--[[
	Description: game settings info
	Author: M.Wan
	Date: 05/19/2014
]]

GameSettings = {}

GameSettings.musicVolume = nil		-- 音乐声音大小
GameSettings.effectVolume = nil		-- 音效声音大小

local CONFIG_PATH = "config"

function GameSettings:loadSettings()
	log("GameSettings:loadSettings")
	if not cc.FileUtils:getInstance():isFileExist(CONFIG_PATH) then
		self.musicVolume = 0.5
		self.effectVolume = 0.5
	else
		local result = RecordHelperLua:getTableFromRecord(CONFIG_PATH)
		self.musicVolume = tonumber(result["musicVolume"])
		self.effectVolume = tonumber(result["effectVolume"])
	end
	cc.SimpleAudioEngine:getInstance():setMusicVolume(self.musicVolume)
	cc.SimpleAudioEngine:getInstance():setEffectsVolume(self.effectVolume)
	log("MusicVolume: %.2f, EffectVolume: %.2f", self.musicVolume, self.effectVolume)
end

function GameSettings:saveSettings()
	log("GameSettings:saveSettings")
	RecordHelperLua:recordTable(CONFIG_PATH, self)
end