--parent is component's parent gameObject. It supports functions 


function start()

test = gameObject.find("tptest")

waitTime = 60
maskPart = 0

end

function Wait()

waitTime = waitTime - 1

end

function SpawnPart()

	if		maskPart == 0 then test:addComponent("mesh", "transparent", "plane.obj","DeathMask/Mask_1.png","black.dds","flat_n.png")
    elseif	maskPart == 1 then test:addComponent("mesh", "transparent", "plane.obj","DeathMask/Mask_2.png","black.dds","flat_n.png")
    elseif	maskPart == 2 then test:addComponent("mesh", "transparent", "plane.obj","DeathMask/Mask_3.png","black.dds","flat_n.png")
	elseif	maskPart == 3 then test:addComponent("mesh", "transparent", "plane.obj","DeathMask/Mask_4.png","black.dds","flat_n.png")
	elseif	maskPart == 4 then test:addComponent("mesh", "transparent", "plane.obj","DeathMask/Mask_5.png","black.dds","flat_n.png")
	elseif	maskPart == 5 then test:addComponent("mesh", "transparent", "plane.obj","DeathMask/Mask_6.png","black.dds","flat_n.png")
	elseif	maskPart == 6 then test:addComponent("mesh", "transparent", "plane.obj","DeathMask/Mask_6.png","black.dds","flat_n.png")
	end
	
maskPart = maskPart + 1
waitTime = 90
end
	
function fixedupdate()
	
	if(maskPart <= 7) then
		if (waitTime <= 0) then
			SpawnPart()
		else
		Wait()
		end
	end
	
end
	
function ondestroy()

end