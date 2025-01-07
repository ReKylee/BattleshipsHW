#include "Grid.h"

#include <ftxui/dom/table.hpp>

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

bool BattleshipsHW::Grid::inBounds(const int row, const int col, const int shipSize, const int pivot,
								   const bool horizontal) const {
	int startRow = 0;
	int endRow	 = 0;
	int startCol = 0;
	int endCol	 = 0;

	if (horizontal) {
		startRow = std::max(0, row - 1);							// Buffer: 1 row below (if within bounds)
		endRow	 = std::min(GRID_SIZE - 1, row + 1);				// Buffer: 1 row above (if within bounds)
		startCol = std::max(0, col - pivot - 1);					// Buffer: 1 column to the left (if within bounds)
		endCol	 = std::min(GRID_SIZE - 1, col + shipSize - pivot); // Buffer: 1 column to the right (if within bounds)
	} else {
		startRow = std::max(0, row - pivot - 1);					// Buffer: 1 row below (if within bounds)
		endRow	 = std::min(GRID_SIZE - 1, row + shipSize - pivot); // Buffer: 1 row above (if within bounds)
		startCol = std::max(0, col - 1);							// Buffer: 1 column to the left (if within bounds)
		endCol	 = std::min(GRID_SIZE - 1, col + 1);				// Buffer: 1 column to the right (if within bounds)
	}

	// Check for collisions in the buffer zone
	for (int r = startRow; r <= endRow; ++r) {
		for (int c = startCol; c <= endCol; ++c) {
			if (cells[r][c] != EMPTY) {
				return false; // Collision detected
			}
		}
	}

	// If all checks pass, placement is valid
	return true;
}

void BattleshipsHW::Grid::placeShip(const int row, const int col, const int shipSize, const int pivot,
									const bool horizontal) {
	int startRow = 0;
	int endRow	 = 0;
	int startCol = 0;
	int endCol	 = 0;

	if (horizontal) {
		startRow = std::max(0, row);
		endRow	 = std::min(GRID_SIZE - 1, row);
		startCol = std::max(0, col - pivot);
		endCol	 = std::min(GRID_SIZE - 1, col + shipSize - pivot);
	} else {
		startRow = std::max(0, row - pivot);
		endRow	 = std::min(GRID_SIZE - 1, row + shipSize - pivot);
		startCol = std::max(0, col);
		endCol	 = std::min(GRID_SIZE - 1, col);
	}

	for (int r = startRow; r <= endRow; ++r) {
		for (int c = startCol; c <= endCol; ++c) {
			cells[r][c] = OCCUPIED;
		}
	}
}

char BattleshipsHW::Grid::getCell(const int row, const int col) const { return cells[row][col]; }

void BattleshipsHW::Grid::markHit(int row, int col) { cells[row][col] = HIT; }

void BattleshipsHW::Grid::markMiss(int row, int col) { cells[row][col] = MISS; }
