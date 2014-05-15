--[[
	Description: Framework extensions
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

--psGameLayer
class("psGameLayer", {
		create = function()
			return GameLayer:create()
		end,
		createWithTransitions = function(...)
			return GameLayer:createWithTransitions(...)
		end
	})

--psCoreLayer
class("psCoreLayer", {
		create = function()
			return CoreLayer:create()
		end
	})

--psModalLayer
class("psModalLayer", {
		create = function()
			return ModalLayer:create()
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

--psStack
class("psStack", {
		create = function()
			return Stack:create()
		end
	})

--psQueue
class("psQueue", {
		create = function()
			return Queue:create()
		end
	})


-- Be accustomed to old functions
function ccp(x, y)
	return { x = x, y = y }
end

function ccc3(r, g, b)
	return { r = r, g = g, b = b }
end

function ccc4(a, r, g, b)
	return { a = a, r = r, g = g, b = b }
end

function CCSizeMake(width, height)
	return { width = width, height = height }
end

function CCRectMake(originX, originY, width, height)
	return cc.rect(originX, originY, width, height)
end