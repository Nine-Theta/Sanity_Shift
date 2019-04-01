door = nil

function math.Clamp(val, lower, upper)
    assert(val and lower and upper, "not very useful error message here")
    if lower > upper then lower, upper = upper, lower end -- swap if boundaries supplied the wrong way
    return math.max(lower, math.min(upper, val))
end

function start()
	door = parent:getParent()
	parent:setDistanceLimit(35)
	print("DOOR INITIALISED")
end
maxAngle = 100
angleS = 0
direction = 1
secs = 0.95
ctime = 1

timeToClose = 0
function fixedupdate()
	lastTime = timeToClose
	timeToClose = timeToClose - time.fixedDelta()
	if timeToClose < 0 then
		direction = 1
		if lastTime > 0 then
			parent:getParent():setSound("door_close.wav")
			parent:getParent():playSound()
		end
	end
	ctime = math.Clamp(ctime + (time.fixedDelta() / secs) * direction,0,1)
	angleS = (1 - math.pow(ctime,4)) * maxAngle
	door:setRotation(0,1,0,angleS)
	--print(door:getName())
end

function onraycasthit(caster)
	if keys.down(keys.E) then
	print("Toggling door")
		--if direction == then
		--	angle = 90
		--else
		--	angle = 0
		--end
		parent:setSound("door_open.wav")
		direction = -direction
		if direction == -1 then
			timeToClose = math.random(12,20)
		end
		if direction == -1 then
			parent:getParent():setSound("door_open.wav")
		else
			parent:getParent():setSound("door_close.wav")
		end

		parent:getParent():playSound()
	end
end