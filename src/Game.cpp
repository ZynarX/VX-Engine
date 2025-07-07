#include <iostream>
#include "Game.hpp"

Game::Game(std::string filepath, Player& player, std::vector<Entity> Entities, std::vector<Item> Items, std::vector<Trap> Traps, std::vector<Uint32> backgroundColors, int width, int height, bool combat, bool collision)
{
	this->filename = filepath;
	this->player = &player;

	this->WIDTH = width;
	this->HEIGHT = height;

	this->COMBAT_ENABLED = combat;
	this->COLLISION_ENABLED = collision;

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

	for (Uint32& color : backgroundColors)
	{
		this->background_colors.push_back(color);
	}

	this->FIXED_TIME_STEP = 1.0f / 60.0f;
	this->FRAME_DELAY = 1000.0f / 60.0f;
}

bool Game::CheckCollision(SDL_Rect a, SDL_Rect b)
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

void Game::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, this->background_colors[0], this->background_colors[1], this->background_colors[2], 255);
	SDL_RenderClear(renderer);

	for (Tile& tile : this->TILES)
	{
		SDL_SetRenderDrawColor(renderer, tile.Red, tile.Green, tile.Blue, tile.Alpha);
		SDL_Rect tileRect = { tile.X, tile.Y, 100, 100 };
		
		if (tile.Type == 1)
		{
			SDL_RenderFillRect(renderer, &tileRect);
		}
		else if (tile.Type == 2)
		{
			SDL_RenderDrawRect(renderer, &tileRect);
		}
	}

	SDL_Rect playerRectangle = { (int)this->player->get_xposition(), (int)this->player->get_yposition(), this->player->get_width(), this->player->get_height()};

	SDL_SetRenderDrawColor(renderer, this->player->get_color()[0], this->player->get_color()[1], this->player->get_color()[2], 255);
	SDL_RenderFillRect(renderer, &playerRectangle);

	for (size_t i = 0; i < this->entities.size(); i++)
	{
		SDL_Rect entityRectangle = { (int)entities[i].get_xposition(), (int)entities[i].get_yposition(), 75, 75};

		SDL_SetRenderDrawColor(renderer, entities[i].get_color()[0], entities[i].get_color()[1], entities[i].get_color()[2], 255);
		SDL_RenderFillRect(renderer, &entityRectangle);

		if (!combat)
		{
			if (CheckCollision(playerRectangle, entityRectangle) && this->COLLISION_ENABLED)
			{
				if (this->COMBAT_ENABLED)
				{
					this->HandleCombat(entities[i], i);
				}
			}
		}
	}

	for (size_t i = 0; i < this->items.size(); i++)
	{
		SDL_Rect itemRectangle = { (int)items[i].get_xposition(), (int)items[i].get_yposition(), 50, 50};

		SDL_SetRenderDrawColor(renderer, items[i].get_color()[0], items[i].get_color()[1], items[i].get_color()[2], 255);
		SDL_RenderFillRect(renderer, &itemRectangle);

		if (CheckCollision(playerRectangle, itemRectangle))
		{
			this->player->pickup(items[i]);
			this->items.erase(this->items.begin() + i);
		}
	}

	for (size_t i = 0; i < this->traps.size(); i++)
	{
		SDL_Rect trapRectangle = { (int)traps[i].get_xposition(), (int)traps[i].get_yposition(), 25, 25};

		SDL_SetRenderDrawColor(renderer, traps[i].get_color()[0], traps[i].get_color()[1], traps[i].get_color()[2], 255);
		SDL_RenderFillRect(renderer, &trapRectangle);

		if (CheckCollision(playerRectangle, trapRectangle))
		{
			std::cout << "Player stepped into a trap!" << std::endl;
			this->player->take_damage(5);

			this->traps.erase(this->traps.begin() + i);
		}
	}

	SDL_RenderPresent(renderer);
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
			if(this->player->get_yposition() - (this->player->get_speed() * this->FIXED_TIME_STEP) >= -1)
				this->player->move(0, -(this->player->get_speed() * this->FIXED_TIME_STEP));
		}
		if (this->player->move_down)
		{
			if ((this->player->get_yposition() - (this->player->get_speed() * this->FIXED_TIME_STEP)) + this->player->get_height() <= this->HEIGHT)
				this->player->move(0, (this->player->get_speed() * this->FIXED_TIME_STEP));
		}
		if (this->player->move_right)
		{
			if ((this->player->get_xposition() - (this->player->get_speed() * this->FIXED_TIME_STEP)) + this->player->get_width() <= this->WIDTH)
				this->player->move((this->player->get_speed() * this->FIXED_TIME_STEP), 0);
		}
		if (this->player->move_left)
		{
			if (this->player->get_xposition() - (this->player->get_speed() * this->FIXED_TIME_STEP) >= -1)
				this->player->move(-(this->player->get_speed() * this->FIXED_TIME_STEP), 0);
		}

		for (Entity& entity : this->entities)
		{
			if (entity.get_yposition() > this->player->get_yposition())
			{
				entity.move_up = true;
			}
			else if (entity.get_yposition() < this->player->get_yposition())
			{
				entity.move_down = true;
			}
			if (entity.get_xposition() < this->player->get_xposition())
			{
				entity.move_right = true;
			}
			else if (entity.get_xposition() > this->player->get_xposition())
			{
				entity.move_left = true;
			}

			if (entity.move_up)
			{
				entity.move(0, -(entity.get_speed() * this->FIXED_TIME_STEP));
			}
			if (entity.move_down)
			{
				entity.move(0, entity.get_speed() * this->FIXED_TIME_STEP);
			}
			if (entity.move_right)
			{
				entity.move(entity.get_speed() * this->FIXED_TIME_STEP, 0);
			}
			if (entity.move_left)
			{
				entity.move(-(entity.get_speed() * this->FIXED_TIME_STEP), 0);
			}

			entity.move_up = false;
			entity.move_down = false;
			entity.move_right = false;
			entity.move_left = false;
		}
	}
}

