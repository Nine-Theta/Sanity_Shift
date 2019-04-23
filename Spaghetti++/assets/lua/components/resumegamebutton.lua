--parent is component's parent gameObject. It supports functions 


function start()

buttonSelected = parent:getChildren()[0]
buttonIdle = parent:getChildren()[1]

--buttonSelected:setFluorEmission(0.65,0.3,0,1)
--buttonIdle:setFluorEmission(0.3,0.3,0.3,0.3)

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
	--print("Resumebutton invoked")
	time.settimescale(1)
	screen = gameObject.find("PauseScreen") 
	screen:callFunction("DeactivateAll")
	screen:setActive(false)
	mouse.setLock(true)
end
	
function fixedupdate()
end
	
function ondestroy()

end