function start()
	print("RAYCAST TEST COMPONENT INITIALISED HERE!!")
end

function onraycasthit(caster)
	print("Test collider got hit by a raycast from " .. caster:getName())
end