#define SDL_MAIN_HANDLED
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include "Designer.hpp"
#include "Compiler.hpp"
#include "Game.hpp"
#include "EntityComponentSystem.h"

int main()
{
	char option = '\0';

	std::cout << "******************************* VX ENGINE *******************************\n";

	do
	{
		do
		{
			std::cout << "What would you like to do ([D]esign or [P]lay or [Q]uit): ";
			std::cin >> option;

			option = toupper(option);

			if (option != 'D' && option != 'P' && option != 'Q')
			{
				std::cout << " - Invalid option!\n";
				option = '\0';
			}
		} while (option == '\0');

		if (option == 'D')
		{
			Designer designer;
			designer.Design();
		}
		else if (option == 'P')
		{
			std::cout << "-------------------------------------------------------------------------\n";
			
			std::string filepath = "";
			
			do
			{
				std::cout << "Enter file name (e.g. game.vxed): ";
				std::getline(std::cin >> std::ws, filepath);
			} while (filepath.empty());

			do
			{
				Compiler compiler(filepath);
				bool result = compiler.Compile();

				if (result)
				{
					float PlayerStartingSpeed;
					int PlayerStartingDamage;

					try
					{
						std::cout << "-------------------------------------------------------------------------\n";

						do
						{
							std::cout << "- Enter player Speed (100 -> 450): ";
							std::cin >> PlayerStartingSpeed;

							if (PlayerStartingSpeed < 100.0f || PlayerStartingSpeed > 450.0f)
							{
								std::cout << " - Invalid Value of Player Starting Speed!" << std::endl;
							}
						} while (PlayerStartingSpeed < 100.0f || PlayerStartingSpeed > 450.0f);

						do
						{
							std::cout << "- Enter player Damage (0 -> 35): ";
							std::cin >> PlayerStartingDamage;

							if (PlayerStartingDamage < 0 || PlayerStartingDamage > 35)
							{
								std::cout << " - Invalid Value of Player Damage!" << std::endl;
							}
						} while (PlayerStartingDamage < 0 || PlayerStartingDamage > 35);

						std::vector<std::string> returned_window_data = compiler.get_window_info();
						std::vector<int> integer_colors = { std::stoi(returned_window_data[2]), std::stoi(returned_window_data[3]), std::stoi(returned_window_data[4]) };
						int width = std::stoi(returned_window_data[0]);
						int height = std::stoi(returned_window_data[1]);
						Color backgroundColors = {};
						backgroundColors.Red = (Uint32)integer_colors[0];
						backgroundColors.Green = (Uint32)integer_colors[1];
						backgroundColors.Blue = (Uint32)integer_colors[2];

						std::vector<std::string> returned_player_data = compiler.get_player();
						std::vector<int> integer_player_colors = { std::stoi(returned_player_data[3]), std::stoi(returned_player_data[4]), std::stoi(returned_player_data[5]) };
						std::string name = returned_player_data[0];
						int PlayerXPos = std::stoi(returned_player_data[1]);
						int PlayerYPos = std::stoi(returned_player_data[2]);
						Color playerColors = {};
						playerColors.Red = (Uint32)integer_player_colors[0];
						playerColors.Green = (Uint32)integer_player_colors[1];
						playerColors.Blue = (Uint32)integer_player_colors[2];

						Player player(name, PlayerXPos, PlayerYPos, 100, playerColors, PlayerStartingDamage, PlayerStartingSpeed);

						std::vector<std::vector<std::string>> returned_entities_data = compiler.get_entities();
						std::vector<Entity> entities = { };

						for (size_t i = 0; i < returned_entities_data.size(); i++)
						{
							std::vector<std::string> returned_entity_data = returned_entities_data[i];
							std::vector<int> integer_entity_colors = { std::stoi(returned_entity_data[5]), std::stoi(returned_entity_data[6]), std::stoi(returned_entity_data[7]) };
							std::string name = returned_entity_data[0];
							int EntityXPos = std::stoi(returned_entity_data[1]);
							int EntityYPos = std::stoi(returned_entity_data[2]);
							Hostility entityHostility = {};
							float EntitySpeed;

							entityHostility.mode = std::stoi(returned_entity_data[3]);
							entityHostility.amount = std::stoi(returned_entity_data[4]);
							Color entityColors = {};
							entityColors.Red = (Uint32)integer_entity_colors[0];
							entityColors.Green = (Uint32)integer_entity_colors[1];
							entityColors.Blue = (Uint32)integer_entity_colors[2];

							do
							{
								std::cout << "- Enter Entity (" << name << ") Speed (100 -> 350): ";
								std::cin >> EntitySpeed;

								if (EntitySpeed < 100.0f || EntitySpeed > 350.0f)
								{
									std::cout << " - Invalid Value of " << name << " Speed!" << std::endl;
								}
							} while (EntitySpeed < 100.0f || EntitySpeed > 350.0f);

							Entity entity(name, EntityXPos, EntityYPos, 100, entityColors, entityHostility, EntitySpeed);
							entities.push_back(entity);
						}

						std::vector<std::vector<std::string>> returned_items_data = compiler.get_items();
						std::vector<Item> items = { };

						for (size_t i = 0; i < returned_items_data.size(); i++)
						{
							std::vector<std::string> returned_item_data = returned_items_data[i];
							std::vector<int> integer_item_colors = { std::stoi(returned_item_data[4]), std::stoi(returned_item_data[5]), std::stoi(returned_item_data[6]) };
							std::string name = returned_item_data[0];
							int ItemXPos = std::stoi(returned_item_data[1]);
							int ItemYPos = std::stoi(returned_item_data[2]);
							int ItemBuff = std::stoi(returned_item_data[3]);
							Color itemColors = {};
							itemColors.Red = (Uint32)integer_item_colors[0];
							itemColors.Green = (Uint32)integer_item_colors[1];
							itemColors.Blue = (Uint32)integer_item_colors[2];

							Item item(name, ItemXPos, ItemYPos, ItemBuff, itemColors);
							items.push_back(item);
						}

						std::vector<std::vector<std::string>> returned_traps_data = compiler.get_traps();
						std::vector<Trap> traps = { };

						for (size_t i = 0; i < returned_traps_data.size(); i++)
						{
							std::vector<std::string> returned_trap_data = returned_traps_data[i];
							std::vector<int> integer_trap_colors = { std::stoi(returned_trap_data[3]), std::stoi(returned_trap_data[4]), std::stoi(returned_trap_data[5]) };
							std::string name = returned_trap_data[0];
							int TrapXPos = std::stoi(returned_trap_data[1]);
							int TrapYPos = std::stoi(returned_trap_data[2]);
							Color trapColors = {};
							trapColors.Red = (Uint32)integer_player_colors[0];
							trapColors.Green = (Uint32)integer_player_colors[1];
							trapColors.Blue = (Uint32)integer_player_colors[2];

							Trap trap(name, TrapXPos, TrapYPos, trapColors);
							traps.push_back(trap);
						}

						char combat_choice = '\0';
						bool combat = false;

						do
						{
							std::cout << "Would you like Combat enabled (Y/N)?: ";
							std::cin >> combat_choice;

							combat_choice = toupper(combat_choice);

							if (combat_choice == 'Y')
							{
								combat = true;
							}
							else if (combat_choice == 'N')
							{
								combat = false;
							}
							else
							{
								combat_choice = '\0';
							}
						} while (combat_choice == '\0');

						char collision_choice = '\0';
						bool collision = false;

						do
						{
							std::cout << "Would you like Collisions enabled (Y/N)?: ";
							std::cin >> collision_choice;

							collision_choice = toupper(collision_choice);

							if (collision_choice == 'Y')
							{
								collision = true;
							}
							else if (collision_choice == 'N')
							{
								collision = false;
							}
							else
							{
								collision_choice = '\0';
							}
						} while (collision_choice == '\0');

						Game curGame(filepath, player, entities, items, traps, backgroundColors, width, height, combat, collision);

						std::cout << "-------------------------------------------------------------------------\n";
						std::cout << "If you would like to exit, just click the \"X\" button or press \"ESC\" key!" << std::endl;
						std::cout << "-------------------------------------------------------------------------\n";

						SDL_Delay(2000);

						curGame.run();

						filepath = compiler.get_next_map();

						option = '\0';
						if (!filepath.empty())
						{
							do
							{
								std::cout << "Would you like to continue (Y/N): ";
								std::cin >> option;

								option = toupper(option);

								if (option == 'Y')
								{
									option = 'P';
								}
								else if (option == 'N')
								{
									option = 'Q';
								}
								else
								{
									std::cout << " - Invalid option!" << std::endl;
									option = '\0';
								}
							} while (option == '\0');
						}
					}
					catch (const std::exception& e)
					{
						std::cout << "Error while compiling file..." << e.what() << std::endl;
						break;
					}
				}
				else
				{
					std::cout << "Couldn't compile file..." << std::endl;
					break;
				}
			} while (!filepath.empty() && option != 'Q');
		}
		else if (option == 'Q')
		{
			char confirmation = '\0';

			do
			{
				std::cout << "Are you sure you want to exit (Y/N)?: ";
				std::cin >> confirmation;

				confirmation = toupper(confirmation);

				if (confirmation == 'Y')
				{
					option = 'Q';
				}
				else if (confirmation == 'N')
				{
					option = '\0';
				}
				else
				{
					std::cout << " - Enter a valid confirmation!" << std::endl;
					confirmation = '\0';
				}
			} while (confirmation == '\0');
		}

	} while (option != 'Q');

	std::cout << "Quitting..." << std::endl;

	return 0;
}
