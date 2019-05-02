
x,y,z = 0
function loadRandomFootstep()
	step = math.random(1,7)
	parent:setSound("steps" .. step .. ".wav")
	--parent:setSound("thomas.wav")
	--parent:playSound()
end
function start()
	x,y,z = parent:getPos()
	loadRandomFootstep()
end


nextStep = 0
playing = false
function fixedupdate()
	local nx,ny,nz = parent:getPos()
	local posSum = nx+ny+nz
	local lastPosSum = x+y+z
	nextStep = nextStep - time.fixedDelta()
	if nextStep < 0 then
		nextStep = 0.8 * math.random() + 1.3
		playing = false
	end
	if lastPosSum == posSum then
		parent:stopSound()
		playing = false
	elseif not playing then
		loadRandomFootstep()
		parent:playSound()
		playing = true
	end
	x,y,z = parent:getPos()
end
