run = 0

function start()
	door = parent:getParent():getParent()
	obj = gameObject.new()
	obj:addComponent("lua","../scene.lua")
end

function update()
	if run > 100 then
		obj:callFunction("init")
		parent:delete()
	end
	run = run + 1
end