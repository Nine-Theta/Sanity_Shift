--parent is component's parent gameObject. It supports functions 


function start()
buttonSelected = gameObject.find("ExitButtonA")
buttonIdle = gameObject.find("ExitButtonNA")

buttonSelected:setActive(false)
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
	print("TODO: close game")
end

function Deselected()
	buttonSelected:setActive(false)
	buttonIdle:setActive(true)
	print("TODO: close game2")
end

function Invoke()
	util.exitGame()
	--print("TODO: close game")
end
	
function fixedupdate()
	--util.raycast(gameObject.find("Player"), gameObject.find("MainCam"))
end
	
function ondestroy()

end