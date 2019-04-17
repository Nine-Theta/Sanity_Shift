--parent is component's parent gameObject. It supports functions 

function start()
	--print(test.test())
end

--[[function update() --currently disabled
--	print("Updated lua component") 
end]]--

accz = -0.005
velz = 0

function fixedupdate()
	--print(parent.getPos())
	local x, y, z = parent:getPos()
	
	velz = velz + accz
	z = z + velz
	
	parent:setPos(x,y,z)
end
	
function ondestroy()

end

function oncollision(other)
	--print(other:getName())
	if other:getName() == "Player" then
		--audio.play("PlayerDeathSound.wav")
	end
end

function returnTest()
	return 3,5,7
end
