#include <iostream>
#include "Player.hpp"

Player::Player(std::string Name, int x_position, int y_position, int health, std::vector<Uint32> rgb, int damage, float speed)
{
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
	this->name = Name;
	this->XPos = x_position;
	this->YPos = y_position;
	this->Width = 100;
	this->Height = 100;
	this->Health = health;
	
	for (Uint32 &item : rgb)
	{
		this->RGB.push_back(item);
	}

	this->Damage = damage;
	this->Speed = speed;
}

void Player::take_damage(int amount)
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
void Player::pickup(Item item)
{
	this->Inventory.push_back(item);
	this->Items[item.get_name()] = this->Items[item.get_name()] + 1;


	std::cout << "---- Current Player Inventory ----\n";

	for (auto& pair : this->get_items())
	{
		std::cout << pair.first << " x" << pair.second << std::endl;
	}

	std::cout << "----------------------------------\n";

}
void Player::move(int x_steps, int y_steps)
{
	this->XPos += x_steps;
	this->YPos += y_steps;
}

std::string Player::get_name()
{
	return this->name;
}
int Player::get_xposition()
{
	return this->XPos;
}
int Player::get_yposition()
{
	return this->YPos;
}
int Player::get_width()
{
	return this->Width;
}
int Player::get_height()
{
	return this->Height;
}
int Player::get_health()
{
	return this->Health;
}
int Player::get_damage()
{
	return this->Damage;
}
float Player::get_speed()
{
	return this->Speed;
}
std::vector<Uint32> Player::get_color()
{
	return this->RGB;
}
std::vector<Item> Player::get_inventory()
{
	return this->Inventory;
}
std::map<std::string, int> Player::get_items()
{
	return this->Items;
}
