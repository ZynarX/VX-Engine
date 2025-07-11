#include <iostream>
#include "Player.hpp"

Player::Player(std::string Name, int x_position, int y_position, int health, Color rgb, int damage, float speed)
{
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
	this->name = Name;
	this->transform.Position.X = x_position;
	this->transform.Position.Y = y_position;
	this->transform.Size.X = 100;
	this->transform.Size.Y = 100;
	this->Health = health;
	
	this->color.Red = rgb.Red;
	this->color.Green = rgb.Green;
	this->color.Blue = rgb.Blue;

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

	this->Damage += item.get_buff();


	std::cout << "--------------------------- Current Inventory ---------------------------\n";

	for (auto& pair : this->get_items())
	{
		std::cout << pair.first << " x" << pair.second << std::endl;
	}

	std::cout << "-------------------------------------------------------------------------\n";

}
void Player::move(int x_steps, int y_steps)
{
	this->transform.Position.X += x_steps;
	this->transform.Position.Y += y_steps;
}

void Player::stop_movement()
{
	this->move_up = false;
	this->move_down = false;
	this->move_right = false;
	this->move_left = false;
}

std::string Player::get_name()
{
	return this->name;
}
Position Player::get_position()
{
	return this->transform.Position;
}
Size Player::get_size()
{
	return this->transform.Size;
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
Color Player::get_color()
{
	return this->color;
}
std::vector<Item> Player::get_inventory()
{
	return this->Inventory;
}
std::map<std::string, int> Player::get_items()
{
	return this->Items;
}
