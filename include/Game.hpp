#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <SDL.h>
#include "Player.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Trap.hpp"
#include "Struct.hpp"

class Game
{
private:
	int HEIGHT;
	int WIDTH;

	std::string filename;
	std::vector<SDL_Rect> MAP;
	std::vector<Uint32> background_colors;
	
	bool is_running;
	bool combat;

	bool COMBAT_ENABLED;
	bool COLLISION_ENABLED;

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

	void HandleCombat(Entity& entity, size_t entity_index);
public:
	Game(std::string filepath, Player& player, std::vector<Entity> Entities, std::vector<Item> Items, std::vector<Trap> Traps, std::vector<Uint32> backgroundColors, int width, int height, bool combat, bool collision);
	bool run();
};
