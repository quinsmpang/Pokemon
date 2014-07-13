--[[
	Description: Map info model (From DB)
	Author: M.Wan
	Date: 05/29/2014
]]

luaClass("MapInfo", psModel)

MapInfo.id = DBNULL		-- id
MapInfo.path = DBNULL	-- 地图路径
MapInfo.name = DBNULL	-- 地图名称
MapInfo.bgMusic = DBNULL	-- 背景音乐
MapInfo.specialBgMusic = DBNULL	-- 特殊剧情下的背景音乐

function MapInfo:create(id)
	local model = MapInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function MapInfo:updateFromDB()
	log("MapInfo:updateFromDB")
	local data = GameDBHelper:queryMapById(self.id)
	if data then
		self:updateWithData(data)

		self.id = tonumber(data["id"])
	else
		log("MapInfo:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end