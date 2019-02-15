--parent is component's parent gameObject. It supports functions 

function start()
	print("Initialised test lua component")
	--print(test.test())
end

function update()

	if mouse.moved() then
		local mX, mY = mouse.delta()
		parent:rotate(1,0,0, mY * 10 * time.fixedDelta())
		--print(mX, mY)
	end
end
	
function ondestroy()

end

function returnTest()
	return 3,5,7
end
