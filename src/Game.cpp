#include <iostream>
#include "Game.hpp"

Game::Game(std::string filepath, Player& player, std::vector<Entity> Entities, std::vector<Item> Items, std::vector<Trap> Traps, Color backgroundColors, int width, int height, bool combat, bool collision)
{
	this->filename = filepath;
	this->player = &player;

	this->WIDTH = width;
	this->HEIGHT = height;

	this->COMBAT_ENABLED = combat;
	this->COLLISION_ENABLED = collision;

	this->combat_entity_index = -1;

	this->background_colors.Red = backgroundColors.Red;
	this->background_colors.Green = backgroundColors.Green;
	this->background_colors.Blue = backgroundColors.Blue;

	this->combat = false;
	this->is_running = true;

	for (Entity& entity : Entities)
	{
		this->entities.push_back(entity);
	}

	for (Item& item : Items)
	{
		this->items.push_back(item);
	}

	for (Trap& trap : Traps)
	{
		this->traps.push_back(trap);
	}

	this->FIXED_TIME_STEP = 1.0f / 60.0f;
	this->FRAME_DELAY = 1000.0f / 60.0f;
}

bool Game::CheckCollision(SDL_Rect a, SDL_Rect b)
{
	if (this->combat == false)
	{
		int aLeft = a.x;
		int aRight = a.x + a.w;
		int aTop = a.y;
		int aBottom = a.y + a.h;

		int bLeft = b.x;
		int bRight = b.x + b.w;
		int bTop = b.y;
		int bBottom = b.y + b.h;

		return ((aLeft < bRight && aRight > bLeft) && (aBottom > bTop && aTop < bBottom));
	}
	else
	{
		return false;
	}
}

void Game::render(SDL_Renderer* renderer)
{
	if (this->combat == false)
	{
		SDL_SetRenderDrawColor(renderer, this->background_colors.Red, this->background_colors.Green, this->background_colors.Blue, 255);
		SDL_RenderClear(renderer);

		for (Tile tile : this->TILES)
		{
			SDL_SetRenderDrawColor(renderer, tile.color.Red, tile.color.Green, tile.color.Blue, 255);
			SDL_Rect tileRect = { tile.position.X, tile.position.Y, 100, 100 };

			if (tile.Type == 1)
			{
				SDL_RenderFillRect(renderer, &tileRect);
			}
			else if (tile.Type == 2)
			{
				SDL_RenderDrawRect(renderer, &tileRect);
			}
		}

		SDL_Rect playerRectangle = { (int)this->player->get_position().X, (int)this->player->get_position().Y, this->player->get_size().X, this->player->get_size().Y };

		SDL_SetRenderDrawColor(renderer, this->player->get_color().Red, this->player->get_color().Green, this->player->get_color().Blue, 255);
		SDL_RenderFillRect(renderer, &playerRectangle);

		for (size_t i = 0; i < this->items.size(); i++)
		{
			SDL_Rect itemRectangle = { (int)items[i].get_position().X, (int)items[i].get_position().Y, 50, 50 };

			SDL_SetRenderDrawColor(renderer, items[i].get_color().Red, items[i].get_color().Green, items[i].get_color().Blue, 255);
			SDL_RenderFillRect(renderer, &itemRectangle);

			if (CheckCollision(playerRectangle, itemRectangle))
			{
				this->player->pickup(items[i]);
				this->items.erase(this->items.begin() + i);
			}
		}

		for (size_t i = 0; i < this->traps.size(); i++)
		{
			SDL_Rect trapRectangle = { (int)traps[i].get_position().X, (int)traps[i].get_position().Y, 25, 25 };

			SDL_SetRenderDrawColor(renderer, traps[i].get_color().Red, traps[i].get_color().Green, traps[i].get_color().Blue, 255);
			SDL_RenderFillRect(renderer, &trapRectangle);

			if (CheckCollision(playerRectangle, trapRectangle))
			{
				std::cout << "Player stepped into a trap!" << std::endl;
				this->player->take_damage(5);

				this->traps.erase(this->traps.begin() + i);
			}
		}

		for (size_t i = 0; i < this->entities.size(); i++)
		{
			SDL_Rect entityRectangle = { (int)this->entities[i].get_position().X, (int)this->entities[i].get_position().Y, 75, 75 };

			SDL_SetRenderDrawColor(renderer, this->entities[i].get_color().Red, this->entities[i].get_color().Green, this->entities[i].get_color().Blue, 255);
			SDL_RenderFillRect(renderer, &entityRectangle);
		}

		SDL_RenderPresent(renderer);
	}
}

