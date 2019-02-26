--parent is component's parent gameObject. It supports functions 

function start()
	print("Initialised test lua component")
	--print(test.test())
	offX,offY,offZ = parent:getPos()
	print(offY)
end

function update() --currently disabled
--	print("Updated lua component") 
end

function fixedupdate()
	local x = math.sin(time.seconds() * 0.8) * 0.1
	local y = math.sin(time.seconds() * 0.6) * 0.1
	
	
	parent:setRotation(0,1,0,x * 35)
	parent:rotate(1,0,0,y * 35)
	parent:setPos(x+ offX,y + offY,offZ)
	--print(offY)
end
	
function ondestroy()

end

function oncollision(other)
	--print(other:getName())
end
