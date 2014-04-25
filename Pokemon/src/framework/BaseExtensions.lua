--[[
	Description: Framework extension class
	Author: M.Wan
	Date: 04/25/2014
]]

--psGameScene
class("psGameScene", {
		create = function(...)
			return GameScene:create(...)
		end
	})

--psViewController
class("psViewController", {
		create = function()
			return ViewController:create()
		end
	})

--psActiveSprite
class("psActiveSprite", {
		create = function(...)
			return ActiveSprite:create(...)
		end
	})

--psButton
class("psButton", {
		create = function(...)
			return Button:create(...)
		end
	})

--psTextBlock
class("psTextBlock", {
		create = function(...)
			return TextBlock:create(...)
		end
	})

--psMaskLayer
class("psMaskLayer", {
		create = function(...)
			return MaskLayer:create(...)
		end
	})

--psNode
class("psNode", {
		create = function(...)
			return cc.Node:create()
		end
	})

--psLayer
class("psLayer", {
		create = function(...)
			return cc.Layer:create()
		end
	})

--psSprite
class("psSprite", {
		create = function(...)
			return cc.Sprite:create(...)
		end, 
		createWithTexture = function(...)
			return cc.Sprite:createWithTexture(...)
		end, 
		createWithSpriteFrame = function(...)
			return cc.Sprite:createWithSpriteFrame(...)
		end,
		createWithSpriteFrameName = function(...)
			return cc.Sprite:createWithSpriteFrameName(...)
		end
	})