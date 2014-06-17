--[[
	Description: Manage observers
	Author: M.Wan
	Date: 04/14/2014
]]

luaClass("Observer")

Observer.sender = nil		-- notifier 
Observer.callback = nil		-- callback
Observer.params = nil		-- params, a table

function Observer:call()
	if self.callback then
		self.callback(self.sender, unpack(self.params))
	end
end


-- static
Notifier = {}

Notifier.observerMap = {}		-- observer map

function Notifier:addObserver(event, sender, callback, ...)
	local observer = Observer:new()
	observer.sender = sender
	observer.callback = callback
	observer.params = {...}

	if not self.observerMap[event] then
		self.observerMap[event] = {}
	end
	table.insert(self.observerMap[event], observer)
end

function Notifier:removeObserver(event, sender)
	if not self.observerMap[event] then
		return
	end
	local newObservers = {}
	for i, observer in ipairs(self.observerMap[event]) do
		if observer.sender ~= sender then
			table.insert(newObservers, observer)
		end
	end
	if #newObservers <= 0 then
		newObservers = nil
	end
	self.observerMap[event] = newObservers
end

function Notifier:notify(event)
	for k, v in pairs(self.observerMap) do
		if k == event then
			for _, observer in ipairs(v) do
				observer:call()
			end
			break
		end
	end
end