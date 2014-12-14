-- load lanes module
local lanes = require "src/framework/lanes/lanes"
lanes.configure()

local linda = lanes.linda()

Threading = {}

-- create a new thread with varadic params
function Threading:newThread(threadFunc, ...)
	local f = lanes.gen("*", threadFunc)

	local th, err = f(...)
	return th, err
end

function Threading:send(key, value)
	linda:send("cc", cc)
end

function Threading:retrieve(key, timeout)
	timeout = timeout or 3
	return linda:receive(timeout, key)
end