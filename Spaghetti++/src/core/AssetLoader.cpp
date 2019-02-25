#include "core/AssetLoader.h"
#include <iostream>
#include <map>
#include "SFML/Audio.hpp"
namespace sge {
	AssetLoader::AssetLoader()
	{
	}


	AssetLoader::~AssetLoader()
	{
	}
	std::map<std::string, Mesh*> AssetLoader::_cached;
	std::map<std::string, Texture*> AssetLoader::_cachedT;
	std::map<std::string, Sound*> AssetLoader::_cachedS;

	Mesh* sge::AssetLoader::GetMesh(std::string path) //keeps pointers to texture objects. Todo: Remember how many components use them to delete if unused
	{
		BufferMesh(path);
		if (_cached[path] == NULL)
			return GetMesh("error.obj");
		return _cached[path];
	}

	void AssetLoader::BufferMesh(std::string path) {
		if (_cached.find(path) != _cached.end())
			return;// _cached[path];
		Mesh* mesh = Mesh::load(Settings::GetSetting("meshDir") + path);
		if (mesh == NULL) {
			std::cout << "Error loading mesh: " << Settings::GetSetting("meshDir") << path << std::endl;
			return;
		}
		_cached.insert(std::make_pair(path, mesh));
	}

	Texture * AssetLoader::GetTexture(std::string path)
	{
		BufferTexture(path);
		if (_cachedT[path] == NULL)
			return GetTexture("error.png");
		return _cachedT[path];
	}
	void AssetLoader::BufferTexture(std::string path)
	{
		if (_cachedT.find(path) != _cachedT.end())
			return;// _cached[path];
		Texture* tex = Texture::load(Settings::GetSetting("texDir") + path);
		if (tex == NULL) {
			std::cout << "Error loading Texture: " << path << std::endl;
			return;
		}
		_cachedT.insert(std::make_pair(path, tex));
	}

	Sound * AssetLoader::GetSound(std::string path)
	{
		BufferTexture(path);
		if (_cachedS[path] == NULL)
			return GetSound("error.wav");
		return _cachedS[path];
	}
	void AssetLoader::BufferSound(std::string path)
	{
		if (_cachedS.find(path) != _cachedS.end())
			return;// _cached[path];
		Texture* tex = Texture::load(Settings::GetSetting("sndDir") + path);
		if (tex == NULL) {
			std::cout << "Error loading Sound: " << path << std::endl;
			return;
		}
		_cachedT.insert(std::make_pair(path, tex));
	}
}