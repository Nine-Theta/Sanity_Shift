--parent is component's parent gameObject. It supports functions 

function start()
screen = gameObject.find("PauseScreen") 

end

enabled = true

function fixedupdate()
	if keys.down(keys.P) then
		if time.gettimescale() > 0 then
		time.settimescale(0)
		screen:setActive(enabled)
		else
		time.settimescale(1)
		screen:setActive(not enabled)
		end
	end		
	
	if keys.down(keys.Num1) then
		time.settimescale(1)
	end	
	if keys.down(keys.Num2) then
		time.settimescale(2)
	end		
	if keys.down(keys.Num3) then
		time.settimescale(10.0)
	end
	if keys.down(keys.Num4) then
		time.settimescale(0.25)
	end	
end
	
function ondestroy()

end


