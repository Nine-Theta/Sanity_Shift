function init()

	local objmannequin = gameObject.new()
	objmannequin:setName("Bob")
	objmannequin:setPos(0,0.5,150)
	objmannequin:setRotation(0,1,0,180)
	objmannequin:addComponent("mesh", "Mannequin/Mannequin_2.obj", "Mannequin/diffuse.dds", "Mannequin/specular.dds", "Mannequin/normal.dds")
	objmannequin:addComponent("sound", "death_shriek.wav")
	objmannequin:addComponent("lua", "endscenethings.lua")
	objmannequin:addComponent("lua", "move.lua")
	
	local objfloor = gameObject.new()
	objfloor:setName("Floor")
	objfloor:setPos(0,0,0)
	objfloor:addComponent("meshcollider", "plane20x20_2tris_aligned_uvs.obj")
				
	local obj1 = gameObject.new()
	obj1:setName("Player")
	obj1:setPos(0,1.0,-5)
	obj1:addComponent("capsulecollider","0.49","1.85","40")
		local obj2 = gameObject.new()
		obj2:setName("PlayerFeet")
		obj2:setPos(0,-0.94,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
			local obj3 = gameObject.new()
			obj3:setName("MainCam")
			obj3:setPos(0,0.3,0)
			obj3:setRotationQ(1,0,0,0)
			obj3:setParent(obj2)
			obj3:addComponent("camera")
				local obj4 = gameObject.new()
				obj4:setName("Flashlight")
				obj4:setPos(0,0,-0.5)
				obj4:setRotationQ(1,0,0,0)
				obj4:setParent(obj3)
				obj4:addComponent("spotlight","99999999.32")
end
