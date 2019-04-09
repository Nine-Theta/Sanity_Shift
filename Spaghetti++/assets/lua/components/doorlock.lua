function start()
	wheels = parent:getChildren()
	doors = parent:getParent():getChildren()
	for i = 0, #doors do
		if doors[i] ~= parent then
			--doors[i]:removeComponent("lua")
			doors[i]:getChildren()[0]:getChildren()[0]:sendMessage("lock")
		end
	end
	code = parent:getName()
end

function updateNumbers()
	local n1 = wheels[2]:getName()
	local n2 = wheels[1]:getName()
	local n3 = wheels[0]:getName()
	number = n1 .. n2 .. n3
	
	if number == code then
		--wheels[0]:removeComponent("spherecollider")
		--wheels[1]:removeComponent("spherecollider")
		--wheels[2]:removeComponent("spherecollider")
	end
end
active = true

function fixedupdate()
	if not active then
		return
	end
	updateNumbers()
	--print(number .. " - " .. code)
	if number == code then
		print("CODE LOCK SUCCESSFULLY COMPLETED!")
		--parent:setParent(nil)
		parent:addComponent("boxcollider","0.19","0.09","0.04","1")
		for i = 0, #doors do
			if doors[i] ~= parent then
			--doors[i]:removeComponent("lua")
				doors[i]:getChildren()[0]:getChildren()[0]:sendMessage("unlock")
			end
		end
		--parent:removeComponent("lua")
		active = false
	end
end

function raycastresult(lol)
	print("RESULT")
end
collisions = 0
played = false
function oncollisionenter(collider)
	collisions = collisions + 1
	if not (string.find(collider:getName(),"Door") or string.find(collider:getName(),"default")) and not played then
		parent:setSound("lock_drop1.wav")
		parent:playSound()
		played = true
	end
	print("Lock dropped onto: " .. collider:getName())
end

function onraycasthit(caster)
	hit = true
	if keys.down(keys.E) then
		print("Turning Lock Wheel!")
		loadRandomTick()
		rotationT = (rotationT + (360 / rotationSteps))
	end
end