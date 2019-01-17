teststring = "This is a test"
string2 = "\nor is it??"

width = 800
height = 600

function printJoined(s1, s2)
	local s3 = s1 .. s2
	print(s3)
end

printJoined(teststring, string2)