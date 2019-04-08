--parent is component's parent gameObject. It supports functions 

function start()

play = gameObject.find("PlayButton")
settings = gameObject.find("SettingsButton")
exitb = gameObject.find("ExitButton")

buttonArray = { settings, exitb }
buttonArray[0] = play
buttonCount = 3

selected = 0

buttonArray[selected]:callFunction("Selected")	
end

function update() --currently disabled

end

function UpdateSelection(change)
	buttonArray[selected]:callFunction("Deselected")
	selected = (selected + change) % buttonCount
	buttonArray[selected]:callFunction("Selected")	
end

function InvokeButton(button)
	buttonArray[button]:callFunction("Invoke")
end
	
function fixedupdate()

	if (keys.down(keys.Any)) then
		--play:callFunction("Invoke")
	end
		
	if (keys.down(keys.Down) or keys.down(keys.S)) then
		UpdateSelection(1)
	end
	
	if (keys.down(keys.Up) or keys.down(keys.W)) then
		UpdateSelection(-1)
	end
	
	if(keys.down(keys.Enter) or keys.down(keys.Space)) then
		InvokeButton(selected)
	end
	
	if(mouse.buttonDown(0)) then
		--util.raycast(gameObject.find("Player"), gameObject.find("MainCam"), mouse.relativePosition())
		end
		
	if(keys.down(keys.Numpad1)) then
		play:callFunction("Invoke")
		end
	if(keys.down(keys.Numpad2)) then
		settings:callFunction("Invoke")
		end	
	if(keys.down(keys.Numpad3)) then
		exitb:callFunction("Invoke")
		end	
end
	
function ondestroy()

end