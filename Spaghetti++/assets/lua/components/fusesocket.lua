phand = nil
function start()
	phand = gameObject.find("LeftHand")
	dlight = gameObject.find("fuseLight" .. parent:getName())
	dlight:setActive(false)
	dlamp = dlight:getParent()
	door = gameObject.find("movable_right")
end

hit = false
function fixedupdate()
	--	print(parent:getWorldPos())
	if fuse == nil then
		return
	end
	if hit then 
		fuse:getChildren()[0]:setFluorReaction(1)
		fuse:setParent(parent)
		fuse:setPos(0,0,0)
		fuse:setRotationQ(1,0,0,0)
		if keys.down(keys.E) then
			fuse:getChildren()[0]:setFluorReaction(0)
			fuse:setSound("plug_in.wav")
			fuse:playSound()
			fuse = nil
			dlight:setActive(true)
			dlamp:setFluorEmission(0.9,0.9,0.6,2)
			parent:removeComponent("boxcollider")
			door:sendMessage("fuse")
		end
	else
		fuse:getChildren()[0]:setFluorReaction(0)
		fuse:setParent(phand)
		fuse:setPos(0,0,0)
		fuse = nil
	end
	hit = false
end

function raycastresult(lol)
	print("RESULT")
end

function onraycasthit(caster)
	hit = true
	--print("FUSESOCKET")
	if fuse == nil then
		fuse = phand:getChildren()[0]
		--hit = false
		return
	end
end