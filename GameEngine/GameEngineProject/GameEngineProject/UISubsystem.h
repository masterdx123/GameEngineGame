#pragma once
#include <jsoncpp/json/json.h>
#include "Common.h"


class UISubsystem
{
public:
	UISubsystem(std::string path_);


private:
	std::string path;
	Json::Value fileData;
};

