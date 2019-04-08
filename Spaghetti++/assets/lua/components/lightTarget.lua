--parent is component's parent gameObject. It supports functions 

function start()
	target = gameObject.find("FlashlightTarget")
	light = parent:getChildren()[0]
	x,y,z = target:getWorldPos()
end

function fixedupdate()
	x,y,z = target:getWorldPos()
	light:lookAt(x,y,z)
end
