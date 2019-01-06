#include "SoundManager.h"
#include <iostream>


namespace sge {
	SoundManager::SoundManager()
	{
	}


	SoundManager::~SoundManager()
	{
	}
	std::map<std::string, sf::Sound*> SoundManager::_cached;
	void sge::SoundManager::PlaySound(std::string name)
	{
		if (_cached.find(name) != _cached.end()) {
			_cached[name]->play();
			return;
		};
		sf::SoundBuffer* sound = new sf::SoundBuffer(); //sf::Sound stores the buffer anyway, this is done so that it won't get deleted out of scope. It's a form of irreversible caching, no memory leak ;)
		if (!sound->loadFromFile(name)) {
			std::cout << "Error loading sound file: " << name << std::endl;
			return;
		}
		else {
			std::cout << "Successfully loaded sound file: " << name << std::endl;
		}
		sf::Sound* snd = new sf::Sound();
		snd->setBuffer(*sound);
		_cached.insert(std::make_pair(name, snd));
		snd->play(); //Not optimal, sounds get cut off when played again. Will work with multiple objects in the future and delete only when done playing
	}
	sf::Music SoundManager::music;
	void SoundManager::PlayBGM(std::string name)
	{
		if (!music.openFromFile(name))
			return; // error
		music.play();
	}
	void SoundManager::StopBGM()
	{
		music.stop();
	}
	void SoundManager::playBuffer(sf::Sound * toPlay)
	{
		sf::Sound* snd = new sf::Sound();
		//snd->setBuffer(*toPlay);
		snd->play();
	}
}