--parent is component's parent gameObject. It supports functions 

function start()
	--parent:playSound()
	--audio.play("frolic.wav")
end

function fixedupdate()
	if(keys.down(keys.Any)) then		
	gameObject.deleteAll()
	obj = gameObject.new()
	obj:setName("Loader")
	obj:addComponent("lua", "sceneloader.lua")
	obj:sendMessage("../startscene.lua")
	end
end
	
function ondestroy()

end