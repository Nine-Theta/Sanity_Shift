#pragma once

#include "lua.hpp"
#include <iostream>
#include <vector>

namespace sge {

	class LuaState
	{
	public:
		LuaState(std::string file);
		~LuaState();
		double GetNumber(std::string name);
		std::string GetString(std::string name);
		std::vector<std::string> ReadFromTable(std::string table, std::vector<std::string> vars);
		std::string ReadFromTable(std::string table, std::string var);
		std::vector<std::string> CallFunction(std::string name, int returns = 0);
		std::vector<std::string> CallFunction(std::string name, std::vector<std::string> args, int returns = 0);
	private:
		lua_State *state = luaL_newstate();
	};
}
