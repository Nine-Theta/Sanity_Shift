phand = nil
function start()
	phand = gameObject.find("LeftHand")
	dlight = gameObject.find("fuseLight" .. parent:getName())
	dlight:setActive(false)
	dlamp = dlight:getParent()
	door = gameObject.find("ChapelDoorLocked")
	door:sendMessage("invert")
	door:sendMessage("lock")
	dlamp:setFluorEmission(0.9,0.9,0.6,0)
	--door:removeComponent("lua")
end

hit = false
holdingfuse = false
function fixedupdate()
	--	print(parent:getWorldPos())
	if fuse == nil then
		return
	end
	if hit then 
		--fuse:setParent(parent)
		fuse:setWorldPos(parent:getWorldPos())
		fuse:setRotationQ(1,0,0,0)
		fuse:getChildren()[0]:setFluorReaction(1)
		if keys.down(keys.E) then
			fuse:getChildren()[0]:setFluorReaction(0)
			fuse:setParent(parent)
			if not holdingfuse then
				holdingfuse = true
				fuse:setSound("plug_in.wav")
				fuse:playSound()
				fuse = nil
				dlight:setActive(true)
				dlamp:setFluorEmission(0.9,0.9,0.6,2)
				--door:addComponent("lua","door.lua")
				door:sendMessage("unlock")
				door:sendMessage("open")
			else
				holdingfuse = false
				fuse:setSound("plug_in.wav")
				fuse:playSound()
				fuse:setParent(phand)
				fuse:setPos(0,0,0)
				fuse = nil
				dlight:setActive(false)
				dlamp:setFluorEmission(0,0,0,0)
				door:sendMessage("close")
				door:sendMessage("lock")
			--	door:removeComponent("lua")
				--door:getParent():setRotationQ(1,0,0,0)
			end
			--parent:removeComponent("boxcollider")
		end
	else
		fuse:getChildren()[0]:setFluorReaction(0)
		if not holdingfuse then
			fuse:setParent(phand)
			fuse:setPos(0,0,0)
		end
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
	if fuse == nil and not holdingfuse then
		fuse = phand:getChildren()[0]
		--hit = false
		return
	end
	if fuse == nil and holdingfuse then
		local children = parent:getChildren()
		local lchildren = phand:getChildren()[0]
		--print("Player is holding objects: ")
		--print(lchildren)
		if lchildren ~= nil then 
			hit = false
			return
		end
		fuse = children[#children]
	end
end