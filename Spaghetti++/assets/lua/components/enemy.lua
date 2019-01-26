--parent is component's parent gameObject. It supports functions 



function update() --currently disabled
--	print("Updated lua component") 
end

function fixedupdate()
	--print(parent.getPos())
	local x,y = parent:getPos()
	parent:setPos(x - 150 * time:fixedDelta(),y)
end


function oncollision(other)
	local name = other:getName()
	if name == "Player" then
		parent:delete()
	end
end