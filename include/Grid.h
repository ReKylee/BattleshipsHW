
#ifndef GRID_H
#define GRID_H
#include "ftxui/component/loop.hpp"

namespace BattleshipsHW {
class Grid {
public:
	static constexpr char EMPTY	   = '~';
	static constexpr char OCCUPIED = 'O';
	static constexpr char HIT	   = 'X';
	static constexpr char MISS	   = ' ';

	static constexpr int GRID_SIZE = 10;

	Grid();

	~Grid();

	bool isTileOccupied(int row, int col) const;

	bool inBounds(int row, int col, int shipSize, int pivot, bool horizontal) const;

	void placeShip(int row, int col, int shipSize, int pivot, bool horizontal);

	void markHit(int row, int col);

	void markMiss(int row, int col);

	char getCell(int row, int col) const;


private:
	char cells[GRID_SIZE][GRID_SIZE]{};
};
} // namespace BattleshipsHW

#endif // GRID_H
