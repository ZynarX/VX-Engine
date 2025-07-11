#include <iostream>
#include "Designer.hpp"

void Designer::Design()
{
	std::string filepath = "";

	do
	{
		std::cout << "New Game Name (name.vxed, e.g. game.vxed): ";
		std::getline(std::cin >> std::ws, filepath);
	} while (filepath.empty());

	std::ofstream outputFile;
	outputFile.open(filepath, std::ios::out | std::ios::trunc);

	if (outputFile.is_open())
	{
		try
		{
			int WIDTH = -1;
			int HEIGHT = -1;

			do
			{
				std::cout << "- Window Width (500 pixels or more): ";
				std::cin >> WIDTH;

				if (WIDTH < 500)
				{
					std::cout << " - Invalid Value of Window Width!" << std::endl;
				}
			} while (WIDTH < 500);

			do
			{
				std::cout << "- Window Height (500 pixels or more): ";
				std::cin >> HEIGHT;

				if (HEIGHT < 500)
				{
					std::cout << " - Invalid Value of Window Height!" << std::endl;
				}
			} while (HEIGHT < 500);

			if (WIDTH >= 500 && HEIGHT >= 500)
			{
				this->window_info.push_back(WIDTH);
				this->window_info.push_back(HEIGHT);

				int BackgroundRed = -1;
				int BackgroundGreen = -1;
				int BackgroundBlue = -1;

				do
				{
					std::cout << "- Background color Red variant (0 -> 255): ";
					std::cin >> BackgroundRed;

					if (BackgroundRed < 0 || BackgroundRed > 255)
					{
						std::cout << " - Invalid Value of Red variant of Background!" << std::endl;
					}
				} while (BackgroundRed < 0 || BackgroundRed > 255);

				do
				{
					std::cout << "- Background color Green variant (0 -> 255): ";
					std::cin >> BackgroundGreen;

					if (BackgroundGreen < 0 || BackgroundGreen > 255)
					{
						std::cout << " - Invalid Value of Green variant of Background!" << std::endl;
					}
				} while (BackgroundGreen < 0 || BackgroundGreen > 255);

				do
				{
					std::cout << "- Background color Blue variant (0 -> 255): ";
					std::cin >> BackgroundBlue;

					if (BackgroundBlue < 0 || BackgroundBlue > 255)
					{
						std::cout << " - Invalid Value of Blue variant of Background!" << std::endl;
					}
				} while (BackgroundBlue < 0 || BackgroundBlue > 255);

				this->window_info.push_back(BackgroundRed);
				this->window_info.push_back(BackgroundGreen);
				this->window_info.push_back(BackgroundBlue);

				int PlayerX = -1;
				int PlayerY = -1;
				int PlayerRed = -1;
				int PlayerGreen = -1;
				int PlayerBlue = -1;

				do
				{
					std::cout << "- Player starting X position (Player Width: 100): ";
					std::cin >> PlayerX;

					if (PlayerX < 0 || PlayerX + 100 > WIDTH)
					{
						std::cout << " - Invalid Value of Player Starting X Position!" << std::endl;
					}
				} while (PlayerX < 0 || PlayerX + 100 > WIDTH);

				do
				{
					std::cout << "- Player starting Y position (Player Height: 100): ";
					std::cin >> PlayerY;

					if (PlayerY < 0 || PlayerY + 100 > HEIGHT)
					{
						std::cout << " - Invalid Value of Player Starting Y Position!" << std::endl;
					}
				} while (PlayerY < 0 || PlayerY + 100 > HEIGHT);

				do
				{
					std::cout << "- Player color Red Variant (0 -> 255): ";
					std::cin >> PlayerRed;

					if (PlayerRed < 0 || PlayerRed > 255)
					{
						std::cout << " - Invalid Value of Player red Variant!" << std::endl;
					}
				} while (PlayerRed < 0 || PlayerRed > 255);

				do
				{
					std::cout << "- Player color Green Variant (0 -> 255): ";
					std::cin >> PlayerGreen;

					if (PlayerGreen < 0 || PlayerGreen > 255)
					{
						std::cout << " - Invalid Value of Player green Variant!" << std::endl;
					}
				} while (PlayerGreen < 0 || PlayerGreen > 255);

				do
				{
					std::cout << "- Player color Blue Variant (0 -> 255): ";
					std::cin >> PlayerBlue;

					if (PlayerBlue < 0 || PlayerBlue > 255)
					{
						std::cout << " - Invalid Value of Player blue Variant!" << std::endl;
					}
				} while (PlayerBlue < 0 || PlayerBlue > 255);

				this->player_info.push_back(PlayerX);
				this->player_info.push_back(PlayerY);
				this->player_info.push_back(PlayerRed);
				this->player_info.push_back(PlayerGreen);
				this->player_info.push_back(PlayerBlue);

				int NumberOfEntities = -1;

				do
				{
					std::cout << "Enter No. of Entites (0 -> 10): ";
					std::cin >> NumberOfEntities;
				} while (NumberOfEntities < 0 || NumberOfEntities > 10);

				for (int i = 0; i < NumberOfEntities; i++)
				{
					std::string iName = "";
					int iX = -1;
					int iY = -1;
					int iHostilityMode = -1;
					int iHostilityDamage = 0;
					int iRed = -1;
					int iGreen = -1;
					int iBlue = -1;

					do
					{
						std::cout << "- Entity No. " << i << " Name: ";
						std::getline(std::cin >> std::ws, iName);
					} while (iName.empty());

					do
					{
						std::cout << "- Entity No. " << i << " starting X positions (Entity Width: 75): ";
						std::cin >> iX;

						if (iX < 0 || iX + 75 > WIDTH)
						{
							std::cout << " - Invalid Value of Entity No. " << i << " starting X Position!" << std::endl;
						}
					} while (iX < 0 || iX + 75 > WIDTH);

					do
					{
						std::cout << "- Entity No. " << i << " starting Y positions (Entity Height: 75): ";
						std::cin >> iY;

						if (iY < 0 || iY + 75 > HEIGHT)
						{
							std::cout << " - Invalid Value of Entity No. " << i << " starting Y Position!" << std::endl;
						}
					} while (iY < 0 || iY + 75 > HEIGHT);

					do
					{
						std::cout << "- Entity No. " << i << " hostility mode (1. Hostile, 2. None Hostile): ";
						std::cin >> iHostilityMode;

						if (iHostilityMode != 1 && iHostilityMode != 2)
						{
							std::cout << " - Invalid Value of Entity No. " << i << " hostility mode!" << std::endl;
						}
					} while (iHostilityMode != 1 && iHostilityMode != 2);

					if (iHostilityMode == 1)
					{
						do
						{
							std::cout << "- Entity No. " << i << " damage (0 -> 50): ";
							std::cin >> iHostilityDamage;

							if (iHostilityDamage < 0 || iHostilityDamage > 50)
							{
								std::cout << " - Invalid Value of Entity No. " << i << " hostility damage!" << std::endl;
							}
						} while (iHostilityDamage < 0 || iHostilityDamage > 50);
					}

					do
					{
						std::cout << "- Entity No. " << i << " color Red Variant (0 -> 255): ";
						std::cin >> iRed;

						if (iRed < 0 || iRed > 255)
						{
							std::cout << " - Invalid Value of Entity No." << i << " red Variant!" << std::endl;
						}
					} while (iRed < 0 || iRed > 255);

					do
					{
						std::cout << "- Entity No. " << i << " color Green Variant (0 -> 255): ";
						std::cin >> iGreen;

						if (iGreen < 0 || iGreen > 255)
						{
							std::cout << " - Invalid Value of Entity No." << i << " green Variant!" << std::endl;
						}
					} while (iGreen < 0 || iGreen > 255);

					do
					{
						std::cout << "- Entity No. " << i << " color Blue Variant (0 -> 255): ";
						std::cin >> iBlue;

						if (iBlue < 0 || iBlue > 255)
						{
							std::cout << " - Invalid Value of Entity No." << i << " blue Variant!" << std::endl;
						}
					} while (iBlue < 0 || iBlue > 255);

					this->entities_info[iName] = { iX, iY, iHostilityMode, iHostilityDamage, iRed, iGreen, iBlue };
				}

				int NumberOfItems = -1;

				do
				{
					std::cout << "Enter No. of Items (0 -> 10): ";
					std::cin >> NumberOfItems;
				} while (NumberOfItems < 0 || NumberOfItems > 10);

				for (int i = 0; i < NumberOfItems; i++)
				{
					std::string iName = "";
					int iX = -1;
					int iY = -1;
					int iBuff = -1;
					int iRed = -1;
					int iGreen = -1;
					int iBlue = -1;

					do
					{
						std::cout << "- Item No. " << i << " Name: ";
						std::getline(std::cin >> std::ws, iName);
					} while (iName.empty());

					do
					{
						std::cout << "- Item No. " << i << " starting X positions (Item Width: 50): ";
						std::cin >> iX;

						if (iX < 0 || iX + 75 > WIDTH)
						{
							std::cout << " - Invalid Value of Item No. " << i << " starting X Position!" << std::endl;
						}
					} while (iX < 0 || iX + 75 > WIDTH);

					do
					{
						std::cout << "- Item No. " << i << " starting Y positions (Item Height: 50): ";
						std::cin >> iY;

						if (iY < 0 || iY + 75 > HEIGHT)
						{
							std::cout << " - Invalid Value of Item No. " << i << " starting Y Position!" << std::endl;
						}
					} while (iY < 0 || iY + 75 > HEIGHT);

					do
					{
						std::cout << "- Item No. " << i << " damage Buff (0 -> 10): ";
						std::cin >> iBuff;

						if (iBuff < 0 || iBuff > 10)
						{
							std::cout << " - Invalid Value of Item No. " << i << " damage Buff!" << std::endl;
						}
					} while (iBuff < 0 || iBuff > 10);

					do
					{
						std::cout << "- Item No. " << i << " color Red Variant (0 -> 255): ";
						std::cin >> iRed;

						if (iRed < 0 || iRed > 255)
						{
							std::cout << " - Invalid Value of Item No." << i << " red Variant!" << std::endl;
						}
					} while (iRed < 0 || iRed > 255);

					do
					{
						std::cout << "- Item No. " << i << " color Green Variant (0 -> 255): ";
						std::cin >> iGreen;

						if (iGreen < 0 || iGreen > 255)
						{
							std::cout << " - Invalid Value of Item No." << i << " green Variant!" << std::endl;
						}
					} while (iGreen < 0 || iGreen > 255);

					do
					{
						std::cout << "- Item No. " << i << " color Blue Variant (0 -> 255): ";
						std::cin >> iBlue;

						if (iBlue < 0 || iBlue > 255)
						{
							std::cout << " - Invalid Value of Item No." << i << " blue Variant!" << std::endl;
						}
					} while (iBlue < 0 || iBlue > 255);

					this->items_info[iName] = { iX, iY, iBuff, iRed, iGreen, iBlue };
				}

				int NumberOfTraps = -1;

				do
				{
					std::cout << "Enter No. of Traps (0 -> 10): ";
					std::cin >> NumberOfTraps;
				} while (NumberOfTraps < 0 || NumberOfTraps > 10);

				for (int i = 0; i < NumberOfTraps; i++)
				{
					int iX = -1;
					int iY = -1;
					int iRed = -1;
					int iGreen = -1;
					int iBlue = -1;

					do
					{
						std::cout << "- Trap No. " << i << " starting X positions (Trap Width: 25): ";
						std::cin >> iX;

						if (iX < 0 || iX + 75 > WIDTH)
						{
							std::cout << " - Invalid Value of Trap No. " << i << " starting X Position!" << std::endl;
						}
					} while (iX < 0 || iX + 75 > WIDTH);

					do
					{
						std::cout << "- Trap No. " << i << " starting Y positions (Trap Height: 25): ";
						std::cin >> iY;

						if (iY < 0 || iY + 75 > HEIGHT)
						{
							std::cout << " - Invalid Value of Trap No. " << i << " starting Y Position!" << std::endl;
						}
					} while (iY < 0 || iY + 75 > HEIGHT);

					do
					{
						std::cout << "- Trap No. " << i << " color Red Variant (0 -> 255): ";
						std::cin >> iRed;

						if (iRed < 0 || iRed > 255)
						{
							std::cout << " - Invalid Value of Trap No." << i << " red Variant!" << std::endl;
						}
					} while (iRed < 0 || iRed > 255);

					do
					{
						std::cout << "- Trap No. " << i << " color Green Variant (0 -> 255): ";
						std::cin >> iGreen;

						if (iGreen < 0 || iGreen > 255)
						{
							std::cout << " - Invalid Value of Trap No." << i << " green Variant!" << std::endl;
						}
					} while (iGreen < 0 || iGreen > 255);

					do
					{
						std::cout << "- Trap No. " << i << " color Blue Variant (0 -> 255): ";
						std::cin >> iBlue;

						if (iBlue < 0 || iBlue > 255)
						{
							std::cout << " - Invalid Value of Trap No." << i << " blue Variant!" << std::endl;
						}
					} while (iBlue < 0 || iBlue > 255);

					this->traps_info.push_back({ iX, iY, iRed, iGreen, iBlue });
				}

				char nextMapOption = '\0';
				int nextMap = -1;
				std::string nextMapPath = "";

				do
				{
					std::cout << "Next Map (Y/N): ";
					std::cin >> nextMapOption;

					nextMapOption = toupper(nextMapOption);

					if (nextMapOption == 'Y')
					{
						nextMap = 1;
					}
					else if (nextMapOption == 'N')
					{
						nextMap = 0;
					}
					else
					{
						nextMap = -1;
					}
				} while (nextMap == -1);

				if (nextMap == 1)
				{
					do
					{
						std::cout << "- Next Map File Name (e.g. game.vxed): ";
						std::getline(std::cin >> std::ws, nextMapPath);

						if (nextMapPath.empty())
						{
							std::cout << " - Invalid Value of Next Map File Name!" << std::endl;
						}
					} while (nextMapPath.empty());
				}

				this->data.push_back(std::to_string(WIDTH) + ',' + std::to_string(HEIGHT) + ',' + std::to_string(BackgroundRed) + ',' + std::to_string(BackgroundGreen) + ',' + std::to_string(BackgroundBlue));
				this->data.push_back("$/EOWDTPI/$");

				this->data.push_back("Player," + std::to_string(PlayerX) + ',' + std::to_string(PlayerY) + ',' + std::to_string(PlayerRed) + ',' + std::to_string(PlayerGreen) + ',' + std::to_string(PlayerBlue));
				this->data.push_back("$/EOPITEC/$");

				this->data.push_back(std::to_string(NumberOfEntities));

				this->data.push_back("$/EOPITEI/$");

				for (auto& pair : this->entities_info)
				{
					this->data.push_back(pair.first + ',' + std::to_string(pair.second[0]) + ',' + std::to_string(pair.second[1]) + ',' + std::to_string(pair.second[2]) + ',' + std::to_string(pair.second[3]) + ',' + std::to_string(pair.second[4]) + ',' + std::to_string(pair.second[5]) + ',' + std::to_string(pair.second[6]));
				}

				this->data.push_back("$/EOEITIC/$");

				this->data.push_back(std::to_string(NumberOfItems));

				this->data.push_back("$/EOEITII/$");

				for (auto& pair : this->items_info)
				{
					this->data.push_back(pair.first + ',' + std::to_string(pair.second[0]) + ',' + std::to_string(pair.second[1]) + ',' + std::to_string(pair.second[2]) + ',' + std::to_string(pair.second[3]) + ',' + std::to_string(pair.second[4]) + ',' + std::to_string(pair.second[5]));
				}

				this->data.push_back("$/EOIITTC/$");

				this->data.push_back(std::to_string(NumberOfTraps));

				this->data.push_back("$/EOIITTI/$");

				for (auto& trap : this->traps_info)
				{
					this->data.push_back("Trap," + std::to_string(trap[0]) + ',' + std::to_string(trap[1]) + ',' + std::to_string(trap[2]) + ',' + std::to_string(trap[3]) + ',' + std::to_string(trap[4]));
				}

				this->data.push_back("$/EOTITNMT/$");

				this->data.push_back(std::to_string(nextMap));

				if (!nextMapPath.empty())
				{
					this->data.push_back("$/EONMTTNMP/$");
					this->data.push_back(nextMapPath);
				}

				this->data.push_back("$/EOWDAI/$");

				for (std::string line : this->data)
				{
					outputFile << line << '\n';
				}
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		outputFile.close();
	}
	else
	{
		std::cout << "Couldn't open file!\n";
	}
}
