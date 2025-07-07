#include <iostream>
#include "Entity.hpp"

Entity::Entity(std::string Name, int x_position, int y_position, int health, std::vector<Uint32> rgb, int damage, float speed)
{
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
	this->name = Name;
	this->XPos = x_position;
	this->YPos = y_position;
	this->Health = health;

	for (Uint32& item : rgb)
	{
		this->RGB.push_back(item);
	}

	this->Damage = damage;
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
	this->XPos += x_steps;
	this->YPos += y_steps;
}

std::string Entity::get_name()
{
	return this->name;
}
int Entity::get_xposition()
{
	return this->XPos;
}
int Entity::get_yposition()
{
	return this->YPos;
}
int Entity::get_health()
{
	return this->Health;
}
int Entity::get_damage()
{
	return this->Damage;
}
float Entity::get_speed()
{
	return this->Speed;
}
std::vector<Uint32> Entity::get_color()
{
	return this->RGB;
}
