function start()
	chance = tonumber(parent:getName())
	if chance == nil then
		chance = 100
	end
end

function ontriggerenter()
	print(chance .. " - " .. math.random(1,100))
	if math.random(1,100) <= chance then
		parent:playSound()
		parent:removeComponent("lua")
	end
end
