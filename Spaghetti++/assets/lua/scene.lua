--initialises the scene. You can create gameObject:new() here, add components to game objects, move them around, etc.

function init()
	print("Loading custom scene")
	--print(test.test())
	local newObj = gameObject:new()
	newObj:setName("luaObjTest")
	newObj:setPos(-300,300,300)
	--newObj:addComponent("text","Press Spacebar to play!")
	--newObj:addComponent("lua","startscreen.lua")
	local cam = gameObject:new()
	cam:setName("Camera")	
	cam:addComponent("camera")
	cam:addComponent("lua","movement.lua")
	cam:setPos(0,2,0)
	audio.buffer("LaserBlaster.wav")
	audio.buffer("PlayerDeathSound.wav")
end
