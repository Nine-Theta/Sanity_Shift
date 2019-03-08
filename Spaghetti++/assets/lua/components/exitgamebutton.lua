--parent is component's parent gameObject. It supports functions 


function start()

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

function Invoke()
	
	--gameObject.deleteAll()
	print("TODO: close game")
end
	
function fixedupdate()
	--util.raycast(gameObject.find("Player"), gameObject.find("MainCam"))
end
	
function ondestroy()

end