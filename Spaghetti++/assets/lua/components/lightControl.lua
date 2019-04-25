--parent is component's parent gameObject. It supports functions 



rotation = 0
verticalSensitivity = 10 --default: 10
upperLimit = 45
lowerLimit = -45

active = true
enabled = false

lastActive = true
function setActive(act)
	for i = 0,#light do
		light[i]:setActive(act)
	end
	if lastActive ~= act then
		if act then
			parent:setSound("flashlight/click_on.wav")
		else
			parent:setSound("flashlight/click_off.wav")
		end
		parent:playSound()
	end
	lastActive = act
end


function createpausemenu()

	local objpause = gameObject.new()
	objpause:setName("PauseScreen")
	objpause:setParent(parent:getParent():getParent())
	objpause:setPos(-0.065,0.0,0)
	objpause:setRotation(0,1,0,180)
	
		local objresume = gameObject.new()
		objresume:setName("ResumeButton")
		objresume:setPos(0.01,2.7,2)
		objresume:setRotation(0,1,0,180)
			local objresumeA = gameObject.new()
			objresumeA:setName("ResumeButtonA")
			objresumeA:addComponent("mesh","ResumeGameTestSelect.obj","brown.dds","white_s.png","flat_n.png")
			objresumeA:setParent(objresume)
			local objresumeNA = gameObject.new()
			objresumeNA:setName("ResumeButtonNA")
			objresumeNA:addComponent("mesh","ResumeGameTest.obj","lightGray.dds","white_s.png","flat_n.png")
			objresumeNA:setParent(objresume)
		--objresume:addComponent("lua", "resumegamebutton.lua")
		objresume:setParent(objpause)
		--objresume:setActive(false)
		
		local objsettingsp = gameObject.new()
		objsettingsp:setName("PauseSettingsButton")
		objsettingsp:setPos(-0.2,2.55,2)
		objsettingsp:setRotation(0,1,0,180)	
		local objsettingspA = gameObject.new()
			objsettingspA:setName("SettingsButtonA")	
			objsettingspA:addComponent("mesh","SettingsTestSelect.obj","brown.dds","white_s.png","flat_n.png")
			objsettingspA:setParent(objsettingsp)
			local objsettingspNA = gameObject.new()
			objsettingspNA:setName("SettingsButtonNA")	
			objsettingspNA:addComponent("mesh","SettingsTest.obj","lightGray.dds","white_s.png","flat_n.png")
			objsettingspNA:setParent(objsettingsp)
		--objsettingsp:addComponent("lua", "settings.lua")
		objsettingsp:setParent(objpause)
		objsettingsp:setActive(false)
		
		local objexitmenu = gameObject.new()
		objexitmenu:setName("ExitToMenuButton")		
		objexitmenu:setPos(0.085,2.4,2)
		objexitmenu:setRotation(0,1,0,180)			
			local objexitmenuA = gameObject.new()
			objexitmenuA:setName("ExitMenuButtonA")	
			objexitmenuA:addComponent("mesh","QuitToMenuTestSelect.obj","brown.dds","white_s.png","flat_n.png")
			objexitmenuA:setParent(objexitmenu)
			local objexitmenuNA = gameObject.new()
			objexitmenuNA:setName("ExitMenuButtonNA")	
			objexitmenuNA:addComponent("mesh","QuitToMenuTest.obj","lightGray.dds","white_s.png","flat_n.png")
			objexitmenuNA:setParent(objexitmenu)
		--objexitmenu:addComponent("lua", "exittomenubutton.lua")
		objexitmenu:setParent(objpause)
		objexitmenu:setActive(false)
		
		local objexitdesk = gameObject.new()
		objexitdesk:setName("ExitToDeskButton")		
		objexitdesk:setPos(0.3,2.25,2)
		objexitdesk:setRotation(0,1,0,180)				
			local objexitdeskA = gameObject.new()
			objexitdeskA:setName("ExitButtonA")	
			objexitdeskA:addComponent("mesh","QuitToDesktopTestSelect.obj","brown.dds","white_s.png","flat_n.png")
			objexitdeskA:setParent(objexitdesk)
			local objexitdeskNA = gameObject.new()
			objexitdeskNA:setName("ExitButtonNA")	
			objexitdeskNA:addComponent("mesh","QuitToDesktopTest.obj","lightGray.dds","white_s.png","flat_n.png")
			objexitdeskNA:setParent(objexitdesk)
		--objexitdesk:addComponent("lua", "exitgamebutton.lua")
		objexitdesk:setParent(objpause)
		--objexitdesk:setActive(false)
			
	--objpause:addComponent("lua", "pausecontrol.lua")
	--objpause:setActive(false)

end

function start()

	--createpausemenu()
	--print("Initialised test lua component")
	--print(test.test())
	light = parent:getChildren()
	--also controls the flashlight now, so slightly misleading name but if it works...
	setActive(false)
	
end

function fixedupdate()
	if not active then
		setActive(false)
		return
	end
	if time.fixedDelta() == 0 then
		return
	end
	if mouse.buttonDown(1) then
		enabled = not enabled
	end
	if mouse.buttonPressed(0) then
		setActive(not enabled)
	else
		setActive(enabled)
	end
end

function onmessage(msg)
	if msg == "disabled" then
		active = false
	else
		active = true
	end
end