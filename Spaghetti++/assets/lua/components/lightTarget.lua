--parent is component's parent gameObject. It supports functions 

function start()
	target = gameObject.find("FlashlightTarget")
	light = parent:getChildren()[0]
	x,y,z = target:getWorldPos()
end

function fixedupdate()
	x,y,z = target:getWorldPos()
	--x = x - (x - x2) * 0.4
	--y = y - (y - y2) * 0.4
	--z = z - (z - z2) * 0.4
	light:lookAt(x,y,z)
end
