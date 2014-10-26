--[[
	Description: Game records controller
	Author: M.Wan
	Date: 10/26/2014
]]

class("GameRecordsViewController", psViewController)

GameRecordsViewController.resources = {
}

function GameRecordsViewController:load()
	log("GameRecordsViewController:load")
	self:loadResources()
	self:renderView()
end

function GameRecordsViewController:unload()
	log("GameRecordsViewController:unload")
	self:cleanResources()
end

function GameRecordsViewController:loadResources()
	log("GameRecordsViewController:loadResources")
	LoadSpriteFrames(self.resources)
end

function GameRecordsViewController:cleanResources()
	log("GameRecordsViewController:cleanResources")
	RemoveSpriteFrames(self.resources)
end

function GameRecordsViewController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	local screenSize = cc.Director:getInstance():getWinSize()
end