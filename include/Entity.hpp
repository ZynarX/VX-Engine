#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "EntityComponentSystem.h"
#pragma once

class Entity {
private:
	std::string name;
	Position position;
	Hostility hostility;
	Color color;
	int Health;
	float Speed;
public:
	bool move_up;
	bool move_down;
	bool move_right;
	bool move_left;

	Entity(std::string Name, int x_position, int y_position, int health, Color rgb, Hostility hostility, float speed);

	void take_damage(int amount);
	void move(int x_steps, int y_steps);

	void stop_movement();

	std::string get_name();
	Position get_position();
	int get_health();
	int get_mode();
	int get_damage();
	float get_speed();
	Color get_color();
};
