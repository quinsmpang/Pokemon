--[[
	Description: Main title scene
	Author: M.Wan
	Date: 05/03/2014
]]

require "src/controller/maintitle/MainViewController"

class("MainViewScene", psGameScene)

function MainViewScene:onEnter()
	log("MainViewScene:onEnter")
	local mainViewController = MainViewController:create()
	self:loadViewController(mainViewController)
end

function MainViewScene:onExit()
	log("MainViewScene:onExit")
end