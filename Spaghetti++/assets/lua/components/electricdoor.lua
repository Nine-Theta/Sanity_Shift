door = nil

function math.Clamp(val, lower, upper)
    assert(val and lower and upper, "not very useful error message here")
    if lower > upper then lower, upper = upper, lower end -- swap if boundaries supplied the wrong way
    return math.max(lower, math.min(upper, val))
end

function start()
	
end
fuse = 6

function onmessage(msg)
	if msg == "fuse" then
		fuse = fuse - 1
	end
	if fuse == 0 then
		parent:setPos(-1.3,0,0)
	end
	print("Fuses left until door: " .. fuse)
end

function onraycasthit(caster)
	
end