--[[
	Description: Item info (from DB)
	Author: M.Wan
	Date: 11/19/2014
]]

luaClass("ItemInfo", psModel)

-- db attributes
ItemInfo.id = DBNULL
ItemInfo.name = DBNULL
ItemInfo.itemType = DBNULL		-- 道具类型
ItemInfo.price = DBNULL			-- 价格
ItemInfo.description = DBNULL	-- 描述
ItemInfo.handler = DBNULL
ItemInfo.params = DBNULL

function ItemInfo:create(id)
	local model = ItemInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function ItemInfo:updateFromDB()
	log("ItemInfo:updateFromDB")

	local data = GameDBHelper:queryItemById(self.id)
	if data then
		self:updateWithData(data)

		self.id = tonumber(data.id)
		self.itemType = tonumber(data.itemType)
		self.price = tonumber(data.price)
	else
		log("ItemInfo:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end