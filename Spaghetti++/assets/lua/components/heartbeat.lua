
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


nextStep = 0
playing = false
function fixedupdate()
	nextStep = nextStep - time.fixedDelta()
	if nextStep < 0 then
		nextStep = 0.12 * math.random() + 1.4
		playing = false
	end
	if not playing then
		parent:playSound()
		playing = true
	end
	x,y,z = parent:getPos()
end
