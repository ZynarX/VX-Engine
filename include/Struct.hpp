#include <iostream>
#include <SDL.h>
#include "EntityComponentSystem.h"
#pragma once

struct Tile {
	int Type;
	Position position;
	Color color;
};
