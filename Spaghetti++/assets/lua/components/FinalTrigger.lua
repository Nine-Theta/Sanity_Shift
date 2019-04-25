--parent is component's parent gameObject. It supports functions 

function start()
	finalDoor = gameObject.find("FinalDoor")
	mannequin = parent:getChildren()[0]
	mannequin:setActive(false)
end

function ontriggerenter(other)
	local name = other:getName()
	if name == "AnimLookTarget" then
		print("END SEQUENCE!")
		print(finalDoor)
		finalDoor:sendMessage("shut")
	end
end

function ontriggerexit(other)
	local name = other:getName()
	if name == "Player" then
		print("END SEQUENCE!")
		mannequin:setActive(true)
	end
end