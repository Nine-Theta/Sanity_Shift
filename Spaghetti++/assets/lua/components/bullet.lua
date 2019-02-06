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
	if x > 1200 then
		parent:delete()
	end
end


function oncollision(other)
	local name = other:getName()
	if name == "Enemy" then
		other:sendMessage("Bullet sending message to enemy that got killed!")
		parent:delete()
	end
end