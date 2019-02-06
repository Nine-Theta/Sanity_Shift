--parent is component's parent gameObject. It supports functions 

function start()
	print("Initialised test lua component")
	--print(test.test())
end

function update() --currently disabled
--	print("Updated lua component") 
end

function spawnBullet()
	local bullet = gameObject:new()
	bullet:setName("Bullet")
	bullet:addComponent("sprite","glows.png")
	bullet:addComponent("trigger",8)
	bullet:addComponent("lua","bullet.lua")
	bullet:setPos(parent:getPos())
end

velY = 0
pressed = false
function fixedupdate()
	--print(parent.getPos())
	local x, y = parent:getPos()
	
	if keys.pressed(keys.down) then
		velY = velY + 10 * time.fixedDelta()
	end
	if keys.pressed(keys.up) then
		velY = velY - 10 * time.fixedDelta()
	end
	if keys.pressed(keys.space) then
		if not pressed then
			spawnBullet()
			pressed = true
		end
	else
		pressed = false
	end
	velY = velY * 0.98
	y = y + velY
	parent:setPos(x,y)
end
	
function ondestroy()

end

function oncollision(other)
	--print(other:getName())
end

function returnTest()
	return 3,5,7
end
