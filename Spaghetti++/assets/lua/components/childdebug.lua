door = nil

function math.Clamp(val, lower, upper)
    assert(val and lower and upper, "not very useful error message here")
    if lower > upper then lower, upper = upper, lower end -- swap if boundaries supplied the wrong way
    return math.max(lower, math.min(upper, val))
end

function start()
end
maxAngle = 100
angleS = 0
direction = 1
secs = 0.95
ctime = 0

timeToClose = 0
function fixedupdate()
	children = parent:getChildren()
	print("Children: " )
	for i = 0, #children do
		print(children[i]:getName())
	end
end

function onraycasthit(caster)

end