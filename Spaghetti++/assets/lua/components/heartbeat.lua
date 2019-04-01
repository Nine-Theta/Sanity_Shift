
x,y,z = 0
function loadRandomFootstep()
	step = math.random(1,10)
	parent:setSound("steps" .. step .. ".wav")
	--parent:setSound("thomas.wav")
	--parent:playSound()
end
function start()
	x,y,z = parent:getPos()
	parent:addComponent("sound","player/normal_heartbeat_one.wav")
	print("INITIALISED HEARTBEAT")
	parent:playSound()
end

function length(x,y,z)
	return math.sqrt(math.pow(x,2) + math.pow(y,2) + math.pow(z,2))
end

maxRad = 10
closestT = maxRad
closest = 5
nextStep = 0
maxTime = 1.4
minTime = 0.5
playing = false
function fixedupdate()
	nextStep = nextStep - time.fixedDelta()
	closest = (closestT - closest) * 0.002 + closest
	coeffOld = coeff
	coeff = closest / maxRad
	--print(coeff)
	--if coeff > 0.15 and coeffOld <= 0.15 then
	--	parent:setSound("player/normal_heartbeat_one.wav")
	--elseif coeff < 0.15 and coeffOld >= 0.15 then
	--	parent:setSound("player/fast_heartbeat_one.wav")	--swap out for faster effect
	--end													--disabled, sounded bad
	coeff2 = math.min(math.max(coeff * 2, 0), 1)
	if nextStep < 0 then
		nextStep = 0.12 * math.random() + (coeff2 * maxTime) + ((1 - coeff2) * minTime)
		playing = false
	end
	if not playing then
		parent:setVolume(1 - coeff)
		parent:playSound()
		playing = true
	end
	x,y,z = parent:getPos()
	closestT = maxRad
end

function ontriggerstay(obj)
	if obj:getName() ~= "default" then
		return
	end
	x,y,z = parent:getWorldPos()
	x2,y2,z2 = obj:getWorldPos()
	closestT = math.min(length(x-x2,y-y2,z-z2) - 3,closestT)
end