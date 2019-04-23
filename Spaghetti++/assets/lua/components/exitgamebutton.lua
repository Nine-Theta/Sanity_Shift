--parent is component's parent gameObject. It supports functions 


function start()
buttonSelected = parent:getChildren()[0]
buttonIdle = parent:getChildren()[1]

buttonSelected:setActive(false)
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
	util.exitGame()
	--print("TODO: close game")
end
	
function fixedupdate()
	--util.raycast(gameObject.find("Player"), gameObject.find("MainCam"))
end
	
function ondestroy()

end