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
		obj = gameObject.new()
		obj:addComponent("sound","battery_pickup.wav")
		obj:addComponent("lua","playdestroy.lua")
		obj:setWorldPos(parent:getWorldPos())
		parent:delete()
	end
end