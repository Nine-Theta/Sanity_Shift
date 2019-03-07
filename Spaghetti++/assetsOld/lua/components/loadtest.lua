run = 0

function start()

end

function update()
	if run == 50 then
		obj = gameObject.new()
		obj:addComponent("lua","../scene.lua")
	end
	if run == 100 then
		obj:callFunction("init")
		print("Starting scene")
	end
	if run == 150 then
		parent:delete()
	end
	run = run + 1
end