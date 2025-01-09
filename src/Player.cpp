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
BattleshipsHW::Ship &BattleshipsHW::Player::getShip(const int index) const { return *ships[index]; }
bool				 BattleshipsHW::Player::shipsHidden() const { return hideShips; }
bool				 BattleshipsHW::Player::isPlacingShips() const {
	for (const Ship *ship: ships) {
		if (!ship->isPlaced()) {
			return true;
		}
	}
	return false;
}
void BattleshipsHW::Player::selectShip(const int index) { currentlySelectedShipIndex = index; }

void BattleshipsHW::Player::placeSelectedShip(const int row, const int col) {

	if (Ship &ship = *ships[currentlySelectedShipIndex]; !ship.isPlaced() && grid.inBounds(row, col, ship)) {
		grid.placeShip(row, col, ship);
		ship.setPlaced(true);
	}
}
void BattleshipsHW::Player::rotateSelectedShip() const {
	Ship &ship = *ships[currentlySelectedShipIndex];
	ship.rotate();
}
BattleshipsHW::Ship &BattleshipsHW::Player::getCurrentlySelectedShip() const {
	return *ships[currentlySelectedShipIndex];
}

bool BattleshipsHW::Player::allShipsSunk() const {
	for (auto &ship: ships) {
		if (!ship->isSunk()) {
			return false;
		}
	}
	return true;
}

BattleshipsHW::Player::Player(const char *str, const bool shouldHideShips) :
	playerName(str), hideShips(shouldHideShips), currentlySelectedShipIndex(0) {
	ships[0] = new Carrier();
	ships[1] = new Battleship();
	ships[2] = new Cruiser();
	ships[3] = new Submarine();
	ships[4] = new Destroyer();
}
BattleshipsHW::Player::~Player() {
	for (const auto &ship: ships) {
		delete ship;
	}
}