bool Game::CheckCombat()
{
	if (this->COMBAT_ENABLED && this->combat == false)
	{
		SDL_Rect playerRectangle = { (int)this->player->get_position().X, (int)this->player->get_position().Y, this->player->get_size().X, this->player->get_size().Y };

		for (size_t i = 0; i < this->entities.size(); i++)
		{
			if (this->entities[i].get_mode() == 1)
			{
				SDL_Rect curEntityRect = { this->entities[i].get_position().X, this->entities[i].get_position().Y, 75, 75 };

				if (this->CheckCollision(playerRectangle, curEntityRect))
				{
					this->combat_entity_index = i;
					return true;
				}
			}
		}
	}

	return false;
}

void Game::HandleInput(SDL_Event& event)
{
	if (this->combat == false)
	{
		if (event.type == SDL_QUIT)
		{
			this->is_running = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				this->is_running = false;
			}
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
			{
				this->player->move_up = true;
			}
			if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
			{
				this->player->move_down = true;
			}
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
			{
				this->player->move_left = true;
			}
			if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
			{
				this->player->move_right = true;
			}
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
			{
				this->player->move_up = false;
			}
			if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
			{
				this->player->move_down = false;
			}
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
			{
				this->player->move_left = false;
			}
			if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
			{
				this->player->move_right = false;
			}
		}
	}
}

void Game::HandleMovement(float deltaTime)
{
	if (this->combat == false)
	{
		if (this->player->move_up)
		{
			if (this->player->get_position().Y - (this->player->get_speed() * this->FIXED_TIME_STEP) >= -1)
				this->player->move(0, -(this->player->get_speed() * this->FIXED_TIME_STEP));
		}
		if (this->player->move_down)
		{
			if ((this->player->get_position().Y - (this->player->get_speed() * this->FIXED_TIME_STEP)) + this->player->get_size().Y <= this->HEIGHT)
				this->player->move(0, (this->player->get_speed() * this->FIXED_TIME_STEP));
		}
		if (this->player->move_right)
		{
			if ((this->player->get_position().X - (this->player->get_speed() * this->FIXED_TIME_STEP)) + this->player->get_size().X <= this->WIDTH)
				this->player->move((this->player->get_speed() * this->FIXED_TIME_STEP), 0);
		}
		if (this->player->move_left)
		{
			if (this->player->get_position().X - (this->player->get_speed() * this->FIXED_TIME_STEP) >= -1)
				this->player->move(-(this->player->get_speed() * this->FIXED_TIME_STEP), 0);
		}

		for (Entity& entity : this->entities)
		{

			if (entity.get_mode() == 1)
			{
				int entityXCenter = entity.get_position().X + (75 / 2) + 1;
				int entityYCenter = entity.get_position().Y + (75 / 2) + 1;
				int playerXCenter = this->player->get_position().X + (this->player->get_size().X / 2);
				int playerYCenter = this->player->get_position().Y + (this->player->get_size().Y / 2);

				int XDiffer = playerXCenter - entityXCenter;
				int YDiffer = playerYCenter - entityYCenter;

				int distance = sqrt(pow(XDiffer, 2) + pow(YDiffer, 2));

				int leastDistance = sqrt(pow(this->WIDTH, 2) + pow(this->HEIGHT, 2)) / 3;

				if (distance > leastDistance)
				{
					srand(time(NULL));
					int randomXChoice = 1 + rand() % 2;
					int randomYChoice = 1 + rand() % 2;

					if (randomXChoice == 1)
					{
						entity.move_right = true;
					}
					else if (randomXChoice == 2)
					{
						entity.move_left = true;
					}
					if (randomYChoice == 1)
					{
						entity.move_up = true;
					}
					else if (randomYChoice == 2)
					{
						entity.move_down = true;
					}
				}
				else
				{
					if (entityYCenter > playerYCenter)
					{
						entity.move_up = true;
					}
					else if (entityYCenter < playerYCenter)
					{
						entity.move_down = true;
					}
					if (entityXCenter < playerXCenter)
					{
						entity.move_right = true;
					}
					else if (entityXCenter > playerXCenter)
					{
						entity.move_left = true;
					}
				}
			}
			else if (entity.get_mode() == 2)
			{
				srand(time(NULL));
				int randomXChoice = 1 + rand() % 2;
				int randomYChoice = 1 + rand() % 2;

				if (randomXChoice == 1)
				{
					entity.move_right = true;
				}
				else if (randomXChoice == 2)
				{
					entity.move_left = true;
				}
				if (randomYChoice == 1)
				{
					entity.move_up = true;
				}
				else if (randomYChoice == 2)
				{
					entity.move_down = true;
				}
			}

			if (entity.move_up)
			{
				if (entity.get_position().Y - (entity.get_speed() * this->FIXED_TIME_STEP) >= -1)
					entity.move(0, -(entity.get_speed() * this->FIXED_TIME_STEP));
			}
			if (entity.move_down)
			{
				if ((entity.get_position().Y - (entity.get_speed() * this->FIXED_TIME_STEP)) + 75 <= this->HEIGHT)
					entity.move(0, entity.get_speed() * this->FIXED_TIME_STEP);
			}
			if (entity.move_right)
			{
				if ((entity.get_position().X - (entity.get_speed() * this->FIXED_TIME_STEP)) + 75 <= this->WIDTH)
					entity.move(entity.get_speed() * this->FIXED_TIME_STEP, 0);
			}
			if (entity.move_left)
			{
				if (entity.get_position().X - (entity.get_speed() * this->FIXED_TIME_STEP) >= -1)
					entity.move(-(entity.get_speed() * this->FIXED_TIME_STEP), 0);
			}

			entity.move_up = false;
			entity.move_down = false;
			entity.move_right = false;
			entity.move_left = false;
		}
	}
}

