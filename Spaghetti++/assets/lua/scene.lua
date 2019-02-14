--initialises the scene. You can create gameObject:new() here, add components to game objects, move them around, etc.

function init()
	print("Loading custom scene")
	--print(test.test())
	local newObj = gameObject:new()
	newObj:setName("luaObjTest")
	newObj:setPos(-300,300,300)
	--newObj:addComponent("text","Press Spacebar to play!")
	--newObj:addComponent("lua","startscreen.lua")
	local light = gameObject.new()
	light:setPos(-0.9,-1.2,3.1)
	light:addComponent("lua","flashlightMove.lua")
	light:setName("FlashLight")
	local cam = gameObject:new()
	light:setParent(cam)
	local lightAura = gameObject.new()
	lightAura:setParent(light)
	lightAura:addComponent("pointlight",9)
	lightAura:setPos(0,0,0)
	cam:setName("Camera")	
	cam:addComponent("camera")
	cam:addComponent("lua","movement.lua")
	cam:setPos(0,0,0)
	light:addComponent("spotlight",35)
	
	local mesh = gameObject.new()
	mesh:addComponent("mesh","monkeyhead.obj")
	mesh:setPos(0,0,10)
	mesh:setName("PhysicsTest")
	mesh:addComponent("boxcollider",2,2,2,1)
	--audio.buffer("LaserBlaster.wav")
	--audio.buffer("PlayerDeathSound.wav")
end
