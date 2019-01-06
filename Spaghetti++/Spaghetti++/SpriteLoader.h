#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include <iterator>
namespace sge {
	class SpriteLoader
	{
	public:
		SpriteLoader();
		~SpriteLoader();
		static sf::Texture* GetTexture(std::string path); //this will return the texture if it was previously loaded, as all textures are kept in memory in order to be reusable to no stutter
	private:
		static std::map<std::string, sf::Texture*> _cached;
	};
}