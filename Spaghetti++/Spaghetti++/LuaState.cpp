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


}