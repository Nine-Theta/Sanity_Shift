--parent is component's parent gameObject. It supports functions 

function start()
end

velY = 0
velX = 0
velZ = 0
pressed = false

rotX = 0
function update()

	if mouse.moved() then
		local mX, mY = mouse.delta()
		rotX = rotX -10*mX*time.fixedDelta()
		--print(mX, mY)
	end
	
	parent:setWorldRotation(0,1,0,rotX)
	if keys.down(keys.L) then
		mouse.toggleLock()
	end
end

function fixedupdateOLD()
	--print(parent.getPos())
	local x, y, z = parent:getPos()
	--print(x .. y .. z)
	local fx,fy,fz = parent:forward();
	local rx,ry,rz = parent:right();
	local ux,uy,uz = parent:up();
	if keys.pressed(keys.S) then
		velY = velY + 0.5 * time.fixedDelta()
	end
	if keys.pressed(keys.W) then
		velY = velY - 0.5 * time.fixedDelta()
	end
	if keys.pressed(keys.D) then
		velX = velX - 0.5 * time.fixedDelta()
		end
	if keys.pressed(keys.A) then
		velX = velX + 0.5 * time.fixedDelta()
	end
	
	if keys.pressed(keys.Space) then
		velZ = velZ + 0.5 * time.fixedDelta()
	end
	
	if keys.pressed(keys.LeftControl) then
		velZ = velZ - 0.5 * time.fixedDelta()
	end
	
	if keys.pressed(keys.LeftShift) then
		velY = velY * 1.04
		velX = velX * 1.04
		velZ = velZ * 1.04
	end
	
	
	velY = velY * 0.95
	velX = velX * 0.95
	velZ = velZ * 0.95
	z = z + fz * velY + rz * velX + uz * velZ
	x = x + fx * velY + rx * velX + ux * velZ
	y = y + fy * velY + ry * velX + uy * velZ
	parent:setPos(x,y,z)
end
	
function ondestroy()

end

