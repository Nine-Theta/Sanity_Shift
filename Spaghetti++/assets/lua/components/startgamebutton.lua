--parent is component's parent gameObject. It supports functions 


function start()

buttonSelected = gameObject.find("PlayButtonA")
buttonIdle = gameObject.find("PlayButtonNA")

buttonIdle:setActive(false)

end

function update() --currently disabled

end

function onraycasthit(caster)
	print("raycast hit!")
	local children = parent:getChildren()
	print("Parent component has " .. #children .. " children")
	for i = 0, #children do --actualcode
		print(children[i])
	end
	print("Test collider got hit by a raycast from " .. caster:getName())
	Invoke()
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
	gameObject.deleteAll()
	obj = gameObject.new()
	obj:setName("Loader")
	obj:addComponent("lua", "sceneloader.lua")
	obj:sendMessage("../scene.lua")
end
	
function fixedupdate()
	
end
	
function ondestroy()

end