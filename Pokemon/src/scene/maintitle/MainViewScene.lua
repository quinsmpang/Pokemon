--[[
	Description: Main title scene
	Author: M.Wan
	Date: 05/03/2014
]]

require "src/scene/maintitle/MainViewController"

class("MainViewScene", psGameScene)

function MainViewScene:onEnter()
	log("MainViewScene:onEnter")
	local coreLayer = CoreLayer:create()
	self:setCoreLayer(coreLayer)

	local mainViewController = MainViewController:create()
	self:loadViewController(mainViewController)
end

function MainViewScene:onExit()
	log("MainViewScene:onExit")
end