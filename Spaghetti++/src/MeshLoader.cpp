#include "SpriteLoader.h"
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
	std::map<std::string, sf::Texture*> AssetLoader::_cached;

	sf::Texture* sge::AssetLoader::GetTexture(std::string path) //keeps pointers to texture objects. Todo: Remember how many components use them to delete if unused
	{
		if (_cached.find(path) != _cached.end())
			return _cached[path];
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(path)) {
			std::cout << "Error loading texture: " << path << std::endl;
			return NULL;
		}
		_cached.insert(std::make_pair(path, texture));
		return texture;
	}
}