--parent is component's parent gameObject. It supports functions 

function start()
	parent:setPos(0,-0.4,-0.1)
	parent:setRotation(0,0,0,0)
end

endCount = 2.8
angle = 30
Tangle = -30
ty = -0.15
tz = 0.65
function fixedupdate()
	endCount = endCount - time.fixedDelta()
	if endCount - 0.25 < 0 then
		Tangle = 30
		ty = -0.4
		tz = -0.1
	end
	if endCount < 0 then
		parent:getParent():removeComponent("camera")
		endCount = 99999999
	end
	local px,py,pz = parent:getPos()
	py = py - (py - ty) * 0.03
	pz = pz - (pz - tz) * 0.03
	parent:setPos(0,py,pz)
	angle = angle - (angle - Tangle) * 0.02
	parent:setRotation(1,0,0,angle)
end