--parent is component's parent gameObject. It supports functions 


function start()

buttonSelected = gameObject.find("ExitMenuButtonA")
buttonIdle = gameObject.find("ExitMenuButtonNA")

buttonSelected:setActive(false)

end

function update() --currently disabled

end

function Selected()
	buttonSelected:setActive(true)
	buttonIdle:setActive(false)
end

function Deselected()
	buttonSelected:setActive(false)
	buttonIdle:setActive(true)
end

function Invoke()
	--print("ExitToMenuButton Invoked")
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