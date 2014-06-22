--[[
	Description: Dialog Model
	Author: M.Wan
	Date: 06/09/2014
]]

luaClass("Dialog", psModel)

-- db attributes
Dialog.id = DBNULL		--id
Dialog.relatedStep = DBNULL		--关联剧情step
Dialog.mapId = DBNULL		--剧情所在地图
Dialog.dialog = DBNULL		--对话内容
Dialog.speaker = DBNULL		--说话者
Dialog.params = DBNULL		--对话参数
Dialog.isQuestion = DBNULL	--是否是问题
Dialog.choices = DBNULL		--回答选项
Dialog.actionId = DBNULL	--执行的动画id

function Dialog:create(id)
	local model = Dialog:new()
	model.id = id
	model.updateFlag = true

	return model
end

function Dialog:updateFromDB()
	log("Dialog:updateFromDB")
	local data = GameDBHelper:queryDialogById(self.id)
	if data then
		self:updateWithData(data)

		self.relatedStep = tonumber(data.relatedStep)
		self.mapId = tonumber(data.mapId)
		self.params = string.split(data.params, ";")
		if data.isQuestion == "1" then
			self.isQuestion = true
		else
			self.isQuestion = false
		end
		self.choices = string.split(data.choices, ";")
		self.actionId = tonumber(data.actionId)
	else
		log("Dialog:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end