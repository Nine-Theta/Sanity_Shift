teststring = "This is a test"
string2 = "\nor is it??"

width = 1280
height = 1024
windowname = "Spaghetti+++Lua"

function printJoined(s1, s2)
	local s3 = s1 .. s2
	print(s3)
end

function start()
	print("Initialised test lua component")
end

function update()
--	print("Updated lua component")
end

function fixedupdate()
	print("FixedUpdated lua component")
end
	
function ondestroy()
	print("Destroyed test lua component")
end

function returnTest()
	return 3,5,7
end

printJoined(teststring, string2)