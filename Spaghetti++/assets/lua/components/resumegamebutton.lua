--parent is component's parent gameObject. It supports functions 


function start()

end

function update() --currently disabled

end

function onraycasthit(caster)
	print("raycast hit!")
	local children = parent:getChildren()
	print("Parent component has " .. #children .. " children")
	for i = 0, #children do --actualcode
		print(children[i])
	end
	print("Test collider got hit by a raycast from " .. caster:getName())
	Invoke()
end

function Selected()
	parent:removeComponent("mesh")
	parent:addComponent("mesh","ResumeGameTestSelect.obj","brown.dds","white_s.png","flat_n.png")
	--print("ResumeGameButton Selected")
end

function Deselected()
	parent:removeComponent("mesh")
	parent:addComponent("mesh","ResumeGameTest.obj","lightGray.dds","white_s.png","flat_n.png")
	--print("ResumeGameButton Deselected")
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