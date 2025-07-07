#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#pragma once

class Designer
{
private:
	std::vector<std::string> data = {};
	std::vector<int> window_info = {};
	std::vector<int> player_info = {};
	std::map<std::string, std::vector<int>> entities_info = {};
	std::map<std::string, std::vector<int>> items_info = {};
	std::vector<std::vector<int>> traps_info = {};
public:
	void Design();
};
