teststring = "This is a test"
string2 = "\nor is it??"

width = 1280
height = 1024
windowname = "Spaghetti+++Lua"
fov=60

function printJoined(s1, s2)
	local s3 = s1 .. s2
	print(s3)
end

printJoined(teststring, string2)