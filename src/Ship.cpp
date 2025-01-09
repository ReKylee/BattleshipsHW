#include "Ship.h"

#include <Grid.h>
#include <cstring>
#include <iostream>

bool			   BattleshipsHW::Ship::isSunk() const { return hitsTaken >= size; }
bool			   BattleshipsHW::Ship::isHorizontal() const { return horizontal; }
int				   BattleshipsHW::Ship::getSize() const { return size; }
std::array<int, 2> BattleshipsHW::Ship::getPosition() const { return pos; }
int				   BattleshipsHW::Ship::getPivot() const { return pivot; }
int				   BattleshipsHW::Ship::getHitsTaken() const { return hitsTaken; }
std::string		   BattleshipsHW::Ship::getName() const { return name; }

void BattleshipsHW::Ship::setPlaced(const bool place) { placed = place; }
void BattleshipsHW::Ship::setPos(const int row, const int col) {
	pos[0] = row;
	pos[1] = col;
}
bool BattleshipsHW::Ship::isPlaced() const { return placed; }


void BattleshipsHW::Ship::setHorizontal(const bool h) { horizontal = h; }
void BattleshipsHW::Ship::rotate() { horizontal = !horizontal; }


BattleshipsHW::Ship::Ship(const char *shipName, const int shipSize, const int shipPivot) :
	name(shipName), size(shipSize), pivot(shipPivot), pos{0, 0}, hitsTaken(0), horizontal(false), placed(false) {}

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

std::array<int, 4> BattleshipsHW::Ship::getAABB() const {
	int startRow, endRow, startCol, endCol;

	if (horizontal) {
		startRow = pos[0];
		endRow	 = pos[0];
		startCol = pos[1] - pivot;
		endCol	 = pos[1] + size - pivot - 1;
	} else {
		startRow = pos[0] - pivot;
		endRow	 = pos[0] + size - pivot - 1;
		startCol = pos[1];
		endCol	 = pos[1];
	}


	return {startRow, endRow, startCol, endCol};
}
