#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include "Vector2.h"

enum class ComponentType { Behaviour, Physics, BoxShape2D, UI, Gameplay, Network, Unassigned };
enum class SubsystemType { Graphics, Physics , UI, Gameplay, Network, Unassigned};
enum class EventType { MoveUp, MoveDown, MoveLeft, MoveRight, Movement, SetPosition, Shot, Unassigned };
enum class BehaviourType { Patrol, Hunt, Unassigned };

