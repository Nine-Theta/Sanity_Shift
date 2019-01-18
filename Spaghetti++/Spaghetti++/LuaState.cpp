#include "LuaState.h"
#include <string>

namespace sge {
	LuaState::LuaState(std::string file)
	{
		luaL_openlibs(state);
		file = "lua/" + file;
		if (luaL_loadfile(state, file.c_str())) {
			throw std::runtime_error("Lua file could not be found: " + file);
		}

		int status = lua_pcall(state, 0, 0, 0);
		if (status) {
			std::cout << "Lua error: " << std::to_string(status) << "\n" << lua_tostring(state, -1) << "\n" << "Stack: " << lua_gettop(state) << std::endl;
		}
	}


	LuaState::~LuaState()
	{
		lua_close(state);
	}

	double LuaState::GetNumber(std::string name)
	{
		lua_getglobal(state,name.c_str());
		double nmbr = lua_tonumber(state, -1);
		return nmbr;
	}

	std::string LuaState::GetString(std::string name)
	{
		lua_getglobal(state, name.c_str());
		std::string str = lua_tostring(state, -1);
		return str;
	}


}