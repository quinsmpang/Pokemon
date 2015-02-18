--[[
	Description: Test blend.
	Author: M.Wan
	Date: 02/18/2015
]]

class("TestBlendLayer", psLayer)

TestBlendLayer.__create = psLayer.create

function TestBlendLayer:create()
	local layer = TestBlendLayer:__create()
	layer:init()
	return layer
end

function TestBlendLayer:init()
	local winSize = cc.Director:getInstance():getWinSize()

	local bg = cc.Sprite:createWithSpriteFrameName("images/item/background.jpg")
	bg:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	self:addChild(bg)

	local mask = cc.LayerColor:create(ccc3(255, 255, 255))
	-- mask:setCascadeOpacityEnabled(true)
	mask:setOpacity(255)
	mask:ignoreAnchorPointForPosition(false)
	-- self:addChild(mask)

	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemons.rc", "003_b.png", GameConfig.ZIP_PASSWORD)
	local playerPokemon = ImageUtils:getInstance():createSpriteWithBinaryData(data)
	playerPokemon:setPosition(winSize.width * 0.5, winSize.height * 0.5)
	-- playerPokemon:setCascadeOpacityEnabled(true)
	self:addChild(playerPokemon)

	mask:setContentSize(playerPokemon:getContentSize())
	mask:setPosition(playerPokemon:getPosition())

	playerPokemon:setBlendFunc(gl.ONE_MINUS_DST_ALPHA, gl.ONE_MINUS_SRC_ALPHA)
end