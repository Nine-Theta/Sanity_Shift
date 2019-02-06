--parent is component's parent gameObject. It supports functions 

function start()
	parent:setName("Bullet")
end

function update() --currently disabled
--	print("Updated lua component") 
end

function fixedupdate()
	--print(parent.getPos())
	local x,y = parent:getPos()
	parent:setPos(x + 1000 * time:fixedDelta(),y)
end


function oncollision(other)
	local name = other:getName()
	if name == "Enemy" then
		parent:delete()
	end
end