--[[
	Description: For test
	Author: M.Wan
	Date: 01/03/2015
]]

class("TestScene", psGameScene)

require "src/scene/test/TestViewController"

function TestScene:onEnter()
	log("TestScene:onEnter")
	local coreLayer = CoreLayer:create()
	self:setCoreLayer(coreLayer)

	local testViewController = TestViewController:create()
	self:loadViewController(testViewController)
end

function TestScene:onExit()
	log("TestScene:onExit")
end