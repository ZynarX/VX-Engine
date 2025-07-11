#include <iostream>
#include "Item.hpp"

Item::Item(std::string name, int x_position, int y_position, int buff, Color rgb)
{
	this->Name = name;
	this->position.X = x_position;
	this->position.Y = y_position;
	this->buff = buff;
	
	this->color.Red = rgb.Red;
	this->color.Green = rgb.Green;
	this->color.Blue = rgb.Blue;
}

std::string Item::get_name()
{
	return this->Name;
}
Position Item::get_position()
{
	return this->position;
}
int Item::get_buff()
{
	return this->buff;
}
Color Item::get_color()
{
	return this->color;
}
