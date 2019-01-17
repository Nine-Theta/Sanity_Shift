#pragma once

#include "lua.hpp"
#include <iostream>

namespace sge {

	class LuaState
	{
	public:
		LuaState(std::string file);
		~LuaState();
	private:
		lua_State *state = luaL_newstate();
	};
}
