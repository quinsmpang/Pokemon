--[[
	Description: pokemon ui controller
	Author: M.Wan
	Date: 08/31/2014
]]

class("PokemonViewController", psViewController)

PokemonViewController.root = nil

PokemonViewController.resources = {
	"images/pokemon.plist",
	"images/pokemon.pvr.ccz",
}

function PokemonViewController:load()
	log("PokemonViewController:load")
	self:loadResources()
	self:addObservers()

	self:renderView()
end

function PokemonViewController:unload()
	log("PokemonViewController:unload")
	self:removeObservers()
	self.root:getEventDispatcher():removeEventListener(self.touchEventListener)
	self.root:removeFromParent()
	self:cleanResources()
end

function PokemonViewController:loadResources()
	log("PokemonViewController:loadResources")
	LoadSpriteFrames(self.resources)
end

function PokemonViewController:cleanResources()
	log("PokemonViewController:cleanResources")
	RemoveSpriteFrames(self.resources)
end

function PokemonViewController:addObservers()
	log("PokemonViewController:addObservers")
	Notifier:addObserver(NotifyEvents.MapView.ActionEnded, self, self.onActionEnded)
	Notifier:addObserver(NotifyEvents.MapView.DialogKeyboardResponse, self, self.onKeyboardEvent)
	Notifier:addObserver(NotifyEvents.MapView.ResponseBegan, self, self.onResponseBegan)
end

function PokemonViewController:removeObservers()
	log("PokemonViewController:removeObservers")
	Notifier:removeObserver(NotifyEvents.MapView.ActionEnded, self)
	Notifier:removeObserver(NotifyEvents.MapView.DialogKeyboardResponse, self)
	Notifier:removeObserver(NotifyEvents.MapView.ResponseBegan, self)
end

function PokemonViewController:renderView()
	local coreLayer = self:getScene():getCoreLayer()

	self.root = ModalLayer:create()
	self:getScene():addChild(self.root)

	local data = ZipHelper:getInstance():getFileDataInZip("images/pokemon_gif.rc", "493.gif", GameConfig.ZIP_PASSWORD)
	local frames = ImageUtils:getInstance():getGifFrames(data)
	-- local icon = frames:objectAt(0)
	-- tolua.cast(icon, "cc.Texture2D")

	-- local sp = cc.Sprite:createWithTexture(icon)
	-- sp:setPosition(100, 100)
	-- self.root:addChild(sp)

	local animate = ImageUtils:getInstance():createAnimationByFrames(frames, 0.1)
	local action = cc.RepeatForever:create(animate)
	local sp = cc.Sprite:create()
	sp:setPosition(100, 100)
	self.root:addChild(sp)
	sp:runAction(action)
end