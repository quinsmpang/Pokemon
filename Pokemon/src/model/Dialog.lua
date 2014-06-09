--[[
	Description: Dialog Model
	Author: M.Wan
	Date: 06/09/2014
]]

luaClass("Dialog", psModel)

-- db attributes
Dialog.id = DBNULL		--id
Dialog.relatedStep = DBNULL		--关联剧情step
Dialog.dialog = DBNULL		--对话内容
Dialog.speaker = DBNULL		--说话者
Dialog.params = DBNULL		--参数
Dialog.isQuestion = DBNULL	--是否需要回答
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
	self:updateWithData(data)

	self.id = tonumber(data.id)
	self.relatedStep = tonumber(data.relatedStep)
end