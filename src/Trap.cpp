#include <iostream>
#include "Trap.hpp"

Trap::Trap(std::string name, int x_position, int y_position, Color rgb)
{
	this->Name = name;
	this->position.X = x_position;
	this->position.Y = y_position;
	this->color.Red = rgb.Red;
	this->color.Green = rgb.Green;
	this->color.Blue = rgb.Blue;
}

std::string Trap::get_name()
{
	return this->Name;
}
Position Trap::get_position()
{
	return this->position;
}
Color Trap::get_color()
{
	return this->color;
}
