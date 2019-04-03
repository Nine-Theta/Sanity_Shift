--parent is component's parent gameObject. It supports functions 



rotation = 0
verticalSensitivity = 10 --default: 10
upperLimit = 45
lowerLimit = -45

active = true
enabled = false

lastActive = true
function setActive(act)
	for i = 0,#light do
		light[i]:setActive(act)
	end
	if lastActive ~= act then
		if act then
			parent:setSound("flashlight/click_on.wav")
		else
			parent:setSound("flashlight/click_off.wav")
		end
		parent:playSound()
	end
	lastActive = act
end

function start()
	--print("Initialised test lua component")
	--print(test.test())
	light = parent:getChildren()
	--also controls the flashlight now, so slightly misleading name but if it works...
	setActive(false)
end

function fixedupdate()
	if not active then
		setActive(false)
		return
	end
	if mouse.buttonDown(1) then
		enabled = not enabled
	end
	if mouse.buttonPressed(0) then
		setActive(not enabled)
	else
		setActive(enabled)
	end
end

function onmessage(msg)
	if msg == "disabled" then
		active = false
	else
		active = true
	end
end