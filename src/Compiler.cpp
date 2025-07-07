#include <iostream>
#include "Compiler.hpp"

Compiler::Compiler(std::string filepath)
{
	std::ifstream output;
	output.open(filepath);

	if (output.is_open())
	{
		this->FILE_PATH = filepath;

		output.close();

		this->RESERVED_KEYWORDS.push_back("$/EOWDTPI/$");
		this->RESERVED_KEYWORDS.push_back("$/EOPITEC/$");
		this->RESERVED_KEYWORDS.push_back("$/EOPITEI/$");
		this->RESERVED_KEYWORDS.push_back("$/EOEITIC/$");
		this->RESERVED_KEYWORDS.push_back("$/EOEITII/$");
		this->RESERVED_KEYWORDS.push_back("$/EOIITTC/$");
		this->RESERVED_KEYWORDS.push_back("$/EOIITTI/$");
		this->RESERVED_KEYWORDS.push_back("$/EOWDAI/$");
	}
	else
	{
		std::cout << "Couldn't open file path to compile..." << std::endl;
	}
}

std::vector<std::string> Compiler::get_info(std::string line, char split)
{
	std::vector<std::string> output = {};

	std::string string;

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != split)
		{
			string += line[i];
		}
		else
		{
			output.push_back(string);
			string = "";
		}
	}

	output.push_back(string);

	return output;
}

bool Compiler::Compile()
{
	if (!this->FILE_PATH.empty())
	{
		std::ifstream fileContent;
		fileContent.open(this->FILE_PATH);

		std::vector<std::string> fileData = {};

		if (fileContent.is_open())
		{
			std::string curLine = "";

			while (std::getline(fileContent, curLine))
			{
				fileData.push_back(curLine);
			}

			fileContent.close();
		}

		try
		{
			if (fileData.size() >= this->MIN_SIZE)
			{
				int mode = 0;

				for (size_t i = 0; i < fileData.size(); i++)
				{
					for (std::string reserved_keyword : this->RESERVED_KEYWORDS)
					{
						if (reserved_keyword == fileData[i])
						{
							if (reserved_keyword == "$/EOWDTPI/$")
							{
								mode = 1;
								break;
							}
							else if (reserved_keyword == "$/EOPITEC/$")
							{
								mode = 2;
								break;
							}
							else if (reserved_keyword == "$/EOPITEI/$")
							{
								mode = 3;
								break;
							}
							else if (reserved_keyword == "$/EOEITIC/$")
							{
								mode = 4;
								break;
							}
							else if (reserved_keyword == "$/EOEITII/$")
							{
								mode = 5;
								break;
							}
							else if (reserved_keyword == "$/EOIITTC/$")
							{
								mode = 6;
								break;
							}
							else if (reserved_keyword == "$/EOIITTI/$")
							{
								mode = 7;
								break;
							}
							else if (reserved_keyword == "$/EOWDAI/$")
							{
								mode = 8;
								break;
							}
						}
					}

					bool is_reserved = false;

					for (std::string reserved_keyword : this->RESERVED_KEYWORDS)
					{
						if (fileData[i] == reserved_keyword)
						{
							is_reserved = true;
						}
					}

					if (is_reserved == false)
					{
						if (mode == 0)
						{
							try
							{
								std::vector<std::string> window_data = this->get_info(fileData[i], ',');

								for (std::string data : window_data)
								{
									this->WINDOW_INFO.push_back(data);
								}
							}
							catch (std::exception& e)
							{
								std::cout << e.what() << std::endl;
							}
						}
						else if (mode == 1)
						{
							try
							{
								std::vector<std::string> player_data = this->get_info(fileData[i], ',');

								for (std::string data : player_data)
								{
									this->CURRENT_PLAYER.push_back(data);
								}
							}
							catch (std::exception& e)
							{
								std::cout << e.what() << std::endl;
							}
						}
						else if (mode == 2)
						{
							try
							{
								this->NUM_OF_ENTITIES = std::stoi(fileData[i]);
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
							}
						}
						else if (mode == 3)
						{
							if (NUM_OF_ENTITIES > 0)
							{
								if (this->CURRENT_ENTITY < this->NUM_OF_ENTITIES)
								{
									try
									{
										std::vector<std::string> entity_data = this->get_info(fileData[i], ',');

										this->CURRENT_ENTITIES.push_back(entity_data);
										this->CURRENT_ENTITY++;
									}
									catch (const std::exception& e)
									{
										std::cout << e.what() << std::endl;
									}
								}
							}
						}
						else if (mode == 4)
						{
							try
							{
								this->NUM_OF_ITEMS = std::stoi(fileData[i]);
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
							}
						}
						else if (mode == 5)
						{
							if (this->NUM_OF_ITEMS > 0)
							{
								if (this->CURRENT_ITEM < this->NUM_OF_ITEMS)
								{
									try
									{
										std::vector<std::string> item_data = this->get_info(fileData[i], ',');

										this->CURRENT_ITEMS.push_back(item_data);
										this->CURRENT_ITEM++;
									}
									catch (const std::exception& e)
									{
										std::cout << e.what() << std::endl;
									}
								}
							}
						}
						else if (mode == 6)
						{
							try
							{
								this->NUM_OF_TRAPS = std::stoi(fileData[i]);
							}
							catch (const std::exception& e)
							{
								std::cout << e.what() << std::endl;
							}
						}
						else if (mode == 7)
						{
							if (this->NUM_OF_TRAPS > 0)
							{
								if (this->CURRENT_TRAP < this->NUM_OF_TRAPS)
								{
									try
									{
										std::vector<std::string> trap_data = this->get_info(fileData[i], ',');

										this->CURRENT_TRAPS.push_back(trap_data);
										this->CURRENT_TRAP++;
									}
									catch (const std::exception& e)
									{
										std::cout << e.what() << std::endl;
									}
								}
							}
						}
					}
					else
					{
						if (mode == 8)
						{
							break;
						}
					}
				}
			}
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	return true;
}

char* Compiler::get_filepath()
{
	std::string this_filepath = this->FILE_PATH;
	char filepath[25] = "";
	int i = 0;

	for (auto& c : this_filepath)
	{
		filepath[i] = c;
		i++;
	}

	return filepath;
}

std::vector<std::string> Compiler::get_player()
{
	return this->CURRENT_PLAYER;
}
std::vector<std::string> Compiler::get_window_info()
{
	return this->WINDOW_INFO;
}
std::vector<std::vector<std::string>> Compiler::get_entities()
{
	return this->CURRENT_ENTITIES;
}
std::vector<std::vector<std::string>> Compiler::get_items()
{
	return this->CURRENT_ITEMS;
}
std::vector<std::vector<std::string>> Compiler::get_traps()
{
	return this->CURRENT_TRAPS;
}
