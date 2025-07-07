#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#pragma once

class Item {
private:
	std::string Name;
	int XPos;
	int YPos;
	std::vector<Uint32> RGB;
public:
	Item(std::string name, int x_position, int y_position, std::vector<Uint32> rgb);
	
	std::string get_name();
	int get_xposition();
	int get_yposition();
	std::vector<Uint32> get_color();
};
