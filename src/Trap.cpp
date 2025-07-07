#include "Trap.hpp"

Trap::Trap(std::string name, int x_position, int y_position, std::vector<Uint32> rgb)
{
	this->Name = name;
	this->XPos = x_position;
	this->YPos = y_position;

	for (Uint32 color : rgb)
	{
		this->RGB.push_back(color);
	}
}

std::string Trap::get_name()
{
	return this->Name;
}
int Trap::get_xposition()
{
	return this->XPos;
}
int Trap::get_yposition()
{
	return this->YPos;
}
std::vector<Uint32> Trap::get_color()
{
	return this->RGB;
}
