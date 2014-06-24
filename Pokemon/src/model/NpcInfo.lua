--[[
	Description: NPC info (from DB)
	Author: M.Wan
	Date: 06/24/2014
]]

luaClass("NpcInfo", psModel)

NpcInfo.id = DBNULL
NpcInfo.name = DBNULL		-- 姓名
NpcInfo.frameName = DBNULL		-- frame name

function NpcInfo:create(id)
	local model = NpcInfo:new()
	model.id = id
	model.updateFlag = true

	return model
end

function NpcInfo:updateFromDB()
	log("NpcInfo:updateFromDB")
	local data = GameDBHelper:queryNpcInfoById(self.id)
	if data then
		self:updateWithData(data)

		self.name = data.name
		self.frameName = data.frameName
	else
		log("NpcInfo:updateFromDB failed, id[" .. self.id .. "] does not exist.")
	end
end