--parent is component's parent gameObject. It supports functions 


function start()

buttonSelected = gameObject.find("PlayButtonA")
buttonIdle = gameObject.find("PlayButtonNA")

buttonIdle:setActive(false)

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
	--print("startbutton invoked")
	obj = gameObject.new()
	obj:setName("Loader")
	obj:addComponent("lua", "sceneloader.lua")
	obj:sendMessage("../scene.lua")
	
	--gameObject.find("Background"):destroy()
end
	
function fixedupdate()
	
end
	
function ondestroy()

end