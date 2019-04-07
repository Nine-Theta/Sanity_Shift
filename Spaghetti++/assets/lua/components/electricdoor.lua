door = nil

function math.Clamp(val, lower, upper)
    assert(val and lower and upper, "not very useful error message here")
    if lower > upper then lower, upper = upper, lower end -- swap if boundaries supplied the wrong way
    return math.max(lower, math.min(upper, val))
end

function start()
	
end
fuse = 5

function onmessage(msg)
	if msg == "fuse" then
		fuse = fuse - 1
	elseif msg == "unfuse" then
		fuse = fuse + 1
	end
	if fuse == 0 then
		x,y,z = parent:getPos()
		parent:setPos(-2.1,y,z)
		parent:setSound("electric_door_open.wav",0.001)
		parent:playSound()
	end
	print("Fuses left until door: " .. fuse)
end

function onraycasthit(caster)
	
end