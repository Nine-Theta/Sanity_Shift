--parent is component's parent gameObject. It supports functions 

function fixedupdate()
	if keys.down(keys.P) then
		if time.gettimescale() > 0 then
		time.settimescale(0)
		else
		time.settimescale(1)
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


