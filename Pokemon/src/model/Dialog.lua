--[[
	Description: Dialog Model (From DB)
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
Dialog.eventId = DBNULL		--事件id

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

		self.id = tonumber(data.id)
		self.relatedStep = tonumber(data.relatedStep)
		self.mapId = tonumber(data.mapId)
		if data.params ~= DBNULL then
			self.params = string.split(data.params, ";")
		else
			self.params = {}
		end
		if data.isQuestion == "1" then
			self.isQuestion = true
		else
			self.isQuestion = false
		end
		self.choices = string.split(data.choices, ";")
		if data.actionId ~= DBNULL then
			local ids = string.split(data.actionId, "|")
			if #ids == 1 then
				self.actionId = tonumber(data.actionId)
			else
				-- 性别分支
				self.actionId = DataCenter.currentPlayerData.gender == Enumerations.GENDER.MALE and tonumber(ids[1]) or tonumber(ids[2])
			end
		end
		self.eventId = tonumber(data.eventId)
	else
		log("Dialog:updateFromDB failed, id [" .. self.id .. "] does not exist.")
	end
end

-- 获得拥有参数的对话的正确内容
function Dialog:getCorrectDialog()
	local correctDialog = self.dialog
	for i, param in ipairs(self.params) do
		-- tmd 为什么用中括号会有bug!!!
		local originStr = "{" .. tostring(i) .. "}"
		local targetStr = self:getParamString(param)
		correctDialog = string.replaceAll(correctDialog, originStr, targetStr)
	end
	log("Correct Dialog: ", correctDialog)
	return correctDialog
end

function Dialog:getParamString(param)
	if param == "hero" then
		return DataCenter.currentPlayerData.name
	elseif param == "cohero" then
		return DataCenter.currentPlayerData.gender == Enumerations.GENDER.MALE and "小云" or "小风"
	elseif param == "ta" then
		return DataCenter.currentPlayerData.gender == Enumerations.GENDER.MALE and "她" or "他"
	end
	return ""
end