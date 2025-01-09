#pragma once

#include <Ship.h>

namespace BattleshipsHW {
class Grid {
public:
	/**
	 * @brief Cell states
	 */
	static constexpr char EMPTY	   = '~';
	static constexpr char OCCUPIED = 'O';
	static constexpr char HIT	   = 'X';
	static constexpr char MISS	   = ' ';

	/**
	 * @brief Grid size
	 */
	static constexpr int GRID_SIZE = 10;

	Grid();

	~Grid();

	/**
	 * @brief Check if a cell is occupied or hit
	 * @param row The row of the cell
	 * @param col The column of the cell
	 * @return True if the cell is occupied or hit, false otherwise
	 */
	bool isTileOccupied(int row, int col) const;

	/**
	 * @brief Check if a ship can be placed at a given position
	 * @param row The row of the cell
	 * @param col The column of the cell
	 * @param ship The ship to be placed
	 * @return True if the ship can be placed at the given position, false otherwise
	 */
	bool inBounds(int row, int col, const Ship &ship) const;

	/**
	 * @brief Place a ship on the grid
	 * @param row The row of the cell
	 * @param col The column of the cell
	 * @param ship The ship to be placed
	 */
	void placeShip(int row, int col, const Ship &ship);

	/**
	 * @brief Mark a cell as hit
	 * @param row The row of the cell
	 * @param col The column of the cell
	 */
	void markHit(int row, int col);

	/**
	 * @brief Mark a cell as missed
	 * @param row The row of the cell
	 * @param col The column of the cell
	 */
	void markMiss(int row, int col);

	/**
	 * @brief Get the cell at a given position
	 * @param row The row of the cell
	 * @param col The column of the cell
	 * @return The cell at the given position
	 */
	char getCell(int row, int col) const;


private:
	char cells[GRID_SIZE][GRID_SIZE]{};
};
} // namespace BattleshipsHW
