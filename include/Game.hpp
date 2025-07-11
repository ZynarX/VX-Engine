#include <iostream>
#include <cstring>
#include <vector>
#include <random>
#include <SDL.h>
#include "Player.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Trap.hpp"
#include "Struct.hpp"
#include "EntityComponentSystem.h"
#pragma once

class Game
{
private:
	int HEIGHT;
	int WIDTH;

	std::string filename;
	std::vector<SDL_Rect> MAP;
	Color background_colors;
	
	bool is_running;
	bool combat;

	bool COMBAT_ENABLED;
	bool COLLISION_ENABLED;

	int combat_entity_index;

	float FIXED_TIME_STEP;
	float FRAME_DELAY;

	Player* player;
	std::vector<Entity> entities;
	std::vector<Item> items;
	std::vector<Trap> traps;
	std::vector<Tile> TILES;

	void HandleInput(SDL_Event& event);
	void render(SDL_Renderer* renderer);
	void HandleMovement(float deltaTime);

	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool CheckCombat();

	void HandleCombat(Entity* entity, size_t entity_index);

	void Clear();
public:
	Game(std::string filepath, Player& player, std::vector<Entity> Entities, std::vector<Item> Items, std::vector<Trap> Traps, Color backgroundColors, int width, int height, bool combat, bool collision);
	bool run();
};
