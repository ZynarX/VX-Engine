#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SDL.h>
#include "Item.hpp"
#include "Entity.hpp"
#pragma once

class Player {
private:
	std::string name;
	int XPos;
	int YPos;
	int Width;
	int Height;
	int Health;
	std::vector<Uint32> RGB;
	int Damage;
	float Speed;
	std::vector<Item> Inventory;
	std::map<std::string, int> Items;
public:
	bool move_up;
	bool move_down;
	bool move_right;
	bool move_left;

	Player(std::string name, int x_position, int y_position, int health, std::vector<Uint32> rgb, int damage, float speed);
	
	void take_damage(int amount);
	void pickup(Item item);
	void move(int x_steps, int y_steps);

	std::string get_name();
	int get_xposition();
	int get_yposition();
	int get_width();
	int get_height();
	int get_health();
	int get_damage();
	float get_speed();
	std::vector<Uint32> get_color();
	std::vector<Item> get_inventory();
	std::map<std::string, int> get_items();
};
