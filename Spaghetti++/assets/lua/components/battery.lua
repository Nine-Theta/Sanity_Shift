function start()
	mesh = parent:getChildren()[0]
	light = gameObject.find("LightCharge")
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
		light:sendMessage("charge")
		parent:delete()
	end
end