--parent is component's parent gameObject. It supports functions 


function update() --currently disabled
--	print("Updated lua component") 
end

function spawnLight()
obj4 = gameObject.new()
				obj4:setName("FakeFlashlight")
				obj4:setParent(parent:getParent())
				obj4:setPos(0,-0,0)
				--obj4:setRotationQ(0.9987355,-0.05006309,-0.0002160296,-0.004586249)
				--obj4:addComponent("lua","flashlightMove.lua")
					obj5 = gameObject.new()
					obj5:setName("flashlight")
					obj5:setParent(obj4)
					obj5:setPos(0.003000349,-1.104,0.09999967)
					obj5:setRotationQ(0.9988484,-0.04797821,0,-1.164153E-10)
					obj5:addComponent("mesh","glow","flashlight/flashlight.obj","flashlight/Diffuse.dds","flashlight/Specular.dds","flashlight/Normal.dds")
					obj5:addComponent("lua","lightControl.lua")
						obj6 = gameObject.new()
						obj6:setName("Light")
						obj6:setParent(obj5)
						obj6:setPos(-0.05600005,1.126381,0.1356813)
						obj6:setRotationQ(0.9959946,0.07501064,0.04827452,0.006141699)
						obj6:addComponent("pointlight","16.06")
						obj6 = gameObject.new()
						obj6:setName("Flashlight")
						obj6:setParent(obj5)
						obj6:setPos(-0.05600005,1.126381,0.1356813)
						obj6:setRotationQ(0.9971638,0.07522002,-2.175693E-06,0.00250293)
						obj6:addComponent("spotlight","40.32")
						obj6 = gameObject.new()
						obj6:setName("FlashLight_LQ")
						obj6:setParent(obj5)
						obj6:setPos(0,0,0)
						obj6:setRotationQ(1,0,0,0)
end

function start()
	print("Initialised test lua component")
	--print(test.test())
	offX,offY,offZ = parent:getPos()
	print(offY)
	player = parent
	--spawnLight()
	
--	parent:addComponent("lua","childdebug.lua")
end

seconds = 0
function fixedupdate()
	seconds = seconds + time.fixedDelta()
	local x = math.sin(seconds * 0.8) * 0.1
	local y = math.sin(seconds * 0.6) * 0.1
	
	
	parent:setRotation(0,1,0,x * 35)
	parent:rotate(1,0,0,y * 35)
	parent:setPos(x* 0.2+ offX,y * 0.2 + offY ,offZ)
	if keys.down(keys.E) then
		--print(parent:getParent())
		--obj4:setParent(parent:getParent())
		--print(parent:getName())
		--parent:setParent(nil)
		--print("Changed fake flashlight parent")
		--print(nullobject == parent:getParent())
		
	end
	--print(offY)
end
	
function ondestroy()

end

function oncollision(other)
	--print(other:getName())
end
