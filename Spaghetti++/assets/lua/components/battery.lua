function start()
end

function onfixedupdate()
	print("BATTERY")
end

function raycastresult(lol)
	print("RESULT")
end

function onraycasthit(caster)
	if keys.down(keys.E) then
		print("Deleting battery!")
		parent:delete()
	end
end