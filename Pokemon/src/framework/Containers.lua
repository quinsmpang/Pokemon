--[[
	Description: Data structures
	Author: M.Wan
	Date: 06/29/2014
]]

-------------- LinkedList --------------
luaClass("LinkedListLua")

LinkedListLua.head = nil
LinkedListLua.tail = nil
LinkedListLua.length = nil

function LinkedListLua:init()
	self.length = 0
end

function LinkedListLua:append(data)
	if self:empty() then
		self.head = { data = data }
		self.tail = self.head
	else
		local node = { data = data }
		self.tail.next = node
		node.prev = self.tail
		self.tail = node
	end
	self.length = self.length + 1
end

function LinkedListLua:removeHead()
	if self:empty() then
		return
	end
	if self.length == 1 then
		self.head = nil
		self.tail = nil
	else
		self.head.next.prev = nil
		self.head = self.head.next
	end
	self.length = self.length - 1
end

function LinkedListLua:removeTail()
	if self:empty() then
		return
	end
	if self.length == 1 then
		self.head = nil
		self.tail = nil
	else
		self.tail.prev.next = nil
		self.tail = self.tail.prev
	end
	self.length = self.length - 1
end

function LinkedListLua:count()
	return self.length
end

function LinkedListLua:empty()
	return self.length <= 0
end


-------------- Queue --------------
luaClass("QueueLua")

QueueLua.items = nil

function QueueLua:init()
	self.items = LinkedListLua:new()
end

function QueueLua:enqueue(data)
	self.items:append(data)
end

function QueueLua:dequeue()
	self.items:removeHead()
end

function QueueLua:front()
	return self.items.head
end

function QueueLua:count()
	return self.items:count()
end

function QueueLua:empty()
	return self.items:empty()
end


-------------- Stack --------------
luaClass("StackLua")

StackLua.items = nil

function StackLua:init()
	self.items = LinkedListLua:new()
end

function StackLua:push(data)
	self.items:append(data)
end

function StackLua:pop()
	self.items:removeTail()
end

function StackLua:top()
	return self.items.tail
end

function StackLua:count()
	return self.items:count()
end

function StackLua:empty()
	return self.items:empty()
end
