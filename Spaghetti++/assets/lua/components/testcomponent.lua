teststring = "This is a test"
string2 = "\nor is it??"

width = 1280
height = 1024
windowname = "Spaghetti+++Lua"
--parent is component's parent gameObject. It supports functions 

function printJoined(s1, s2)
	local s3 = s1 .. s2
	print(s3)
end

function start()
	print("Initialised test lua component")
	--print(test.test())
	print(parent)
	local newObj = gameObject:new()
	print("New game object: " .. newObj:getName())
	newObj:setName("luaObjTest")
end

function update() --currently disabled
--	print("Updated lua component") 
end

function fixedupdate()
	--print(parent.getPos())
	local x, y = parent:getPos()
	parent:setPos(math.sin(time.seconds() * 10) * 100,y)
end
	
function ondestroy()
	print("Destroyed test lua component")
	--test.setPos()
	local foundObj = gameObject:find("luaObjTest")
	print("Found game object: " .. foundObj:getName())
end

function returnTest()
	return 3,5,7
end

printJoined(teststring, string2)