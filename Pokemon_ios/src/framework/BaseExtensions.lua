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


----------- Be accustomed to old functions -----------

-- Point
function ccp(x, y)
	return cc.p(x, y)
end

-- Color3B
function ccc3(r, g, b)
	return cc.c3b(r, g, b)
end

-- Color4B
function ccc4(r, g, b, a)
	return cc.c4b(r, g, b, a)
end

-- Size
function CCSizeMake(width, height)
	return cc.size(width, height)
end

-- Rect
function CCRectMake(originX, originY, width, height)
	return cc.rect(originX, originY, width, height)
end

POINT_ZERO = ccp(0, 0)
COLOR3B_BLACK = ccc3(0, 0, 0)
COLOR3B_WHITE = ccc3(255, 255, 255)
COLOR3B_RED = ccc3(255, 0, 0)
COLOR3B_GREEN = ccc3(0, 255, 0)
COLOR3B_BLUE = ccc3(0, 0, 255)