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
	parent:addComponent("mesh","SettingsTestSelect.obj","brown.dds","white_s.png","flat_n.png")
	print("Settings Selected")
end

function Deselected()
	parent:removeComponent("mesh")
	parent:addComponent("mesh","SettingsTest.obj","lightGray.dds","white_s.png","flat_n.png")
	print("Settings Deselected")
end

function Invoke()
	print("settings invoked")

end
	
function fixedupdate()
	
end
	
function ondestroy()

end