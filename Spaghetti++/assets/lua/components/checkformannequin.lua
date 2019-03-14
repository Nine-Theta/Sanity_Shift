--parent is component's parent gameObject. It supports functions 

function start()
	parent:setName("Enemy")
end
speed = math.random(150,350)
function update() --currently disabled
--	print("Updated lua component") 
end

function fixedupdate()
	--print(parent.getPos())
	local x,y = parent:getPos()
	parent:setPos(x - speed * time:fixedDelta(),y)
	if x < -400 then
		parent:delete()
	end
end

function onmessage(message)
	print(parent:getName() .. " received a message: ")
	print(message)
end

function oncollision(other)
	local name = other:getName()
	if name == "Bullet" then
		local score = gameObject.find("score")
		score:sendMessage(25)
		audio.play("PlayerDeathSound.wav")
		parent:delete()
	end
end