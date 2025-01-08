#include "Grid.h"
#include "Ship.h"
#include "ftxui/component/component.hpp"

BattleshipsHW::Grid::Grid() {
	for (auto &cell: cells) {
		for (char &j: cell) {
			j = EMPTY;
		}
	}
}

BattleshipsHW::Grid::~Grid() {}

bool BattleshipsHW::Grid::isTileOccupied(const int row, const int col) const {
	return cells[row][col] == OCCUPIED && cells[row][col] == HIT;
}

bool BattleshipsHW::Grid::inBounds(const int row, const int col, const Ship &ship) const {
	const std::array<int, 4> extends = ship.getAABBat(row, col);

	if (extends[0] < 0 || extends[2] < 0 || extends[1] >= Grid::GRID_SIZE || extends[3] >= Grid::GRID_SIZE) {
		return false; // Ship would clip the grid boundaries
	}

	for (int r = extends[0] - 1; r <= extends[1] + 1; ++r) {	 // Extend by 1 row on both sides
		for (int c = extends[2] - 1; c <= extends[3] + 1; ++c) { // Extend by 1 column on both sides
			if (cells[r][c] != EMPTY) {
				return false;
			}
		}
	}

	// If all checks pass, placement is valid
	return true;
}


void BattleshipsHW::Grid::placeShip(const int row, const int col, const Ship &ship) {


	const std::array<int, 4> extends = ship.getAABBat(row, col);

	for (int r = extends[0]; r <= extends[1]; ++r) {
		for (int c = extends[2]; c <= extends[3]; ++c) {
			cells[r][c] = OCCUPIED;
		}
	}
}

char BattleshipsHW::Grid::getCell(const int row, const int col) const { return cells[row][col]; }

void BattleshipsHW::Grid::markHit(int row, int col) { cells[row][col] = HIT; }

void BattleshipsHW::Grid::markMiss(int row, int col) { cells[row][col] = MISS; }
