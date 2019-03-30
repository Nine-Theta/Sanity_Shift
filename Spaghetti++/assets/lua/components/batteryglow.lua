--parent is component's parent gameObject. It supports functions 

function start()
	children = parent:getChildren()
	light = gameObject.find("flashlight"):getChildren()[0]
end

startseconds = 180
seconds = startseconds

flashCount = 0

function reset()
	seconds = startseconds
	flashCount = 0
	light:getParent():sendMessage("enabled")
end

function fixedupdate()
	if light:isActive() then
		seconds = seconds - time.fixedDelta()
	end
	
	local coeff = seconds / startseconds
	parent:setFluorEmission((1 - (coeff * 1.2 - 0.2)) * 2,(coeff * 1.2 - 0.2) * 2,0,2)
	
	
	for i = 0, #children do
		if (i) / (#children + 1) < coeff then
			children[#children - i]:setActive(true)
		else
			children[#children - i]:setActive(false)
		end
		children[i]:setFluorEmission(1 - coeff,coeff,0,2)
	end
	
	childPercent = 1 / (#children + 1)
	flashCount = flashCount + time.fixedDelta()
	if childPercent > coeff and coeff > 0 then
		if flashCount % 1 > 0.5 then
			children[#children]:setActive(false)
		else
			children[#children]:setActive(true)
		end
	end
	
	if coeff < 0 then
		light:getParent():sendMessage("disabled")
	end
end
	
function onmessage(msg)
	if msg == "charge" then
		reset()
	end
end

function oncollision(other)
	--print(other:getName())
end
