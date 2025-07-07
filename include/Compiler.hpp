#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Trap.hpp"
#pragma once

class Compiler
{
private:
    int SizeX;
    int YSize;
    bool IS_PLAYER_X_SET;
    bool IS_PLAYER_Y_SET;
    bool IS_PLAYER_R_SET;
    bool IS_PLAYER_G_SET;
    bool IS_PLAYER_B_SET;
    int NUM_OF_ENTITIES;
    int NUM_OF_ITEMS;
    int NUM_OF_TRAPS;
    int CURRENT_ENTITY;
    int CURRENT_ITEM;
    int CURRENT_TRAP;
    std::vector<std::string> RESERVED_KEYWORDS = {};
    std::vector<std::string> FILE_CONTENT;
    std::vector<std::string> WINDOW_INFO = {};
    std::string FILE_PATH;
    size_t MIN_SIZE = 1;
    std::vector<std::string> CURRENT_PLAYER;
    std::vector<std::vector<std::string>> CURRENT_ENTITIES;
    std::vector<std::vector<std::string>> CURRENT_ITEMS;
    std::vector<std::vector<std::string>> CURRENT_TRAPS;
    std::vector<std::string> get_info(std::string line, char split);
public:
    Compiler(std::string filepath);
    bool Compile();
    char* get_filepath();
    std::vector<std::string> get_player();
    std::vector<std::string> get_window_info();
    std::vector<std::vector<std::string>> get_entities();
    std::vector<std::vector<std::string>> get_items();
    std::vector<std::vector<std::string>> get_traps();
};
