--parent is component's parent gameObject. It supports functions 

function start()
	finalDoor = parent:getParent()
	player = gameObject.find("Player")
	--player:setKeepOnSoftDestroy(true)
end
darkCount = 0.34
endCount = 4
function fixedupdate()
	darkCount = darkCount - time.fixedDelta()
	endCount = endCount - time.fixedDelta()
	if darkCount < 0 then
		gameObject.deleteAll()
		finalDoor:removeComponent("mesh")
		darkCount = 999
	end
	if endCount < 0 then
		obj = gameObject.new()
		obj:setName("Loader")
		obj:addComponent("lua", "sceneloader.lua")
		obj:sendMessage("../startscene.lua")
		parent:getParent():getParent():destroy()
		player:destroy()
	end
end