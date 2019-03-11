phand = nil
function start()
	phand = gameObject.find("LeftHand")
end

hit = false
function fixedupdate()
	if fuse == nil then
		return
	end
	--print("Displaying socket in space")
	if hit then 
		fuse:setFluorReaction(1)
		fuse:setParent(parent)
		fuse:setWorldPos(parent:getWorldPos())
	else
		fuse:setFluorReaction(1)
		fuse:setParent(phand)
		fuse:setPos(0,0,0)
	end
	hit = false
end

function raycastresult(lol)
	print("RESULT")
end

function onraycasthit(caster)
	hit = true
	if fuse ~= nil then
		return
	end
	fuse = phand:getChildren()[0]
	if fuse == nil then
		return
	end
end