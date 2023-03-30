#pragma once

#include <SFML/Audio.hpp>

class AudioSubsystem  {
public:
	AudioSubsystem() {};
	~AudioSubsystem() {};

	bool loadMusic() {
		
		if (!music.openFromFile("../Music/bgMusic.ogg")) {
			std::cout << "Failed to load music file!" << std::endl;
			return false;
		}

		music.setLoop(true);

		return true;
	}

	void playMusic() {
		music.play();
	}
private:
	sf::Music music;
};