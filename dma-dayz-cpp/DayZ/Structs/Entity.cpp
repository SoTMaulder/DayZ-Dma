#pragma once
#include "Entity.h"
#include <fstream>
#include <iostream>

std::set<std::string> DayZ::Entity::rareItems;

void DayZ::Entity::loadRareItems(const std::string& filePath) {
	rareItems.clear();
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Warning: File RareItems.txt" << filePath << " could not be opened. Rare items are not loading.\n";
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			rareItems.insert(line);
		}
	}
	file.close();

	if (rareItems.empty()) {
		std::cerr << "Warning: File RareItems.txt" << filePath << " contains no valid entries.\n";
	}
}

