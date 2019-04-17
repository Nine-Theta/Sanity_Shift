--parent is component's parent gameObject. It supports functions 

function start()
end

rotation = 0
verticalSensitivity = 10 --default: 10
upperLimit = 80
lowerLimit = -80

following = false
enabled = true
function update()
	
end
	
function fixedupdate()
	print("following anim")
end

function onmessage(msg)
end

function ondestroy()
	local menuMusic = gameObject.find("Music")
	if menuMusic ~= nil then
		menuMusic:destroy()
	end
end

function raycastresult(hit)
	print(hit:getName())
end