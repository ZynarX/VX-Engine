#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "EntityComponentSystem.h"
#pragma once

class Item {
private:
	std::string Name;
	Position position;
	Color color;
	int buff;
public:
	Item(std::string name, int x_position, int y_position, int buff, Color rgb);
	
	std::string get_name();
	Position get_position();
	int get_buff();
	Color get_color();
};
