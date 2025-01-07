#include "Player.h"

#include <cstring>
#include <ftxui/dom/table.hpp>

#include "ftxui/component/component.hpp"

bool BattleshipsHW::Player::allShipsSunk() const {
	for (auto &ship: ships) {
		if (!ship->isSunk()) {
			return false;
		}
	}
	return true;
}


BattleshipsHW::Player::Player(const char *str) : playerName(new char[strlen(str) + 1]) {
	strcpy(playerName, str);
	ships[0] = new Carrier();
	ships[1] = new Battleship();
	ships[2] = new Cruiser();
	ships[3] = new Submarine();
	ships[4] = new Destroyer();
}
BattleshipsHW::Player::~Player() {
	delete[] playerName;
	for (const auto &ship: ships) {
		delete ship;
	}
}
