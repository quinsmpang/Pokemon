--[[
	Description: Response controller, to deal with response logic
	Author: M.Wan
	Date: 07/12/2014
]]

ResponseController = {}

ResponseController.isUnderResponse = false

function ResponseController:processResponse(responseModel)
	log("ResponseController:processResponse", responseModel.handler, responseModel.params)
	self.isUnderResponse = true
	local responseHandler = responseModel.handler
	local handler = self["response_" .. responseHandler]
	assert(type(handler) == "function", "Unimplemented response handler in ResponseController.")
	handler(self, responseModel.params)
	Notifier:notify(NotifyEvents.MapView.ResponseBegan, responseModel)
end

-------------------------- Response 处理函数 --------------------------
function ResponseController:response_Speak(params)
	MapStateController:setCurrentState(Enumerations.MAP_STATE.DIALOG)
end

function ResponseController:response_SpeakWithRest(params)
	MapStateController:setCurrentState(Enumerations.MAP_STATE.DIALOG)
end

function ResponseController:response_ShowLayer(params)
	
end