door = nil


function start()
	parent:playSound()
end
maxAngle = 100
angleS = 0
direction = 1
secs = 0.95
ctime = 0

timeToClose = 20
function fixedupdate()
	timeToClose = timeToClose - time.fixedDelta()
	if timeToClose < 0 then
		parent:delete()
	end
end

function onraycasthit(caster)

end