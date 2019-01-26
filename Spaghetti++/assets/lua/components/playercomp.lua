--parent is component's parent gameObject. It supports functions 

function printJoined(s1, s2)
	local s3 = s1 .. s2
	print(s3)
end

function start()
	print("Initialised test lua component")
	--print(test.test())
end

function update() --currently disabled
--	print("Updated lua component") 
end
velY = 0
function fixedupdate()
	--print(parent.getPos())
	local x, y = parent:getPos()
	
	if keys.pressed(keys.down) then
		velY = velY + 10 * time.fixedDelta()
	end
	if keys.pressed(keys.up) then
		velY = velY - 10 * time.fixedDelta()
	end
	velY = velY * 0.98
	y = y + velY
	parent:setPos(x,y)
end
	
function ondestroy()

end

function oncollision(other)
	--print(other:getName())
end

function returnTest()
	return 3,5,7
end

printJoined(teststring, string2)