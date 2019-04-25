--parent is component's parent gameObject. It supports functions 

function ondestroy()
	print("Destroying player, starting end timer")
	local timer = gameObject.new()
	timer:addComponent("lua","endTimer.lua")
	--timer:setParent(parent)
	timer:setPos(0,0,0)
end
