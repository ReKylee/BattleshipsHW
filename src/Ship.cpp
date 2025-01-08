#include "Ship.h"

#include <Grid.h>
#include <cstring>
#include <iostream>

bool		BattleshipsHW::Ship::isSunk() const { return hitsTaken >= size; }
bool		BattleshipsHW::Ship::isHorizontal() const { return horizontal; }
int			BattleshipsHW::Ship::getSize() const { return size; }
int			BattleshipsHW::Ship::getPivot() const { return pivot; }
int			BattleshipsHW::Ship::getHitsTaken() const { return hitsTaken; }
std::string BattleshipsHW::Ship::getName() const { return name; }

void BattleshipsHW::Ship::setHorizontal(const bool h) { horizontal = h; }


BattleshipsHW::Ship::Ship(const char *shipName, const int shipSize, const int shipPivot) :
	name(shipName), size(shipSize), pivot(shipPivot), hitsTaken(0), horizontal(false) {}

BattleshipsHW::Ship::~Ship() {}

void BattleshipsHW::Ship::takeHit() {
	if (hitsTaken < size) {
		hitsTaken++;
		std::cout << name << " got hit!" << std::endl;
	}
}

std::array<int, 4> BattleshipsHW::Ship::getAABBat(const int row, const int col, const int expand) const {
	int startRow, endRow, startCol, endCol;

	if (horizontal) {
		startRow = row;
		endRow	 = row;
		startCol = col - pivot;
		endCol	 = col + size - pivot - 1;
	} else {
		startRow = row - pivot;
		endRow	 = row + size - pivot - 1;
		startCol = col;
		endCol	 = col;
	}

	// Extend the AABB in all directions
	startRow -= expand;
	endRow += expand;
	startCol -= expand;
	endCol += expand;

	return {startRow, endRow, startCol, endCol};
}
