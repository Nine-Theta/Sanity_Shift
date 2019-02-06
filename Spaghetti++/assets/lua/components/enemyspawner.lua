--parent is component's parent gameObject. It supports functions 


function spawnEnemy()
	local enemy = gameObject:new()
	enemy:addComponent("sprite","enemy.png")
	enemy:addComponent("collider",40)
	enemy:addComponent("lua","enemy.lua")
	enemy:setPos(1200,math.random(-300,300))
end

function update() --currently disabled
--	print("Updated lua component") 
end
 timer = math.random(1,5)
 
function fixedupdate()
	--print(parent.getPos())
	timer = timer - time.fixedDelta()
	
	if timer < 0 then
		timer = math.random(1,5) * 0.5
		spawnEnemy()
	end
end

