--[[
	Description: map layer, to load tmx map file
	Author: M.Wan
	Date: 05/29/2014
]]

class("TMXMapLayer", psGameLayer)

TMXMapLayer.mapInfo = nil 		-- MapInfo model

-- treat as static method
function TMXMapLayer:createWithMapInfo(mapInfo, ...)
	local mapLayer = TMXMapLayer:createWithTransitions(...)

	mapLayer.mapInfo = mapInfo

	return mapLayer
end