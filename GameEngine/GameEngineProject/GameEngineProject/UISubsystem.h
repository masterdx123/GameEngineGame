#pragma once
#include <jsoncpp/json/json.h>
#include "Common.h"

class GameEngine;
class UISubsystem
{
public:
	UISubsystem(std::string path_, GameEngine* gameEngine_);


private:
	std::string path;
	Json::Value fileData;

	GameEngine* gameEngine;
};

