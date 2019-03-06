#include "LuaState.h"
#include <string>

namespace sge {
	LuaState::LuaState(std::string file)
	{
		luaL_openlibs(state);
		file = "lua/" + file;
		if (int err = luaL_loadfile(state, file.c_str())) {
			//throw std::runtime_error("Error loading lua file: " + file);
			std::string msg;
			msg = err == LUA_ERRSYNTAX ? "LUA_ERRSYNTAX" : err == LUA_ERRMEM ? "LUA_ERRMEM" : err == LUA_ERRFILE ? "LUA_ERRFILE" : "UNKNOWN";
			std::cout << "Error " << msg << " loading lua file: " << file << std::endl;
			std::cout << lua_tostring(state, -1) << "\n" << "Stack: " << lua_gettop(state) << std::endl;
			return;
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

	std::vector<std::string> LuaState::GetArgsFromStack() {
		std::vector<std::string> vals;
		int n = lua_gettop(state);
		//std::cout << n << " elements on stack" << std::endl;
		for (int i = 1; i <= n; i++) {
			if (!lua_isnil(state, -1) && !lua_isfunction(state, -1) && !lua_islightuserdata(state, -1) && !lua_istable(state, -1)) {
				std::string s = lua_tostring(state, -1);
				//std::cout << "Arg " << i << ": " << s << std::endl;
				vals.push_back(s);
				lua_pop(state, 1);
			}
			else
				break; //once function or lightuserdata is hit, assume we've read all string args
		}
		return vals;
	}

	std::vector<bool> LuaState::GetBoolsFromStack() {
		std::vector<bool> vals;
		int n = lua_gettop(state);
		//std::cout << n << " elements on stack" << std::endl;
		for (int i = 1; i <= n; i++) {
			if (!lua_isnil(state, -1) && !lua_isfunction(state, -1) && !lua_islightuserdata(state, -1) && !lua_istable(state, -1)) {
				bool s = lua_toboolean(state, -1);
				//std::cout << "Arg " << i << ": " << s << std::endl;
				vals.push_back(s);
				lua_pop(state, 1);
			}
			else
				break; //once function or lightuserdata is hit, assume we've read all string args
		}
		return vals;
	}

	std::vector<double> LuaState::GetNumbersFromStack() {
		std::vector<double> vals;
		int n = lua_gettop(state);
		//std::cout << n << " on lua stack" << std::endl;
		for (int i = 1; i <= n; i++) {
			if (!lua_isnil(state, -1) && !lua_isfunction(state, -1) && !lua_islightuserdata(state, -1) && !lua_istable(state, -1)) {
				double s = lua_tonumber(state, -1);
				//std::cout << "Arg " << i << ": " << s << std::endl;
				vals.push_back(s);
				lua_pop(state, 1);
			}
			else
				break;
		}
		return vals;
	}

	int LuaState::GetStackSize()
	{
		return lua_gettop(state);
	}

	std::vector<std::string> LuaState::ReadFromTable(std::string table, std::vector<std::string> vars)
	{
		lua_getglobal(state, table.c_str());

		if (!lua_istable(state, -1)) {
			lua_pop(state, 1);
			return std::vector<std::string>();
		}
		std::vector<std::string> returns{};
		for (std::string s : vars) {
			lua_pushstring(state, s.c_str());
			lua_gettable(state, -2);
			returns.push_back(lua_tostring(state, -1));
			lua_pop(state, 1);
		}
		return returns;
	}

	std::string LuaState::ReadFromTable(std::string table, std::string var)
	{
		if (!lua_istable(state, -1)) {
			lua_pop(state, 1);
			return "";
		}
		lua_pushstring(state, var.c_str());
		lua_gettable(state, -2);
		std::string s = lua_tostring(state, -1);
		lua_pop(state, 1);
		return s;
	}

	void LuaState::OpenTable(std::string table)
	{
		lua_getglobal(state, table.c_str());
		if (!lua_istable(state, -1))
			lua_newtable(state);
	}

	void LuaState::SaveTable(std::string name, std::string metatable)
	{
		if (lua_istable(state, -1)) {
			if (metatable != "") {
				luaL_getmetatable(state, metatable.c_str());
				lua_setmetatable(state, -2);
			}
			lua_setglobal(state, name.c_str());
		}
	}

	void LuaState::PushToTable(std::string table, int value)
	{
		lua_pushstring(state, table.c_str());
		lua_pushinteger(state, value);
		lua_settable(state, -3);
	}

	void LuaState::PushToTable(std::string table, void * value)
	{
		lua_pushstring(state, table.c_str());
		lua_pushlightuserdata(state, value);
		lua_settable(state, -3);
	}

	std::vector<std::string> LuaState::CallFunction(std::string name, int returns)
	{
		return CallFunction(name, std::vector<std::string>{},returns);
	}

	std::vector<std::string> LuaState::CallFunction(std::string name, std::vector<std::string> args, int returns)
	{
		//std::cout << "Top of stack in callfunc: " << lua_gettop(state) << std::endl;
		lua_getglobal(state, name.c_str());

		std::vector<std::string> vals;
		if (!lua_isfunction(state, lua_gettop(state))) {
			lua_pop(state, 1);
			return vals;
		}

		for (std::string s : args) {
			lua_pushstring(state, s.c_str());
		}
		int status = lua_pcall(state, args.size(), 0,0);
		if (status) {
			std::cout << "Lua error: " << std::to_string(status) << "\n" << lua_tostring(state, -1) << "\n" << "Stack: " << lua_gettop(state) << std::endl;
		}

		int n = lua_gettop(state);
		//std::cout << "Top of stack in callfunc2: " << n << std::endl;
		for (int i = 1; i <= n; i++) {
			if (!lua_isnil(state, -1) && !lua_isfunction(state, -1) && !lua_islightuserdata(state, -1) && !lua_istable(state,-1)) {
				std::string s = luaL_checkstring(state, -1);
				vals.push_back(s);
				lua_pop(state, 1);
			}
			else
				break;
		}
		//lua_pop(state,n);
		return vals;
	}

	void LuaState::RegisterLib(const luaL_Reg lib[], std::string libname)
	{
		luaL_newlib(state, lib);
		lua_setglobal(state,libname.c_str());
	}
	void LuaState::PushLightUserData(void * object, std::string metatable)
	{
		PushLightUserData(object);
		luaL_getmetatable(state, metatable.c_str());
		lua_setmetatable(state, -2);
	}
	void LuaState::PushLightUserData(void * object)
	{
		lua_pushlightuserdata(state, object);
	}
	void LuaState::SetGlobal(std::string name)
	{
		lua_setglobal(state, name.c_str());
	}
	void LuaState::PushMetaLib(std::string name, const luaL_Reg* lib)
	{
		luaL_newmetatable(state, name.c_str());

		lua_pushstring(state, "__index");
		lua_pushvalue(state, -2);
		lua_settable(state, -3);
		luaL_setfuncs(state, lib, 0);
	}
	lua_State * LuaState::GetState()
	{
		return state;
	}

}