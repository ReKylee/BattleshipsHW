#include "Player.h"

#include <cstring>


void BattleshipsHW::Player::makeMove(Player *opponent, const int row, const int col) {
	switch (opponent->getCell(row, col)) {
		case Grid::MISS:
		case Grid::HIT:
			return;
		case Grid::OCCUPIED:
			opponent->markHit(row, col);
			break;
		case Grid::EMPTY:
			opponent->markMiss(row, col);
			break;
		default:
			break;
	}
}
void BattleshipsHW::Player::markHit(const int row, const int col) { grid.markHit(row, col); }

void BattleshipsHW::Player::markMiss(const int row, const int col) { grid.markMiss(row, col); }
char BattleshipsHW::Player::getCell(const int row, const int col) const { return grid.getCell(row, col); }
bool BattleshipsHW::Player::shipsHidden() const { return hideShips; }

bool BattleshipsHW::Player::allShipsSunk() const {
	for (auto &ship: ships) {
		if (!ship->isSunk()) {
			return false;
		}
	}
	return true;
}

BattleshipsHW::Player::Player(const char *str, const bool shouldHideShips) :
	playerName(new char[strlen(str) + 1]), hideShips(shouldHideShips) {
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
