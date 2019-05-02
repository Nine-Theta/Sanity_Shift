--parent is component's parent gameObject. It supports functions 

endCount = 15
function fixedupdate()
	endCount = endCount - time.fixedDelta()
	if endCount < 0 then
		parent:destroy()
	end
end