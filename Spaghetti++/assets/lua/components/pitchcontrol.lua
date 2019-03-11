--parent is component's parent gameObject. It supports functions 

function start()
	--print("Initialised test lua component")
	--print(test.test())
	light = gameObject.find("Flashlight") 
	--also controls the flashlight now, so slightly misleading name but if it works...
	parent:playSound()
end

rotation = 0
verticalSensitivity = 10 --default: 10
upperLimit = 90
lowerLimit = -90

enabled = true
function update()

	if mouse.moved() then
		local mX, mY = mouse.delta()
		
		if (rotation < upperLimit and mY > 0) or (rotation > lowerLimit and mY < 0) then
		rotation = rotation + mY * verticalSensitivity * time.fixedDelta()
		end
		parent:setRotation(1,0,0,rotation)
		--print(mX, mY)
	end
	
end
	
function fixedupdate()
	if mouse.buttonDown(1) then
		enabled = not enabled
	end
	if mouse.buttonPressed(0) then
		--light:setActive(not enabled)
	else
		--light:setActive(enabled)
	end
end

function raycastresult(hit)
	print(hit:getName())
end