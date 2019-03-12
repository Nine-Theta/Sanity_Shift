function start()
	mesh = parent:getChildren()[0]
	phand = gameObject.find("LeftHand")
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
	--print("RESULT")
end

function onraycasthit(caster)
	hit = true
	--print("FUSE")
	if keys.down(keys.E) then
		if phand:getChildren()[0] ~= nil then
			return
		end
		print("Attaching a fuse to player hand")
		parent:removeComponent("boxcollider")
		parent:setParent(phand)
		parent:setPos(0,0,0)
		print("Attached fuse to player hand!")
	end
end