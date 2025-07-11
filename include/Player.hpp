#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SDL.h>
#include "Item.hpp"
#include "Entity.hpp"
#include "EntityComponentSystem.h"
#pragma once

class Player {
private:
	std::string name;
	Transform transform;
	int Health;
	Color color;
	int Damage;
	float Speed;
	std::vector<Item> Inventory;
	std::map<std::string, int> Items;
public:
	bool move_up;
	bool move_down;
	bool move_right;
	bool move_left;

	Player(std::string name, int x_position, int y_position, int health, Color rgb, int damage, float speed);
	
	void take_damage(int amount);
	void pickup(Item item);
	void move(int x_steps, int y_steps);

	void stop_movement();

	std::string get_name();
	Position get_position();
	Size get_size();
	int get_health();
	int get_damage();
	float get_speed();
	Color get_color();
	std::vector<Item> get_inventory();
	std::map<std::string, int> get_items();
};
