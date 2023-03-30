#pragma once
#include <jsoncpp/json/json.h>
#include "Common.h"

class GameEngine;
class IOSubsystem
{
public:
	IOSubsystem(std::string path_, GameEngine* gameEngine_);


private:
	std::string path;
	Json::Value fileData;

	GameEngine* gameEngine;
};

