--parent is component's parent gameObject. It supports functions 

--[[function update() --currently disabled
--	print("Updated lua component") 
end]]--

x = 0
y = 0
function fixedupdate()
	--print(parent.getPos())
	--print(x .. y .. z)
	--print("Applying force: " .. x .. y .. z)
	parent:rotate(0,1,0,-90 * time.fixedDelta())
	--parent:rotate(1,0,0,45 * time.fixedDelta())
	--parent:setRotation(40,0,1,0)
end
	
function ondestroy()

end