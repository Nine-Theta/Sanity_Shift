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
		--[[d = d * 0.98
		parent:setWorldRotation(0,1,0,targetRot + d)
			
		if(targetRot +d <= targetRot + 0.5 or targetRot +d <= targetRot - 0.5) then
			commitmurder()
		end]]--
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

function commitmurder() --this isn't brave, what did I ever do to you?
	gameObject.deleteAll()
	obj = gameObject.new()
	obj:setName("Loader")
	obj:addComponent("lua", "sceneloader.lua")
	obj:sendMessage("../deathscene3.lua")
end

function dot(x1,y1,z1,x2,y2,z2)
	return x1*x2+y1*y2+z1*z2
end

function isBehind(self,target)
	local fx,fy,fz = self:forward()
	local px,py,pz = self:getWorldPos()
	local tx,ty,tz = target:getWorldPos()
	tx = px - tx
	ty = py - ty
	tz = pz - tz
	return dot(fx,fy,fz,tx,ty,tz) > 0
end

function killFromFront()
	parent:setKeepOnSoftDestroy(true)
	parent:getChildren()[0]:removeComponent("camera")
	parent:addComponent("lua","selfdestruct.lua")
	parent:setSound("death.wav")
	parent:playSound()
	gameObject.find("Heartbeat"):destroy()
	local children = parent:getChildren()[0]:getChildren()
	for i = 0, #children do
		children[i]:destroy()
	end
	parent:getChildren()[0]:stopSound(3)
	print("Killed player from front")
end

function killFromBack()
	parent:setKeepOnSoftDestroy(true)
	parent:getChildren()[0]:removeComponent("lua")
	parent:getChildren()[0]:removeComponent("raycast")
	parent:getParent():removeComponent("lua")
	parent:getParent():removeComponent("lua")
	parent:addComponent("lua","selfdestruct.lua")
	parent:setSound("death.wav")
	parent:playSound()
	gameObject.find("Heartbeat"):destroy()
	local children = parent:getChildren()[0]:getChildren()
	for i = 0, #children do
		--children[i]:destroy()
	end
	parent:getChildren()[0]:stopSound(3)
	parent:getChildren()[0]:removeComponent("raycast")
	local light = gameObject.find("Flashlight")
	light:removeComponent("lua")
	local claw = gameObject.new()
	claw:setName("Claw")
	claw:setParent(parent:getChildren()[0])
	claw:addComponent("lua","claw.lua")
	claw:setPos(0,0,0)
	claw:setRotation(1,0,0,0)
	claw:addComponent("mesh","specular","claw.obj","Mannequin/Diffuse.dds", "Mannequin/Specular.dds", "Mannequin/Normal.dds")
	--light:setParent(nil)
	--light:addComponent("boxcollider","0.11","0.17","0.11","1")
	print("Killed player from back")
end

function oncollisionenter(other)
	if(not collided) then
	local name = other:getName()
	print("Player collided with " .. name)
	if name == "Mannequin" then
		print("You Died")
		local behind = isBehind(parent,other)
		print("Enemy is behind player: " .. tostring(behind))
		if behind then
			killFromBack()
		else
			killFromFront()
		end
		other:destroy()
		collided = true
		parent:addComponent("lua","playerondestroy.lua")
		--[[ox,oy,oz = other:getWorldPos()
		px,py,pz = parent:getWorldPos()
		x = ox - px
		z = oz - pz
		l = math.sqrt(x*x + z*z)
		ux = x/l
		uz = z/l
				
		targetRot = math.atan2(ux, uz)*180/3.14
		
		if(targetRot <= rotX + 2 and targetRot >= rotX - 2) then
			commitmurder()
		end
		
		d = (rotX - targetRot)
		other:setWorldRotation(0,1,0, targetRot + 180)
		collided = true]]--
		end
	end
end