void Game::HandleCombat(Entity& entity, size_t entityIndex)
{
	this->combat = true;
	bool is_alive = true;
	char choice = '\0';

	this->player->move_up = false;
	this->player->move_left = false;
	this->player->move_right = false;
	this->player->move_left = false;

	for (Entity& entity : this->entities)
	{
		entity.move_up = false;
		entity.move_down = false;
		entity.move_right = false;
		entity.move_left = false;
	}

	std::cout << "---------- COMBAT ----------\n";

	do
	{
		std::cout << "-- CUR STATUS:\n- Player Health: " << this->player->get_health() << "\n- " << entity.get_name() << " Health: " << entity.get_health() << std::endl;
		std::cout << "Would you like to [F]ight or [N]ot?: ";
		std::cin >> choice;

		choice = toupper(choice);

		if (choice == 'F')
		{
			entity.take_damage(this->player->get_damage());

			std::cout << "Player deals " << this->player->get_damage() << " damage to " << entity.get_name() << "!" << std::endl;
		}
		else if (choice == 'N')
		{
			std::cout << "Player chose not to fight " << entity.get_name() << std::endl;
		}

		this->player->take_damage(entity.get_damage());

		std::cout << entity.get_name() << " deals " << entity.get_damage() << " damage to player!" << std::endl;

		if (entity.get_health() <= 0)
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
		std::cout << "Player has fallen to " << entity.get_name() << " :(" << std::endl;
		this->is_running = false;
		this->combat = false;
	}
	else
	{
		this->combat = false;
		this->entities.erase(this->entities.begin() + entityIndex);
	}
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
		this->WIDTH,
		this->HEIGHT,
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
		while (SDL_PollEvent(&event))
		{
			this->HandleInput(event);
		}

		if (this->combat == false)
		{
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
	SDL_Quit();

	return true;
}
