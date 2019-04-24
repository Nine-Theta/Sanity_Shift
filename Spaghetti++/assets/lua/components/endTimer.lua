--parent is component's parent gameObject. It supports functions 

function start()
	finalDoor = gameObject.find("FinalDoor")
	player = gameObject.find("Player")
	--player:setKeepOnSoftDestroy(true)
	parent:setKeepOnSoftDestroy(true)
end
darkCount = 0.34
endCount = 4
function fixedupdate()
	darkCount = darkCount - time.fixedDelta()
	endCount = endCount - time.fixedDelta()
	if darkCount < 0 then
		gameObject.deleteAll()
		if finalDoor ~= nil then
			finalDoor:removeComponent("mesh")
		end
		darkCount = 999
	end
	if endCount < 0 then
		endCount = 2
		obj = gameObject.new()
		obj:setName("Loader")
		obj:addComponent("lua", "sceneloader.lua")
		obj:sendMessage("../startscene.lua")
		local p = parent:getParent()
		if p ~= nil then
			print(p)
			local p2 = p:getParent()
			print(p2)
			if p2 ~= nil then 
				p2:destroy()
			end
		end
			
		parent:destroy()
		if player ~= nil then
			player:destroy()
		end
		print("FINAL TIMER DESTROYED THE WHOLE SCENE!! DOING SELF-DESTRUCT")
	end
end