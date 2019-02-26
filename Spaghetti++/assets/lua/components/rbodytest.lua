--parent is component's parent gameObject. It supports functions 

function start()
	print("Initialised test lua component")
	--print(test.test())
end

function update() --currently disabled
--	print("Updated lua component") 
end

function fixedupdate()
	if keys.pressed(keys.T) then
		parent:addForce(0,521,0)
	end
end
	
function ondestroy()

end

function oncollision(other)

end
