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

	Mesh* sge::AssetLoader::GetMesh(std::string path) //keeps pointers to texture objects. Todo: Remember how many components use them to delete if unused
	{
		BufferMesh(path);
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
		BufferMesh(path);
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
}