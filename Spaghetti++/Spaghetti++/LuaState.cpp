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
		if (lua_isnumber(state, -1)) {
			double nmbr = lua_tonumber(state, -1);
			return nmbr;
		}
		return 0;
	}

	std::string LuaState::GetString(std::string name)
	{
		lua_getglobal(state, name.c_str());
		std::string str = lua_tostring(state, -1);
		return str;
	}

	std::vector<std::string> LuaState::CallFunction(std::string name, int returns)
	{
		return CallFunction(name, std::vector<std::string>{},returns);
	}

	std::vector<std::string> LuaState::CallFunction(std::string name, std::vector<std::string> args, int returns)
	{
		lua_getglobal(state, name.c_str());

		std::vector<std::string> vals;
		if (!lua_isfunction(state, lua_gettop(state))) {
			lua_pop(state, 1);
			return vals;
		}

		for (std::string s : args) {
			lua_pushstring(state, s.c_str());
		}
		int status = lua_pcall(state, args.size(), returns,0);
		if (status) {
			std::cout << "Lua error: " << std::to_string(status) << "\n" << lua_tostring(state, -1) << "\n" << "Stack: " << lua_gettop(state) << std::endl;
		}

		for (int i = 0; i < returns; i++) {
			vals.push_back(lua_tostring(state,-returns + i));
		}
		lua_pop(state,returns);
		return vals;
	}
}