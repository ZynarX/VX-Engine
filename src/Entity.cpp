#include <iostream>
#include "Entity.hpp"

Entity::Entity(std::string Name, int x_position, int y_position, int health, Color rgb, Hostility hostility, float speed)
{
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
	this->name = Name;
	this->position.X = x_position;
	this->position.Y = y_position;
	this->color.Red = rgb.Red;
	this->color.Green = rgb.Green;
	this->color.Blue = rgb.Blue;
	this->Health = health;

	this->hostility.mode = hostility.mode;
	this->hostility.amount = hostility.amount;
	this->Speed = speed;
}

void Entity::take_damage(int amount)
{
	if (amount > 0)
	{
		if (amount >= this->Health)
		{
			this->Health -= this->Health;
		}
		else
		{
			this->Health -= amount;
		}
	}
	else
	{
		std::cout << "Damage is less than or equal to 0!\n";
	}
}
void Entity::move(int x_steps, int y_steps)
{
	this->position.X += x_steps;
	this->position.Y += y_steps;
}

void Entity::stop_movement()
{
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
}

std::string Entity::get_name()
{
	return this->name;
}
Position Entity::get_position()
{
	return this->position;
}
int Entity::get_health()
{
	return this->Health;
}
int Entity::get_mode()
{
	return this->hostility.mode;
}
int Entity::get_damage()
{
	return this->hostility.amount;
}
float Entity::get_speed()
{
	return this->Speed;
}
Color Entity::get_color()
{
	return this->color;
}
