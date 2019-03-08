--parent is component's parent gameObject. It supports functions 

function start()
	--print("Initialised test lua component")
	--print(test.test())
	light = parent:getChildren()
	--also controls the flashlight now, so slightly misleading name but if it works...
end

rotation = 0
verticalSensitivity = 10 --default: 10
upperLimit = 45
lowerLimit = -45

enabled = true
function setActive(active)
	for i = 0,#light do
		light[i]:setActive(active)
	end
end

function fixedupdate()
	if mouse.buttonDown(1) then
		enabled = not enabled
	end
	if mouse.buttonPressed(0) then
		setActive(not enabled)
	else
		setActive(enabled)
	end
end

function ondestroy()

end