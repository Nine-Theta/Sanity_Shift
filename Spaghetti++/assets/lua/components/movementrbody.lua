--parent is component's parent gameObject. It supports functions 

function start()
	print("Initialised test lua component")
	--print(test.test())
	cam = gameObject.find("PlayerFeet")
end

--[[function update() --currently disabled
--	print("Updated lua component") 
end]]--

velY = 0
velX = 0
velZ = 0
pressed = false

force = 800
function fixedupdate()
	--print(parent.getPos())
	--print(x .. y .. z)
	local fx,fy,fz = cam:forward();
	local rx,ry,rz = cam:right();
	local ux,uy,uz = cam:up();
	
	x = 0
	y = 0
	z = 0
	if keys.pressed(keys.S) then
		x = x + force * fx
		y = y + force * fy
		z = z + force * fz
	end
	if keys.pressed(keys.W) then
		x = x + force * -fx
		y = y + force * -fy
		z = z + force * -fz
	end
	if keys.pressed(keys.D) then
		x = x + force * -rx
		y = y + force * -ry
		z = z + force * -rz
		end
	if keys.pressed(keys.A) then
		x = x + force * rx
		y = y + force * ry
		z = z + force * rz
	end
	
	if keys.pressed(keys.Space) then
		--velZ = velZ + 0.5 * time.fixedDelta()
	end
	
	if keys.pressed(keys.LeftControl) then
		--velZ = velZ - 0.5 * time.fixedDelta()
	end
	
	if keys.pressed(keys.LeftShift) then
		force = 1200
	else
		force = 800
	end
	
	parent:addForce(x,y,z)
end
	
function ondestroy()

end