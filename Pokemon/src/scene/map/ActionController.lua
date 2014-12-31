--[[
	Description: Action controller, to deal with action logic
	Author: M.Wan
	Date: 06/25/2014
]]

ActionController = {}

ActionController.isUnderAction = false		-- 是否正在处理action

function ActionController:processAction(actionModel)
	log("ActionController:processAction", actionModel.handler, actionModel.params)
	self.isUnderAction = true
	MapStateController:setCurrentState(Enumerations.MAP_STATE.ACTION)
	local actionHandler = actionModel.handler
	local handler = self["action_" .. actionHandler]
	assert(type(handler) == "function", "Unimplemented action handler in ActionController.")
	handler(self, actionModel.params)
	Notifier:notify(NotifyEvents.MapView.ActionBegan, actionModel)
end

-------------------------- Action 处理函数 --------------------------
function ActionController:action_FadeOut(params)
	
end

function ActionController:action_FadeIn(params)
	local mapId = tonumber(params)
	DataCenter.currentPlayerData.currentMapId = mapId
end

function ActionController:action_WalkOut(params)
	
end

function ActionController:action_SwitchMap(params)
	local mapId = tonumber(params)
	DataCenter.currentPlayerData.currentMapId = mapId
end

function ActionController:action_Walk(params)

end

function ActionController:action_PopMessage(params)
	
end

function ActionController:action_OccurAndWalk(params)
	
end