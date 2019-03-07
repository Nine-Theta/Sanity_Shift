
function start()
once = true
once2 = false
end

function fixedupdate()
	if(once2) then	
		print("init once2")
		init()
		once2 = false
	end
		
	if(once) then
		print("init once")
		once = false
		once2 = true
end
	end

function init()
print("init")
	local obj1 = gameObject.new()
	obj1:setName("13cube")
	obj1:setPos(0,1.82,5)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","13cube.obj","rustypaint.png","rustypaint_s.png","white_n.png")
	obj1:addComponent("lua","rotate.lua")
		local obj2 = gameObject.new()
		obj2:setName("default")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		
		print("init banana tesseract")

	local obj1 = gameObject.new()
	obj1:setName("Hitler")
	obj1:setPos(-1.5,0.1,1.5)
	obj1:setRotationQ(0.3,0,0.954,0)
		local obj2 = gameObject.new()
		obj2:setName("Hitler")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("mesh","Hitler.obj","white.png","white.png","flat_n.png")
		
		print("init hitler ein")
		
	local obj1 = gameObject.new()
	obj1:setName("Hitler2")
	obj1:setPos(1.5,0.1,1.5)
	obj1:setRotationQ(0.3,0,-0.954,0)
		local obj2 = gameObject.new()
		obj2:setName("Hitler2")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("mesh","Hitler.obj","white.png","white.png","flat_n.png")
		
		print("init hitler zwei")
		
	local objfloor = gameObject.new()
	objfloor:setName("Floor")
	objfloor:setPos(0,0,0)
	objfloor:addComponent("mesh", "plane20x20_2tris_aligned_uvs.obj", "rustypaint.png","rustypaint_s.png","flat_n.png")
	objfloor:addComponent("meshcollider", "plane20x20_2tris_aligned_uvs.obj")
		
		print("init floor")
		
	local obj1 = gameObject.new()
	obj1:setName("Player")
	obj1:setPos(0,1.4,-5)
	obj1:setRotationQ(0.9986774,0.02353511,0.04569906,-0.001076957)
	obj1:addComponent("lua","movementrbody.lua")
	obj1:addComponent("capsulecollider","0.49","1.85","40")
		local obj2 = gameObject.new()
		obj2:setName("PlayerFeet")
		obj2:setPos(0,-0.95,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)		
		obj2:addComponent("lua","turncontrol.lua")
			local obj3 = gameObject.new()
			obj3:setName("MainCam")
			obj3:setPos(0,1.7,0)
			obj3:setRotationQ(1,0,0,0)
			obj3:setParent(obj2)
			obj3:addComponent("camera")
			obj3:addComponent("lua","pitchcontrol.lua")
				local obj4 = gameObject.new()
				obj4:setName("Flashlight")
				obj4:setPos(0,0,0)
				obj4:setRotationQ(1,0,0,0)
				obj4:setParent(obj3)
				obj4:addComponent("spotlight","99999999.32")
				
				print("init player full")
	
	local objplane = gameObject.new()
	objplane:setName("PauseScreen")
	objplane:setPos(0,0,3)
	objplane:setRotationQ(0,0,-0.7,0.7)
	objplane:setParent(obj3)
	objplane:addComponent("mesh","plane169test.obj","MenuScreen.dds","black.png","flat_n.png")
	objplane:addComponent("mesh","etest.obj","white.png","gray.png","flat_n.png")		
	objplane:setActive(false)
	objplane:addComponent("lua", "pausecontrol.lua")
	
	print("init pausescreen")
	
	local objmenu = gameObject.new()
	objmenu:setName("Menu")	
	objmenu:setPos(0,0,0)	
	objmenu:addComponent("lua", "buttoncontrol.lua")
		local objplay = gameObject.new()
		objplay:setName("PlayButton")
		objplay:addComponent("lua", "startgamebutton.lua")
		objplay:setParent(objmenu)
		local objsettings= gameObject.new()
		objsettings:setName("SettingsButton")
		objsettings:addComponent("lua", "settings.lua")
		objsettings:setParent(objmenu)
		local objexit = gameObject.new()
		objexit:setName("ExitButton")
		objexit:addComponent("lua", "exitgamebutton.lua")
		objexit:setParent(objmenu)
	
	print("init end")
end
