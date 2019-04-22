--parent is component's parent gameObject. It supports functions 

function deleteMannequins()
	gameObject.find("Enemies"):destroy()
end

function start()
	player = parent:getParent():getParent()
	player:removeComponent("lua")
	player:removeComponent("lua")
	waypoints = gameObject.find("AnimationPoints"):getChildren()
	wpCount = #waypoints
	target = waypoints[0]
	lookTarget = gameObject.find("AnimLookTarget")
	deleteMannequins()
	lookLerp = gameObject.new()
	local x,y,z = parent:getWorldPos()
	local fx,fy,fz = parent:forward()
	--lookLerp:setWorldPos(x + fx * 3,y + fy * 3,z + fz * 3)
	lookLerp:setPos(x + fx * 5,y + fy * 5,z + fz * 5)
	lookLerp:setRotationQ(1,0,0,0)
	lookLerp:setParent(nil)
	--lookLerp:addComponent("mesh","specular","13cube.obj","white.png","white.png","flat_n.dds")
	--lookLerp:removeComponent("mesh")
end

waypoint = 0

force = 400

function length(fx,fy,fz)
	return math.sqrt(math.pow(fx,2) + math.pow(fy,2) + math.pow(fz, 2))
end

function normalize(fx,fy,fz)
	local length = length(fx,fy,fz)
	return fx / length,fy / length,fz / length
end

function updateView()
	local rx,ry,rz = parent:forward()
	rotX = math.atan2(rx,rz)*180/3.14
	local tx,ty,tz = lookTarget:getWorldPos()
	local px,py,pz = parent:getWorldPos()
	targetRot = math.atan2(tx - px, tz - pz)*180/3.14
	d = (rotX - targetRot)--/steps
	zy,zz = normalize(ry,rz,0)
	if zz < 0 then
		zz = math.abs(zz)
	end
	rotVert = math.atan2(zy,math.abs(zz))*180/3.14
	--print(rotVert)
	--print(zz)
	
	--dummy object to follow:
	local lx,ly,lz = lookLerp:getWorldPos()
	local dx = tx-lx
	local dy = ty-ly
	local dz = tz-lz
	lookLerp:setWorldPos(lx+0.02*dx,ly+0.02*dy,lz+0.02*dz)
end

function fixedupdate()
	local px,py,pz = target:getWorldPos()
	tx,ty,tz = parent:getWorldPos()
	px,py,pz = normalize(px - tx,0,pz - tz)
	--print("Waypoint target: " .. waypoint)
	player:addForce(px * force,py * force,pz * force)
	
	updateView()
	if d ~= nil then
		d = d * 0.98
		--parent:setWorldRotation(0,1,0,targetRot + d)
		parent:lookAt(lookLerp:getWorldPos())
		--rotVert = rotVert * 0.99
		--parent:rotate(1,0,0,rotVert)
	end
end

function ontriggerenter(col)
	print("triggered")
	if waypoint == wpCount then
		lookTarget:sendMessage(1600)
		force = 0
		return
	end
	print(col)
	print(target)
	if col == target then
		waypoint = waypoint + 1
		target = waypoints[waypoint]
		print("CHANGING WAYPOINT!!!")
	
	end
	force = tonumber(parent:getName())
	if force == nil then
		force = 400
	end
end

function ondestroy()
	local menuMusic = gameObject.find("Music")
	if menuMusic ~= nil then
		menuMusic:destroy()
	end
end

function raycastresult(hit)
	print(hit:getName())
end