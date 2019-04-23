--parent is component's parent gameObject. It supports functions
--this is pausecontrol to major Tom

function start()
screen = gameObject.find("PauseScreen") 

resume = gameObject.find("ResumeButton")
settings = gameObject.find("PauseSettingsButton")
exitmenu = gameObject.find("ExitToMenuButton")
exitdesk = gameObject.find("ExitToDeskButton")

buttonArray = parent:getChildren()
resume = buttonArray[0]
settings = buttonArray[1]
exitmenu = buttonArray[2]
exitdesk = buttonArray[3]
buttonCount = 4

selected = 0

buttonArray[selected]:callFunction("Selected")

active = false
end

function UpdateSelection(change)
	buttonArray[selected]:callFunction("Deselected")
	selected = (selected + change) % buttonCount
	buttonArray[selected]:callFunction("Selected")	
end

function InvokeButton(button)
	buttonArray[button]:callFunction("Invoke")
end

function SetActiveAll(set)
	for i = buttonCount-1, 0, -1
	do
		buttonArray[i]:setActive(set)
	end
	
	active = set

end

function DeactivateAll()
	for i = buttonCount-1, 0, -1
	do
		buttonArray[i]:setActive(false)
	end
	
	active = false

end

function fixedupdate()
	if keys.down(keys.P) or keys.down(keys.Escape) then
		if time.gettimescale() > 0.8 then
		time.settimescale(0)
		screen:setActive(true)
		SetActiveAll(true)
		--mouse.setLock(false)
		else		
		time.settimescale(1)
		screen:setActive(false)
		SetActiveAll(false)
		--mouse.setLock(true)
		end
	end
		
	if(active)then
	
		if (keys.down(keys.Down) or keys.down(keys.S)) then
			UpdateSelection(1)
		end
	
		if (keys.down(keys.Up) or keys.down(keys.W)) then
			UpdateSelection(-1)
		end
	
		if(keys.down(keys.Enter) or keys.down(keys.Space)) then
			InvokeButton(selected)
		end
	
		if keys.down(keys.Num1) then
			time.settimescale(1)
		end	
		if keys.down(keys.Num2) then
			time.settimescale(2)
		end		
		if keys.down(keys.Num3) then
			time.settimescale(10.0)
		end
		if keys.down(keys.Num4) then
			time.settimescale(0.25)
		end		
		if keys.down(keys.Num5) then
			time.settimescale(64)
		end	
	end
end
	
function ondestroy()

end


