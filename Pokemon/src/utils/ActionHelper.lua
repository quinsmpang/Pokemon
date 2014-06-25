--[[
	Description: Action helper, to deal with action logic
	Author: M.Wan
	Date: 06/25/2014
]]

ActionHelper = {}

function ActionHelper:processAction(actionModel)
	log("ActionHelper:processAction", actionModel.handler)
	local actionHandler = actionModel.handler
	local handler = self["action_" .. actionHandler]
	assert(type(handler) == "function", "Unimplemented action handler in ActionHelper.")
	handler(self, actionModel.params)
end

-------------------------- Action 处理函数 --------------------------
function ActionHelper:action_FadeOut()
	
end