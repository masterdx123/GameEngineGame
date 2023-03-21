#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

enum class ComponentType { Behaviour, Physics, BoxShape2D, IO, AI, Unassigned };
enum class SubsystemType { Graphics, Physics , IO, AI, Unassigned};
enum class EventType { MoveUp, MoveDown, MoveLeft, MoveRight, Movement, Unassigned };
enum class BehaviourType { Patrol, Hunt, Unassigned };