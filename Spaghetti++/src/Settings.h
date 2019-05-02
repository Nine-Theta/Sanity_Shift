#pragma once
#include <map>
#include <iostream>
#include "LuaState.h"
#include <string>
namespace sge {
	class Settings
	{
	public:
		Settings();
		~Settings();
		static void ReadSettings();
		static std::string GetSetting(std::string);
		static int GetInt(std::string);
		static float GetFloat(std::string);
		static bool GetBool(std::string);
		static void SetSetting(std::string, std::string);
	private:
		static std::map<std::string, std::string> _settings;
	};

}