--parent is component's parent gameObject. It supports functions 

function start()

buttonSelected = parent:getChildren()[0]
buttonIdle = parent:getChildren()[1]

buttonSelected:setActive(false)

end

function update() --currently disabled

end

function Selected()
	buttonSelected:setActive(true)
	buttonIdle:setActive(false)
end

function Deselected()
	buttonSelected:setActive(false)
	buttonIdle:setActive(true)
end

function Invoke()
	print("settings invoked")

end
	
function fixedupdate()
	
end
	
function ondestroy()

end