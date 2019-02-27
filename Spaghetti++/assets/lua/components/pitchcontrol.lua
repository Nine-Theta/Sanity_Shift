--parent is component's parent gameObject. It supports functions 

function start()
	--print("Initialised test lua component")
	--print(test.test())
	light = gameObject.find("Flashlight") 
	--also controls the flashlight now, so slightly misleading name but if it works...
end

enabled = true
function update()

	if mouse.moved() then
		local mX, mY = mouse.delta()
		parent:rotate(1,0,0, mY * 10 * time.fixedDelta())
		--print(mX, mY)
	end
	
end
	
function fixedupdate()
	if mouse.buttonDown(1) then
		enabled = not enabled
	end
	if mouse.buttonPressed(0) then
		light:setActive(not enabled)
	else
		light:setActive(enabled)
	end
end

function ondestroy()

end