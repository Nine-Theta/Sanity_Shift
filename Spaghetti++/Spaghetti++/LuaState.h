#pragma once

#include "lua.hpp"
#include <iostream>

namespace sge {

	class LuaState
	{
	public:
		LuaState(std::string file);
		~LuaState();
		double getNumber(std::string name);
	private:
		lua_State *state = luaL_newstate();
	};
}
