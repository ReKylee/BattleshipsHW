#include "Player.h"

#include <cstring>

using namespace BattleshipsHW;
void Player::makeMove(Player *opponent, const int row, const int col) {
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
void Player::markHit(const int row, const int col) {
	grid.markHit(row, col);

	for (const auto ship: ships) {

		if (auto bounds = ship->getAABB();
			row >= bounds[0] && row <= bounds[1] && col >= bounds[2] && col <= bounds[3]) {
			ship->takeHit();
			break;
		}
	}
}

void Player::markMiss(const int row, const int col) { grid.markMiss(row, col); }

char		Player::getCell(const int row, const int col) const { return grid.getCell(row, col); }
std::string Player::getName() const { return playerName; }
Ship	   &Player::getShip(const int index) const { return *ships[index]; }
bool		Player::shipsHidden() const { return hideShips; }
bool		Player::isPlacingShips() const {
	   for (const Ship *ship: ships) {
		   if (!ship->isPlaced()) {
			   return true;
		   }
	   }
	   return false;
}
void Player::selectShip(const int index) { currentlySelectedShipIndex = index; }

void Player::placeSelectedShip(const int row, const int col) {

	if (Ship &ship = *ships[currentlySelectedShipIndex]; !ship.isPlaced() && grid.inBounds(row, col, ship)) {
		grid.placeShip(row, col, ship);
		ship.setPlaced(true);
		ship.setPos(row, col);
	}
}
void Player::rotateSelectedShip() const {
	Ship &ship = *ships[currentlySelectedShipIndex];
	ship.rotate();
}
Ship &Player::getCurrentlySelectedShip() const { return *ships[currentlySelectedShipIndex]; }

bool Player::allShipsSunk() const {
	for (const auto ship: ships) {
		if (!ship->isSunk()) {
			return false;
		}
	}
	return true;
}

Player::Player(const char *str, const bool shouldHideShips) :
	playerName(str), currentlySelectedShipIndex(0), hideShips(shouldHideShips) {
	ships[0] = new Carrier();
	ships[1] = new Battleship();
	ships[2] = new Cruiser();
	ships[3] = new Submarine();
	ships[4] = new Destroyer();
}
Player::~Player() {
	for (const auto &ship: ships) {
		delete ship;
	}
}
