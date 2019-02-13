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
		void OpenTable(std::string table);
		void SaveTable(std::string name, std::string metatable = "");
		void PushToTable(std::string key, int value);
		void PushToTable(std::string key, std::string value);
		std::vector<std::string> CallFunction(std::string name, int returns = 0);
		std::vector<std::string> CallFunction(std::string name, std::vector<std::string> args, int returns = 0);
		std::vector<std::string> GetArgsFromStack();
		std::vector<double> GetNumbersFromStack();
		int GetStackSize();

		void RegisterLib(const luaL_Reg lib[], std::string libname);
		void PushLightUserData(void* object, std::string metatable);
		void PushLightUserData(void* object);

		void SetGlobal(std::string name); //makes top of stack a global
		void PushMetaLib(std::string name, const struct luaL_Reg* lib);

		template<class Type>
		Type* GetObjectFromStack(std::string name);
		template<class Type>
		Type* GetObjectFromStackTop(std::string name);

		lua_State* GetState();
	private:
		lua_State *state = luaL_newstate();

	};
	template<class Type>
	inline Type * LuaState::GetObjectFromStack(std::string name)
	{
		Type* obj = static_cast<Type*>(
			luaL_checkudata(state, 1, name.c_str()));
		//if(obj != NULL)
			//lua_pop(state, 1);
		//lua_pop(state, 1);
		return obj;
	}

	template<class Type>
	inline Type * LuaState::GetObjectFromStackTop(std::string name)
	{
		Type* obj = static_cast<Type*>(
			luaL_checkudata(state, -1, name.c_str()));
		if(obj != NULL)
			lua_pop(state, 1);
		//lua_pop(state, 1);
		return obj;
	}
}
