--[[
	Description: Response model (From DB)
	Author: M.Wan
	Date: 07/12/2014
]]

luaClass("Response", psModel)

Response.id = DBNULL
Response.speaker = DBNULL 		-- 说话者
Response.type = DBNULL			-- 类型
Response.handler = DBNULL		-- 处理函数名
Response.params = DBNULL		-- 参数

function Response:create(id)
	local model = Response:new()
	model.id = id
	model.updateFlag = true

	return model
end

function Response:simulate(speaker, content)
	local model = Response:new()
	model.id = -1
	model.speaker = speaker
	model.type = 0
	model.handler = "Speak"
	model.params = content
	model.updateFlag = false

	return model
end

function Response:updateFromDB()
	log("Response:updateFromDB")
	local data = GameDBHelper:queryResponseById(self.id)
	if data then
		self:updateWithData(data)

		self.id = tonumber(data.id)
		self.type = tonumber(data.type)
	else
		log("Response:updateFromDB failed, id[" .. self.id .. "] does not exist.")
	end
end