void Game::HandleCombat(Entity* entity, size_t entityIndex)
{
	std::cout << "in combat!" << std::endl;

	this->player->stop_movement();

	for (Entity& entity : this->entities)
	{
		entity.stop_movement();
	}

	bool is_alive = true;
	char choice = '\0';

	std::cout << "--------------------------------- Combat --------------------------------\n";

	do
	{
		std::cout << "-- CUR STATUS:\n- Player Health: " << this->player->get_health() << "\n- " << entity->get_name() << " Health: " << entity->get_health() << std::endl;
		std::cout << "Would you like to [F]ight or [N]ot?: ";
		std::cin >> choice;

		choice = toupper(choice);

		if (choice == 'F')
		{
			entity->take_damage(this->player->get_damage());

			std::cout << "Player deals " << this->player->get_damage() << " damage to " << entity->get_name() << "!" << std::endl;
		}
		else if (choice == 'N')
		{
			std::cout << "Player chose not to fight " << entity->get_name() << std::endl;
		}

		this->player->take_damage(entity->get_damage());

		std::cout << entity->get_name() << " deals " << entity->get_damage() << " damage to player!" << std::endl;

		if (entity->get_health() <= 0)
		{
			is_alive = false;
		}
		if (this->player->get_health() <= 0)
		{
			is_alive = false;
		}

	} while (is_alive);

	if (this->player->get_health() <= 0)
	{
		std::cout << "Player has fallen to " << entity->get_name() << " :(" << std::endl;
		this->is_running = false;
	}
	else
	{
		this->entities.erase(this->entities.begin() + entityIndex);
	}

	this->combat = false;

	std::cout << "-------------------------------------------------------------------------" << std::endl;

	this->player->stop_movement();

	for (Entity& entity : this->entities)
	{
		entity.stop_movement();
	}

	this->combat_entity_index = -1;
}

void Game::Clear()
{
	this->player = nullptr;

	this->MAP.clear();

	this->entities.clear();
	this->items.clear();
	this->traps.clear();
	this->TILES.clear();
}

bool Game::run()
{
	SDL_Init(SDL_INIT_VIDEO);

	std::string string_title = "VX Engine (" + this->filename + ")";

	const char* title = string_title.c_str();

	SDL_Window* window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->WIDTH, this->HEIGHT,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		std::cout << "Couldn't initialize renderer..." << std::endl;
		return false;
	}

	SDL_Event event;

	Uint32 previousTick = SDL_GetTicks();
	float accumulator = 0.0f;

	while (this->is_running)
	{
		if (this->combat == false)
		{
			if (!this->combat)
			{
				if (this->CheckCombat())
				{
					std::cout << "Combat check success!" << std::endl;
					this->combat = true;
					this->HandleCombat(&this->entities[this->combat_entity_index], this->combat_entity_index);
				}
			}

			while (SDL_PollEvent(&event))
			{
				this->HandleInput(event);
			}
			
			Uint32 currentTick = SDL_GetTicks();
			float deltaTime = (currentTick - previousTick) / 1000.0f;
			previousTick = currentTick;

			accumulator += deltaTime;

			while (accumulator >= this->FIXED_TIME_STEP)
			{
				HandleMovement(deltaTime);
				accumulator -= this->FIXED_TIME_STEP;
			}

			this->render(renderer);

			Uint32 finalTick = SDL_GetTicks();

			if (finalTick - currentTick < this->FRAME_DELAY)
			{
				SDL_Delay(this->FRAME_DELAY - (finalTick - currentTick));
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	this->Clear();
	SDL_Quit();

	return true;
}
