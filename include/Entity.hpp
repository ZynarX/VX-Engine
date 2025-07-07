#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#pragma once

class Entity {
private:
	std::string name;
	int XPos;
	int YPos;
	int Health;
	int Damage;
	float Speed;
	std::vector<Uint32> RGB;
public:
	bool move_up;
	bool move_down;
	bool move_right;
	bool move_left;

	Entity(std::string Name, int x_position, int y_position, int health, std::vector<Uint32> rgb, int damage, float speed);

	void take_damage(int amount);
	void move(int x_steps, int y_steps);

	std::string get_name();
	int get_xposition();
	int get_yposition();
	int get_health();
	int get_damage();
	float get_speed();
	std::vector<Uint32> get_color();
};
