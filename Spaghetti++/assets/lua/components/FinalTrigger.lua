--parent is component's parent gameObject. It supports functions 

function start()
	finalDoor = gameObject.find("FinalDoor")
end

function ontriggerenter(other)
	local name = other:getName()
	print("Player collided with " .. name)
	if name == "AnimLookTarget" then
		print("END SEQUENCE!")
		print(finalDoor)
		finalDoor:sendMessage("shut")
	end
end