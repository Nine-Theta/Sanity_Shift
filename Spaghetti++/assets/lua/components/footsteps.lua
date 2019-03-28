
x,y,z = 0
function loadRandomFootstep()
	step = math.random(1,10)
	parent:setSound("player/step" .. step .. ".wav")
	--parent:setSound("thomas.wav")
	--parent:playSound()
end
function start()
	x,y,z = parent:getPos()
	parent:addComponent("sound","player/step1.wav")
	print("INITIALISED FOOTTEPS")
	--parent:playSound()
end

function length(lx,ly,lz)
	return math.sqrt(math.pow(lx,2) + math.pow(ly,2) + math.pow(lz,2))
end

dist = 1
playing = false
function fixedupdate()
	local posX,posY,posZ = parent:getWorldPos()
	local lengthStep = length(posX- x,posY - y,posZ - z)
	x = posX
	y = posY
	z = posZ
	dist = dist - lengthStep
	if dist < 0 then
		dist = 0.15 * math.random() + 1.5
		loadRandomFootstep()
		parent:playSound()
	end
end
