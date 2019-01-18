#include "LuaState.h"


namespace sge {
	LuaState::LuaState(std::string file)
	{
		luaL_openlibs(state);
		file = "lua/" + file;
		luaL_loadfile(state, file.c_str());

		lua_call(state, 0, 0);
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