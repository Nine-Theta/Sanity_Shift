door = nil

function math.Clamp(val, lower, upper)
    assert(val and lower and upper, "not very useful error message here")
    if lower > upper then lower, upper = upper, lower end -- swap if boundaries supplied the wrong way
    return math.max(lower, math.min(upper, val))
end

function start()
	door = parent:getParent():getParent()
	print("DOOR INITIALISED")
end
maxAngle = 100
angleS = 0
direction = 1
secs = 0.95
ctime = 0
function fixedupdate()
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
		direction = -direction
	end
end