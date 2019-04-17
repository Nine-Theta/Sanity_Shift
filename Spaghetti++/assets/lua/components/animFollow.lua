--parent is component's parent gameObject. It supports functions 

function start()
	player = parent:getParent():getParent()
	player:removeComponent("lua")
	player:removeComponent("lua")
	waypoints = gameObject.find("AnimationPoints"):getChildren()
	wpCount = #waypoints
	target = waypoints[0]
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

function fixedupdate()
	local px,py,pz = target:getWorldPos()
	tx,ty,tz = parent:getWorldPos()
	px,py,pz = normalize(px - tx,0,pz - tz)
	--print("Waypoint target: " .. waypoint)
	player:addForce(px * force,py * force,pz * force)
end

function ontriggerenter(col)
	print("triggered")
	if waypoint == wpCount then
		return
	end
	print(col)
	print(target)
	if col == target then
		waypoint = waypoint + 1
		target = waypoints[waypoint]
		print("CHANGING WAYPOINT!!!")
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