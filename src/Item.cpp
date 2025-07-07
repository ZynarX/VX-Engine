#include <iostream>
#include "Item.hpp"

Item::Item(std::string name, int x_position, int y_position, std::vector<Uint32> rgb)
{
	this->Name = name;
	this->XPos = x_position;
	this->YPos = y_position;

	for (Uint32& item : rgb)
	{
		this->RGB.push_back(item);
	}
}

std::string Item::get_name()
{
	return this->Name;
}
int Item::get_xposition()
{
	return this->XPos;
}
int Item::get_yposition()
{
	return this->YPos;
}
std::vector<Uint32> Item::get_color()
{
	return this->RGB;
}
