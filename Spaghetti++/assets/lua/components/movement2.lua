--parent is component's parent gameObject. It supports functions 

function start()
	print("Initialised test lua component")
	--print(test.test())
end

--[[function update() --currently disabled
--	print("Updated lua component") 
end]]--

velY = 0
velX = 0
velZ = 0
pressed = false

function update()

	if mouse.moved() then
		local mX, mY = mouse.delta()
		parent:rotate(0,1,0,-mX * 10 * time.fixedDelta())
		--print(mX, mY)
	end
end

function fixedupdate()
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
	
	if keys.down(keys.L) then
		mouse.toggleLock()
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

function oncollision(other)
	--print(other:getName())
	if other:getName() == "Enemy" then
		audio.play("PlayerDeathSound.wav")
		local score = gameObject.find("score")
		score:sendMessage("endGame")
	end
end

function returnTest()
	return 3,5,7
end
