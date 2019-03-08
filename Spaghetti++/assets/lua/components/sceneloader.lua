--parent is component's parent gameObject. It supports functions 


function start()
	objscene = gameObject.new()
	objscene:setName("scene")
	loadscene()
end

function loadscene()
	objscene:addComponent("lua", sceneToLoad)
	once = true
end

function onmessage(message)
	sceneToLoad = message
	print("loading:", sceneToLoad)
end

function fixedupdate()
	if(once) then
		objscene:callFunction("init")		
		once = false
	end
end
	
function ondestroy()

end