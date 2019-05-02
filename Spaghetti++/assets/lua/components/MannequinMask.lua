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
	print(maskPart)
	
	if		maskPart == 0 then test:addComponent("mesh", "transparent", "plane_up.obj","DeathMask/Mask_1.dds","black.dds","flat_n.png")
    elseif	maskPart == 1 then test:addComponent("mesh", "transparent", "plane_up.obj","DeathMask/Mask_2.dds","black.dds","flat_n.png")
    elseif	maskPart == 2 then test:addComponent("mesh", "transparent", "plane_up.obj","DeathMask/Mask_3.dds","black.dds","flat_n.png")
	elseif	maskPart == 3 then test:addComponent("mesh", "transparent", "plane_up.obj","DeathMask/Mask_4.dds","black.dds","flat_n.png")
	elseif	maskPart == 4 then test:addComponent("mesh", "transparent", "plane_up.obj","DeathMask/Mask_5.dds","black.dds","flat_n.png")
	elseif	maskPart == 5 then test:addComponent("mesh", "transparent", "plane_up.obj","DeathMask/Mask_6.dds","black.dds","flat_n.png")
	elseif	maskPart == 6 then test:addComponent("mesh", "transparent", "plane_up.obj","DeathMask/Mask_7.dds","black.dds","flat_n.png")
	end
	
maskPart = maskPart + 1
waitTime = 80
end
	
function fixedupdate()
	
	if(maskPart <= 6) then
		if (waitTime <= 0) then
			SpawnPart()
		else
		Wait()
		end
	end
	
end
	
function ondestroy()

end