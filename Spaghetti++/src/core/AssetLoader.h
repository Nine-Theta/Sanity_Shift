#pragma once
#include "SFML/Graphics.hpp"
#include "core/Mesh.hpp"
#include "core/Texture.hpp"
#include "core/Sound.hpp"
#include "Settings.h"
#include <map>
#include <string>
#include <iterator>
namespace sge {
	class AssetLoader
	{
	public:
		AssetLoader();
		~AssetLoader();
		static Mesh* GetMesh(std::string path); //this will return the mesh if it was previously loaded or buffered, as all mesh are kept in memory in order to be reusable to no stutter
		static void BufferMesh(std::string path);

		static Texture* GetTexture(std::string path); //this will return the mesh if it was previously loaded or buffered, as all mesh are kept in memory in order to be reusable to no stutter
		static void BufferTexture(std::string path);

		static Sound* GetSound(std::string path); //this will return the mesh if it was previously loaded or buffered, as all mesh are kept in memory in order to be reusable to no stutter
		static void BufferSound(std::string path);
	private:
		static std::map<std::string, Mesh*> _cached;
		static std::map<std::string, Texture*> _cachedT;
		static std::map<std::string, Sound*> _cachedS;
	};
}