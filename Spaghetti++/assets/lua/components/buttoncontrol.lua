--parent is component's parent gameObject. It supports functions 


function start()

play = gameObject.find("PlayButton")
settings = gameObject.find("SettingsButton")
exitb = gameObject.find("ExitButton")

end

function update() --currently disabled

end
	
function fixedupdate()

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