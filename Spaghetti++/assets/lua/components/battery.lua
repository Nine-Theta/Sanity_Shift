function start()
	mesh = parent:getChildren()[0]
end
hit = false
function fixedupdate()
	if hit then 
		mesh:setFluorReaction(1)
	else
		mesh:setFluorReaction(0)
	end
	hit = false
end

function raycastresult(lol)
	print("RESULT")
end

function onraycasthit(caster)
	hit = true
	if keys.down(keys.E) then
		print("Deleting battery!")
		parent:delete()
	end
end