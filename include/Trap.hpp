#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include "EntityComponentSystem.h"
#pragma once

class Trap {
private:
	std::string Name;
	Position position;
	Color color;
public:
	Trap(std::string name, int x_position, int y_position, Color rgb);

	std::string get_name();
	Position get_position();
	Color get_color();
};
