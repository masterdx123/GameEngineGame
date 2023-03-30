#include "IOSubsystem.h"
#include <fstream>
#include "GameEngine.h"
#include "GameObject.h"
#include "GraphicsSubsystem.h"
#include "PhysicsComponent.h"
#include "UIComponent.h"
#include "NetComponent.h"
#include "GameplayComponent.h"

IOSubsystem::IOSubsystem(std::string path_, GameEngine* gameEngine_) : path(path_), gameEngine(gameEngine_)
{
	std::ifstream fileStream(path);

	fileStream >> fileData;
	fileStream.close();

	Json::Value objects = fileData["objects"];
	for (const auto& obj : objects) {


		gameEngine->gameObjects->push_back(new GameObject(obj["name"].asString()));

		//std::cout << obj["name"].asString() << std::endl;
		GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(gameEngine->subsystems->at(0));

		std::vector<Vector2> enemyWaypoints = { Vector2(1.0f, -1.0f), Vector2(3.0f,-1.0f) };

		//std::cout << obj["GraphicsComponent"].asBool() << std::endl;
		//std::cout << obj["IOComponent"].asBool() << std::endl;

		if (obj["GraphicsComponent"].asBool()) {
			BoxShape2D* playerBoxShape = new BoxShape2D(gameEngine->gameObjects->back(), gameEngine->subsystems->at(0), tempptr->GetWindow(), Vector2(obj["posX"].asFloat(), obj["posY"].asFloat()), Vector2(obj["scaleX"].asFloat(), obj["scaleY"].asFloat()), obj["texture"].asString());
			Component* a = gameEngine->subsystems->at(0)->AddComponent(playerBoxShape);
			gameEngine->gameObjects->back()->AddComponent(a);
		}	
		if (obj["PhysicsComponent"].asBool()) {
			PhysicsComponent* playerPhysics = new PhysicsComponent(gameEngine->gameObjects->back(), gameEngine->subsystems->at(1), obj["halfWidth"].asFloat());
			gameEngine->gameObjects->back()->AddComponent(gameEngine->subsystems->at(1)->AddComponent(playerPhysics));
		}
		if (obj["UIComponent"].asBool()) {
			UIComponent* playerIO = new UIComponent(gameEngine->gameObjects->back(), gameEngine->subsystems->at(2));
			gameEngine->gameObjects->back()->AddComponent(gameEngine->subsystems->at(2)->AddComponent(playerIO));
		}
		if (obj["GameplayComponent"].asBool())
		{
			GameplayComponent* enemyAI = new GameplayComponent(gameEngine->gameObjects->back(), gameEngine->subsystems->at(3), enemyWaypoints);
			gameEngine->gameObjects->back()->AddComponent(gameEngine->subsystems->at(3)->AddComponent(enemyAI));
		}		
		if (obj["NetComponent"].asBool()) {
			NetComponent* player1Network = new NetComponent(gameEngine->gameObjects->back(), gameEngine->subsystems->at(4));
			gameEngine->gameObjects->back()->AddComponent(gameEngine->subsystems->at(4)->AddComponent(player1Network));
		}
				
	}
}
