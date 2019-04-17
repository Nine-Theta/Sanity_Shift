--parent is component's parent gameObject. It supports functions 


function start()
	objscene = gameObject.new()
	objscene:setName("scene")
	parent:setKeepOnSoftDestroy(true)
	loadscene()
	gameObject.deleteAll()
	
	
	local objback = gameObject.new()
		objback:setName("Background")
		objback:setPos(0,1.25,-2)	
		objback:addComponent("mesh","plane169test.obj","Loading.dds","black.dds","flat_n.png")
			local objbackback = gameObject.new()
			objbackback:setName("Floor")
			objbackback:setPos(0,0,1)
			objbackback:setRotation(1,0,0,-90)
			objbackback:addComponent("mesh", "plane20x20_2tris_aligned_uvs.obj", "black.dds","black.dds","flat_n.png")
			objbackback:setParent(objback)
end

function loadscene()
	objscene:addComponent("lua", sceneToLoad)
	once = 0
end

function onmessage(message)
	sceneToLoad = message
	print("loading:", sceneToLoad)
end

function update()
	once = once + 1
	if(once == 4) then	
		gameObject.deleteAll()
		parent:destroy()
		--once = 3
		local player = gameObject.find("Player")
		objscene:callFunction("init")
		if player ~= nil then
			player:destroy()
		end
	end
end
	
function ondestroy()

end