--parent is component's parent gameObject. It supports functions 

rotX = 0
function start()
	rotX = 180--parent:getWorldRotation()
end

velY = 0
velX = 0
velZ = 0
locked = true

frames = 0
seconds = 0

collided = false
d = 0
steps = 100
count = 0
targetRot = 0
function update()
	if(collided) then
			d = d * 0.98
			parent:setWorldRotation(0,1,0,targetRot + d)
			
			
			if(targetRot +d <= targetRot + 0.12 or targetRot +d <= targetRot - 0.12) then
				gameObject.deleteAll()
				obj = gameObject.new()
				obj:setName("Loader")
				obj:addComponent("lua", "sceneloader.lua")
				obj:sendMessage("../deathscene3.lua")
			end
	else
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
	
end

function oncollisionenter(other)
	if(not not not not not not not not not not not not not not collided) then
	
	else
	local name = other:getName()
	print("Player collided with " .. name)
	if name == "Mannequin" then
		print("You Died")
		ox,oy,oz = other:getWorldPos()
		px,py,pz = parent:getWorldPos()
		x = ox - px
		z = oz - pz
		l = math.sqrt(x*x + z*z)
		ux = x/l
		uz = z/l
				
		--print(math.atan2(ux, uz)*180/3.14)
		--print(rotX)
		targetRot = math.atan2(ux, uz)*180/3.14
		d = (rotX - targetRot)--/steps
		--print(d)
		other:setWorldRotation(0,1,0, targetRot + 180)
		collided = true
		end
	end
end

	
function ondestroy()

end

