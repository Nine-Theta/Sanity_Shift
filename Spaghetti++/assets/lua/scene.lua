--initialises the scene. You can create gameObject:new() here, add components to game objects, move them around, etc.

function init()
	print("Loading custom scene")
	--print(test.test())
	local newObj = gameObject:new()
	newObj:setName("luaObjTest")
	local cam = gameObject:new()
	cam:addComponent("camera")
	cam:setName("Camera")
end