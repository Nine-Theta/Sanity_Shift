--parent is component's parent gameObject. It supports functions 

function start()
	print("Initialised test lua component")
	--print(test.test())
end

function update() --currently disabled
--	print("Updated lua component") 
end

velY = 0
pressed = false
function fixedupdate()
	--print(parent.getPos())
	local x, y, z = parent:getPos()
	--print(x .. y .. z)
	if keys.pressed(keys.down) then
		velY = velY + 10 * time.fixedDelta()
	end
	if keys.pressed(keys.up) then
		velY = velY - 10 * time.fixedDelta()
	end
	velY = velY * 0.98
	y = y + velY * 0.05
	parent:setPos(x,y,z)
end
	
function ondestroy()

end

function oncollision(other)
	--print(other:getName())
	if other:getName() == "Enemy" then
		audio.play("PlayerDeathSound.wav")
		local score = gameObject.find("score")
		score:sendMessage("endGame")
	end
end

function returnTest()
	return 3,5,7
end
