hit = false
rotationT = 0
rotation = 0
rotationSteps = 6
function start()
	rotationT = ((360 / rotationSteps)) * math.random(1,rotationSteps)
	local number = math.floor((rotationT % 360) / (360 / rotationSteps) + 1)
	--print("Code lock changed to: " .. number)
	parent:setName(number)
end
function fixedupdate()
	if hit then 
		parent:setFluorReaction(1)
	else
		parent:setFluorReaction(0)
	end
	rotation = rotation + (rotationT - rotation) * 0.04
	parent:setRotation(1,0,0,-rotation)
	hit = false
end
function loadRandomTick()
	step = math.random(1,2)
	parent:setSound("lock_click" .. step .. ".wav")
	--parent:setSound("thomas.wav")
	parent:playSound()
end
function raycastresult(lol)
	print("RESULT")
end

function onraycasthit(caster)
	hit = true
	if keys.down(keys.E) then
		--print("Turning Lock Wheel!")
		loadRandomTick()
		rotationT = (rotationT + (360 / rotationSteps))
		local number = math.floor((rotationT % 360) / (360 / rotationSteps) + 1)
		print("Code lock changed to: " .. number)
		parent:setName(number)
	end
end