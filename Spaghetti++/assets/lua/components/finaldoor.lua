door = nil

function math.Clamp(val, lower, upper)
    assert(val and lower and upper, "not very useful error message here")
    if lower > upper then lower, upper = upper, lower end -- swap if boundaries supplied the wrong way
    return math.max(lower, math.min(upper, val))
end

invertedSign = 1
function start()
	door = parent:getParent()
	parent:setDistanceLimit(35)
	door:setRotation(0,1,0,0)
	if string.find(parent:getName(),"inverse") then
		invertedSign = -1
	end
	print("DOOR INITIALISED")
end
maxAngle = 100
angleS = 0
direction = 1
secs = 1.55
ctime = 1

toPlaySound = false
active = true
timeToClose = 15
toggled = false
triggered = false

cam = nil
function fixedupdate()
	if not active then
		return
	end
	if ctime ~= 1 and not toggled then
		toggled = true
		--cam:sendMessage("follow")
		cam:removeComponent("lua")
		--cam:getParent():sendMessage("follow")
		cam:getParent():removeComponent("lua")
		cam:removeComponent("raycast")
		player = gameObject.find("Player")
		player:removeComponent("lua")
		player:removeComponent("lua")
		return
	end
	if ctime == 0 and not triggered then
		cam:addComponent("lua","animFollow.lua")
		--parent:removeComponent("lua")
		triggered = true
	end
	lastTime = timeToClose
	timeToClose = timeToClose - time.fixedDelta()
	if toPlaySound then
		if direction == -1 and ctime == 1 then
			parent:getParent():setSound("door_open.wav")
		elseif ctime == 0 then
			parent:getParent():setSound("door/metal_slam1.wav",0.01)
			--parent:getParent():setSound("moon.wav")
		end
		parent:getParent():playSound()
		toPlaySound = false
	end
	if timeToClose < 0 then
		direction = 1
		if lastTime > 0 then
			parent:getParent():setSound("door_close.wav")
			parent:getParent():playSound()
		end
	end
	ctime = math.Clamp(ctime + (time.fixedDelta() / secs) * direction,0,1)
	angleS = (1 - math.pow(ctime,4)) * maxAngle
	door:setRotation(0,1 * invertedSign,0,angleS)
	--print(door:getName())
	if angleS ~= 0 then
		--print("DOOR ACTIVE")
	end
end

function onraycasthit(caster)
	cam = caster
	if keys.down(keys.E) then
	print("Toggling door")
		--if direction == then
		--	angle = 90
		--else
		--	angle = 0
		--end
		
	if not active then
		parent:setSound("locked_door_rattle.wav")
		parent:playSound()
		return
	end
		parent:setSound("door_open.wav")
		direction = -direction
		if direction == -1 then
			timeToClose = math.random(32,40)
		end
		toPlaySound = true
	end
end

function ondestroy()
	print("FINAL Door destroyed!!")
end

function onmessage(msg)
	print(msg)
	if msg == "invert" then
		invertedSign = -invertedSign
	elseif msg == "open" then
		direction = -1
		timeToClose = math.random(50,70)
		toPlaySound = true
		print("Manually opening door")
	elseif msg == "close" then
		direction = 1
		--door:setRotation(0,1,0,0)
		--parent:setRotation(0,1,0,0)
		--direction = 1
		--ctime = 1
		--angleS = 0
		--toPlaySound = true
	--	parent:setWorldPos(1,1,1)
	--	active = false
		toPlaySound = true
		print("Closing door: " .. door:getName())
	elseif msg == "lock" then
		print("Locking door")
	--	parent:setWorldPos(1,1,1)
		active = false
	elseif msg == "unlock" then
		active = true
		print("Unlocking door")
	end
	if msg == "shut" then
		secs = 0.2
		direction = 1
		toPlaySound = true
		local timer = gameObject.new()
		parent:getParent():setKeepOnSoftDestroy(true)
		timer:addComponent("lua","endTimer.lua")
		timer:setParent(parent)
		timer:setPos(0,0,0)
	end
end