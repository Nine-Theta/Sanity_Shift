#pragma once
#include <map>
#include <string>
#include <iterator>
#include "SFML/Audio.hpp"
namespace sge {
	class SoundManager //Super simple audio tool. Pass file name as string to play. Tool will load and cache for you. Quick solution to program without memory issues
	{
	public:
		SoundManager();
		~SoundManager();
		static void PlaySound(std::string name);
		static void PlayBGM(std::string name);
		static void StopBGM();
	private:
		static std::map<std::string, sf::Sound*> _cached;
		static void playBuffer(sf::Sound* toPlay);
		static sf::Music music;
	};

}