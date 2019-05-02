--parent is component's parent gameObject. It supports functions 
function init()
	print("Loading custom scene")
	gameObject.deleteAll()
	audio.stop()
	--print(test.test())
	local finalScore = gameObject.new()
	finalScore:setText("Final score: " .. score)
	finalScore:setPos(-100,0)
	local newObj = gameObject:new()
	newObj:setName("luaObjTest")
	newObj:setPos(-300,300)
	newObj:addComponent("text","Press Spacebar to play!")
	newObj:addComponent("lua","startscreen.lua")
	local cam = gameObject:new()
	cam:setName("Camera")	
	cam:addComponent("camera")
end

function start()
	parent:setName("score")
end

function update() --currently disabled
--	print("Updated lua component") 
end
score = 0
function fixedupdate()
	parent:setText("Score: " .. score)
end

function onmessage(message)
	if message ~= "endGame" then
		score = score + message
	else
		init()
	end
end

function oncollision(other)
	local name = other:getName()
	if name == "Enemy" then
		other:sendMessage("Bullet sending message to enemy that got killed!")
		parent:delete()
	end
end