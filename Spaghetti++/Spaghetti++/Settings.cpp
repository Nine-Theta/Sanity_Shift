#include "Settings.h"

namespace sge {
	std::map<std::string, std::string> sge::Settings::_settings;
	Settings::Settings()
	{
	}


	Settings::~Settings()
	{
	}
	
	void Settings::ReadSettings()
	{
		LuaState settings("settings.lua");
		SetSetting("width", settings.GetString("width"));
		SetSetting("height", settings.GetString("height"));
		SetSetting("windowname", settings.GetString("windowname"));
	}
	std::string Settings::GetSetting(std::string key)
	{
		return _settings[key];
	}
	int Settings::GetInt(std::string key)
	{
		return std::stoi(_settings[key]);
	}
	float Settings::GetFloat(std::string key)
	{
		return std::stof(_settings[key]);
	}
	void Settings::SetSetting(std::string key, std::string value)
	{
		_settings[key] = value;
	}
}