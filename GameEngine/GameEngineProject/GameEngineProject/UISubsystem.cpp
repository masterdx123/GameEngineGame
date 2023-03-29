#include "UISubsystem.h"
#include <fstream>
UISubsystem::UISubsystem(std::string path_) : path(path_)
{
	std::ifstream fileStream(path);

	fileStream >> fileData;
	fileStream.close();

	std::string name = fileData["Name"].asString();
	
	std::cout << name << std::endl;
}
