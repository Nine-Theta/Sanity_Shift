function init()
	local obj1 = gameObject.new()
	obj1:setName("Torture_Room_2")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Torture_Room_2.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Torture_Room_2.obj")
		local obj2 = gameObject.new()
		obj2:setName("Torture_Room_2_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("TestBox")
	obj1:setPos(2.34,12.99,-68.48)
	obj1:setRotationQ(1,0,0,0)
		local obj2 = gameObject.new()
		obj2:setName("default")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("boxcollider","1.39","3.067496","8.478649","0")
		obj2:setTrigger(false)
		obj2:addComponent("mesh","specular","TestBox.obj","Diffuse.png","white.png","flat_n.png")

	local obj1 = gameObject.new()
	obj1:setName("M_LQ")
	obj1:setPos(10.69,0.27,-80.2)
	obj1:setRotationQ(0.6550047,0,-0.7556249,0)
	obj1:addComponent("mesh","specular","M_LQ.obj","Mannequin/diffuse.dds","Mannequin/specular.dds","Mannequin/normal.dds")

	local obj1 = gameObject.new()
	obj1:setName("13cube")
	obj1:setPos(-0.56,1.82,-47.66)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","13cube.obj","rustypaint.dds","rustypaint_s.dds","white_n.png")
	obj1:addComponent("lua","rotate.lua")
	obj1:addComponent("boxcollider","1.3","1.3","1.3","0")
	obj1:setTrigger(false)
		local obj2 = gameObject.new()
		obj2:setName("default")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Hitler")
	obj1:setPos(-0.997,0.403301,-55.529)
	obj1:setRotationQ(1,0,0,0)
		local obj2 = gameObject.new()
		obj2:setName("Hitler")
		obj2:setPos(0,-0.152,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("mesh","specular","Hitler.obj","white.png","white.png","flat_n.png")

	local obj1 = gameObject.new()
	obj1:setName("Player")
	obj1:setPos(-1.102,1.221,-55.705)
	obj1:setRotationQ(0.9986774,0.02353511,0.04569906,-0.001076957)
	obj1:addComponent("lua","movementrbody.lua")
	obj1:addComponent("capsulecollider","0.6","1.85","40")
	obj1:setTrigger(false)
		local obj2 = gameObject.new()
		obj2:setName("PlayerFeet")
		obj2:setPos(0,-0.92,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("lua","turncontrol.lua")
			local obj3 = gameObject.new()
			obj3:setName("MainCam")
			obj3:setPos(0,1.698,0)
			obj3:setRotationQ(1,0,0,0)
			obj3:setParent(obj2)
			obj3:addComponent("camera")
			obj3:addComponent("lua","pitchcontrol.lua")
			obj3:addComponent("raycast")
				local obj4 = gameObject.new()
				obj4:setName("Flashlight")
				obj4:setPos(-0.294,-0.247,0.425)
				obj4:setRotationQ(1,0,0,0)
				obj4:setParent(obj3)
				obj4:addComponent("spotlight","40.32")
				obj4:addComponent("lua","flashlightMove.lua")
					local obj5 = gameObject.new()
					obj5:setName("Light")
					obj5:setPos(0,0,0)
					obj5:setRotationQ(0.9988274,0,0.048414,0)
					obj5:setParent(obj4)
					obj5:addComponent("pointlight","16.06")

	local obj1 = gameObject.new()
	obj1:setName("Torture_Room_1")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Torture_Room_1.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Torture_Room_1.obj")
		local obj2 = gameObject.new()
		obj2:setName("Torture_Room_1_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Theater")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Theater.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Theater.obj")
		local obj2 = gameObject.new()
		obj2:setName("Theater_Others_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Small_Bedroom_3")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Small_Bedroom_3.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Small_Bedroom_3.obj")
		local obj2 = gameObject.new()
		obj2:setName("Small_Bedroom_3_Small_Rooms_Bedrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Small_Bedroom_2")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Small_Bedroom_2.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Small_Bedroom_2.obj")
		local obj2 = gameObject.new()
		obj2:setName("Small_Bedroom_2_Small_Rooms_Bedrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Small_Bedroom_1")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Small_Bedroom_1.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","ColliderSmall_Bedroom_1.obj")
		local obj2 = gameObject.new()
		obj2:setName("Small_Bedroom_1_Small_Rooms_Bedrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Small_Bathroom")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Small_Bathroom.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Small_Bathroom.obj")
		local obj2 = gameObject.new()
		obj2:setName("Small_Bathroom_Bathrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Reception")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Reception.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Reception.obj")
		local obj2 = gameObject.new()
		obj2:setName("Reception_Others_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Medium_Room_3")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Medium_Room_3.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Medium_Room_3.obj")
		local obj2 = gameObject.new()
		obj2:setName("Medium_Room_3_Medium_Rooms_Bedrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Medium_Room_2")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Medium_Room_2.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Medium_Room_2.obj")
		local obj2 = gameObject.new()
		obj2:setName("Medium_Room_2_Medium_Rooms_Bedrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Medium_Room_1")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Medium_Room_1.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Medium_Room_1.obj")
		local obj2 = gameObject.new()
		obj2:setName("Medium_Room_1_Medium_Rooms_Bedrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Medium_Bathroom_Theater")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Medium_Bathroom_Theater.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Medium_Bathroom_Theater.obj")
		local obj2 = gameObject.new()
		obj2:setName("Medium_Bathroom_Theater_Bathrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Living_and_Dining")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Living_and_Dining.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Living_and_Dining.obj")
		local obj2 = gameObject.new()
		obj2:setName("Living_and_Dining_Others_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Kitchen")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Kitchen.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Kitchen.obj")
		local obj2 = gameObject.new()
		obj2:setName("Kitchen_Others_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Hydrotherapy_Room")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Hydrotherapy_Room.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Hydrotherapy_Room.obj")
		local obj2 = gameObject.new()
		obj2:setName("Hydrotherapy_Room_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Hallway")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","HallwayCol.obj","white.png","white_s.png","cloth_n.png")
	obj1:addComponent("meshcollider","HallwayCol.obj")
		local obj2 = gameObject.new()
		obj2:setName("Hallway_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Common_Bedroom")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Common_Bedroom.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Common_Bedroom.obj")
		local obj2 = gameObject.new()
		obj2:setName("Common_Bedroom_Bedrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Chapel")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Chapel.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Chapel.obj")
		local obj2 = gameObject.new()
		obj2:setName("Chapel_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Cells_Upper_Levels")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Cells_Upper_Levels.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Cells_Upper_Levels.obj")
		local obj2 = gameObject.new()
		obj2:setName("Cells_Upper_Levels_Cells_Lower_Level_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Cells_Lower_Level_Floor")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Cells_Lower_Level_Floor.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Cells_Lower_Level_Floor.obj")
		local obj2 = gameObject.new()
		obj2:setName("Cells_Lower_Level_Floor_Cells_Lower_Level_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Cells_Lower_Level_Ceiling")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Cells_Lower_Level_Ceiling.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Cells_Lower_Level_Ceiling.obj")
		local obj2 = gameObject.new()
		obj2:setName("Cells_Lower_Level_Ceiling_Cells_Lower_Level_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Cells_Lower_Level")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Cells_Lower_Level.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Cells_Lower_Level.obj")
		local obj2 = gameObject.new()
		obj2:setName("Cells_Lower_Level_Cells_Lower_Level_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Cells_Ceiling")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Cells_Ceiling.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Cells_Ceiling.obj")
		local obj2 = gameObject.new()
		obj2:setName("Cells_Ceiling_Cells_Lower_Level_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Cell_Doors")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Cell_Doors.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Cell_Doors.obj")
		local obj2 = gameObject.new()
		obj2:setName("Cell_Doors_Cells_Lower_Level_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Big_Bathroom")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Big_Bathroom.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Big_Bathroom.obj")
		local obj2 = gameObject.new()
		obj2:setName("Big_Bathroom_Bathrooms_Game_Level_Part_2_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("Bathroom_Cells")
	obj1:setPos(0,0,0)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","Bathroom_Cells.obj","white.png","white.png","white_n.png")
	obj1:addComponent("meshcollider","Bathroom_Cells.obj")
		local obj2 = gameObject.new()
		obj2:setName("Bathroom_Cells_Game_Level_Part_1_Game_Layout_Rooms")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("ReceptionRoom_LQ")
	obj1:setPos(5.06,0.38,-80.72)
	obj1:setRotationQ(1,0,0,0)
		local obj2 = gameObject.new()
		obj2:setName("ReceptionRoom_LQ")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("mesh","specular","ReceptionRoom_LQ.obj","ReceptionRoom_LQ/diffuse.dds","ReceptionRoom_LQ/specular.dds","ReceptionRoom_LQ/normal.dds")
		obj2:addComponent("meshcollider","ReceptionRoom_LQ.obj")
		obj2:addComponent("lua","raycasthit.lua")
			local obj3 = gameObject.new()
			obj3:setName("ReceptionDesk")
			obj3:setPos(5.24,-0.105949,0.1900024)
			obj3:setRotationQ(0.7071068,0,-0.7071068,0)
			obj3:setParent(obj2)
			local obj3 = gameObject.new()
			obj3:setName("Reception 1")
			obj3:setPos(5.24,-0.105949,0.1900024)
			obj3:setRotationQ(0.7071068,0,-0.7071068,0)
			obj3:setParent(obj2)
			obj3:addComponent("mesh","specular","Reception.obj","Reception/diffuse.png","Reception/specular.png","Reception/normal.png")
			obj3:addComponent("meshcollider","Reception.obj")
			local obj3 = gameObject.new()
			obj3:setName("ReceptionDesk (1)")
			obj3:setPos(5.24,-0.105949,0.1900024)
			obj3:setRotationQ(0.7071068,0,-0.7071068,0)
			obj3:setParent(obj2)

	local obj1 = gameObject.new()
	obj1:setName("M_LQ (1)")
	obj1:setPos(4.49,0.27,-81.09)
	obj1:setRotationQ(0.9260682,0,-0.377356,0)
	obj1:addComponent("mesh","glow","M_LQ.obj","Mannequin/diffuseGlow.dds","Mannequin/specular.dds","Mannequin/normal.dds")
	obj1:addComponent("glowcontroller")

	local obj1 = gameObject.new()
	obj1:setName("Door")
	obj1:setPos(-2.26,0.277,-61.26)
	obj1:setRotationQ(1,0,0,0)
		local obj2 = gameObject.new()
		obj2:setName("DoorCol")
		obj2:setPos(0.645,1.158,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("mesh","specular","Door_Placeholder.obj","white.png","white.png","flat_n.png")
		obj2:addComponent("lua","door.lua")
		obj2:addComponent("boxcollider","1.319854","2.331214","0.148174","0")
		obj2:setTrigger(false)

	local obj1 = gameObject.new()
	obj1:setName("GameObject")
	obj1:setPos(0,0.263,-66.35)
	obj1:setRotationQ(1,0,0,0)
		local obj2 = gameObject.new()
		obj2:setName("Hitler_Body")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("mesh","specular","Proportions/Hitler_Body.obj","Proportion/hitlerbody_colspec.png","Proportion/hitlerbody_spec.png","flat_n.png")
			local obj3 = gameObject.new()
			obj3:setName("Hitler_Body")
			obj3:setPos(0,0,0)
			obj3:setRotationQ(1,0,0,0)
			obj3:setParent(obj2)
		local obj2 = gameObject.new()
		obj2:setName("Hitler_Head")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)
		obj2:addComponent("mesh","specular","Proportions/Hitler_Head.obj","Proportion/hitlerhead_colspec.png","Proportion/hitlerhead_spec.dds","flat_n.png")
			local obj3 = gameObject.new()
			obj3:setName("Hitler_Head")
			obj3:setPos(0,0,0)
			obj3:setRotationQ(1,0,0,0)
			obj3:setParent(obj2)

	local obj1 = gameObject.new()
	obj1:setName("13cube (1)")
	obj1:setPos(-0.56,1.45,-43.32)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","13cube.obj","rustypaint.dds","rustypaint_s.dds","white_n.png")
	obj1:addComponent("lua","rotate.lua")
	obj1:addComponent("boxcollider","1.3","1.3","1.3","12")
	obj1:setTrigger(false)
		local obj2 = gameObject.new()
		obj2:setName("default")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

	local obj1 = gameObject.new()
	obj1:setName("13cube (2)")
	obj1:setPos(-0.56,2.949,-43.32)
	obj1:setRotationQ(1,0,0,0)
	obj1:addComponent("mesh","specular","13cube.obj","rustypaint.dds","rustypaint_s.dds","white_n.png")
	obj1:addComponent("lua","rotate.lua")
	obj1:addComponent("boxcollider","1.3","1.3","1.3","12")
	obj1:setTrigger(false)
		local obj2 = gameObject.new()
		obj2:setName("default")
		obj2:setPos(0,0,0)
		obj2:setRotationQ(1,0,0,0)
		obj2:setParent(obj1)

end
