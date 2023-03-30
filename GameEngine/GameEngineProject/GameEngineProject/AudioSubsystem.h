#pragma once

#include <SFML/Audio.hpp>

//Set Audio subsystem
class AudioSubsystem  {
public:
	AudioSubsystem() {};
	~AudioSubsystem() {};

	bool loadMusic() {
		
		//load music from file
		if (!music.openFromFile("../Music/bgMusic.ogg")) {
			std::cout << "Failed to load music file!" << std::endl;
			return false;
		}

		//loop the music
		music.setLoop(true);

		return true;
	}

	//play the music
	void playMusic() {
		music.play();
	}

private:
	sf::Music music;
};