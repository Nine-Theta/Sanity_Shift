--parent is component's parent gameObject. It supports functions 

function start()
	--x,y,z = parent:getPos()
end

velY = 0
velX = 0
velZ = 0
locked = true

rotX = 0
frames = 0
seconds = 0
function update()

	if mouse.moved() and locked then
		local mX, mY = mouse.delta()
		rotX = rotX -10*mX*time.fixedDelta()
		--print(mX, mY)
	end
	--frames = frames + 1
	--seconds = seconds + time.deltaTime()
	
	--if seconds > 1 then
	--	print(frames)
	--	frames = 0
	--	seconds = seconds - 1
	--end
	parent:setWorldRotation(0,1,0,rotX)
	if keys.down(keys.L) then
		mouse.toggleLock()
		locked = not locked		
	end
	--parent:setPos(x,y,z)
	
	
end

	
function ondestroy()

end

