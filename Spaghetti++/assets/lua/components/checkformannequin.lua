--parent is component's parent gameObject. It supports functions 

function oncollisionenter(other)
	local name = other:getName()
	if name == "Mannequin" then
		print("You Died")
		gameObject.deleteAll()
		obj = gameObject.new()
		obj:setName("Loader")
		obj:addComponent("lua", "sceneloader.lua")
		obj:sendMessage("../deathscene.lua")
	end
end