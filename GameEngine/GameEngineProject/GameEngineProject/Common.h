#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

enum class ComponentType { Behaviour, Physics, BoxShape2D, IO, Unassigned };
enum class SubsystemType { Graphics, Physics , IO, Unassigned};
enum class EventType { MoveUp, MoveDown, MoveLeft, MoveRight, Unassigned };