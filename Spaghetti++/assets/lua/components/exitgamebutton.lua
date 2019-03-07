--parent is component's parent gameObject. It supports functions 


function start()

end

function update() --currently disabled

end

function Invoke()

	gameObject.deleteAll()
local obj =  gameObject.new()
	obj:setName("scene")	
	obj:addComponent("lua", "../startscene.lua")
	obj:callFunction("init")

--[[
	print("exitbutton invoked")
	gameObject.deleteAll()
	
	local obj1 = gameObject.new()
	obj1:setName("13cube")
	obj1:setPos(0,1.82,3)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","13cube.obj","rustypaint.png","rustypaint_s.png","white_n.png")
	obj1:addComponent("lua","rotate.lua")
	
	local obj3 = gameObject.new()
			obj3:setName("MainCam")
			obj3:setPos(0,1.7,0)
			obj3:setRotationQ(1,0,0,0)
			obj3:addComponent("camera")
			obj3:addComponent("lua","pitchcontrol.lua")
			
				local obj4 = gameObject.new()
				obj4:setName("Flashlight")
				obj4:setPos(0,0.5,0)
				obj4:setRotationQ(1,0,0,0)
				obj4:addComponent("spotlight","99999999.32")
				
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
		objexit:setParent(objmenu)]]--
	--mouse.loadscene()
	--[[
	gameObject.deleteAll()
	local obj =  gameObject.new()
	obj:setName("scene")	
	obj:addComponent("lua", "empty.lua")
	print("print")]]--
end
	
function fixedupdate()
	
end
	
function ondestroy()

end