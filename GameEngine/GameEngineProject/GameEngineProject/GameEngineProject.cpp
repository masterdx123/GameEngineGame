// GameEngineProject.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "GraphicsSubsystem.h"
#include "AudioSubsystem.h"

using namespace std;

extern GameEngine* myGame = new GameEngine();
AudioSubsystem audio;

int main() {
	
	//load and play music
	if (audio.loadMusic()) {
		audio.playMusic();
	}

   bool running = true;

   //run the game
   while (running)
   {
       running = myGame->Update();
   }

   delete myGame;



    return 0;
}


