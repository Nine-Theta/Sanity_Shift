--parent is component's parent gameObject. It supports functions 


function start()

end

function update() --currently disabled

end

function Selected()
	parent:removeComponent("mesh")
	parent:addComponent("mesh","QuitToMenuTestSelect.obj","brown.dds","white_s.png","flat_n.png")
	print("ExitToMenuButton Selected")
end

function Deselected()
	parent:removeComponent("mesh")
	parent:addComponent("mesh","QuitToMenuTest.obj","lightGray.dds","white_s.png","flat_n.png")
	print("ExitToMenuButton Deselected")
end

function Invoke()
	print("ExitToMenuButton Invoked")
	time.settimescale(1)
	gameObject.deleteAll()
	obj = gameObject.new()
	obj:setName("Loader")
	obj:addComponent("lua", "sceneloader.lua")
	obj:sendMessage("../startscene.lua")
end
	
function fixedupdate()
	
end
	
function ondestroy()

end