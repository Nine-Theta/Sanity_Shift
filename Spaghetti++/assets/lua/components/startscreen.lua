--parent is component's parent gameObject. It supports functions 


function start()
	print("Initialised test lua component")
	--print(test.test())
end

function update() --currently disabled
--	print("Updated lua component") 
end

function initPlayer()
	local player = gameObject:new()
	player:addComponent("sprite","gecko.png")
	player:setName("Player")
	player:addComponent("lua","playercomp.lua")
	player:addComponent("collider",80)
end

function initBounds()
	local top = gameObject:new()
	top:addComponent("collider",0)
	top:setPos(0,512)
	local bottom = gameObject:new()
	bottom:addComponent("collider",0)
	bottom:setPos(0,-512)
end

function initSpawner()
	local spawner = gameObject:new()
	spawner:setName("spawner")
	spawner:addComponent("lua","enemyspawner.lua")
end
	
function fixedupdate()
	--print(parent.getPos())
	
	if keys.pressed(keys.space) then
		local bigScore = gameObject.find("BigScore")
		if bigScore ~= nullobject then
			bigScore:delete()
		end
	
		initPlayer()
		initBounds()
		initSpawner()
		local cam = gameObject.find("Camera")
		cam:setPos(250,0)
		
		parent:delete()
	end
	
	
end
	
function ondestroy()

end

function returnTest()
	return 3,5,7
end
