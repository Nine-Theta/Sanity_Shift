--parent is component's parent gameObject. It supports functions 

function start()
	--print("Initialised test lua component")
	--print(test.test())
	light = gameObject.find("Flashlight") 
	--also controls the flashlight now, so slightly misleading name but if it works...
	parent:playSound()
	local menuMusic = gameObject.find("Music")
	if menuMusic ~= nil then
		menuMusic:stopSound(7)
	end
	x,y,z = parent:getPos()
	local footsteps = gameObject.new()
	footsteps:setParent(parent:getParent())
	footsteps:setPos(0,0,0)
	footsteps:addComponent("lua","footsteps.lua")
	
end

rotation = 0
verticalSensitivity = 10 --default: 10
upperLimit = 80
lowerLimit = -80

following = false
enabled = true
function update()
	if following then
		return
	end
	if mouse.moved() then
		local mX, mY = mouse.delta()
		
		if (rotation < upperLimit and mY > 0) or (rotation > lowerLimit and mY < 0) then
		rotation = rotation + mY * verticalSensitivity * time.fixedDelta()
		end
		parent:setRotation(1,0,0,rotation)
		--print(mX, mY)
	end
	parent:setPos(x,y,z)
	
end
	
function fixedupdate()
	if following then
		return
	end
	--print("Background track playing: " .. tostring(parent:isPlaying()))
	if not parent:isPlaying() then
		parent:playSound()
	end
	if mouse.buttonDown(1) then
		enabled = not enabled
	end
	if mouse.buttonPressed(0) then
		--light:setActive(not enabled)
	else
		--light:setActive(enabled)
	end
end

function onmessage(msg)
	if msg == "follow" then
		--following = true
	end
end

function ondestroy()
	local menuMusic = gameObject.find("Music")
	if menuMusic ~= nil then
		menuMusic:destroy()
	end
	print("DESTROYED VERTICAL PLAYER CONTROLS")
end

function raycastresult(hit)
	--print(hit:getName())
end