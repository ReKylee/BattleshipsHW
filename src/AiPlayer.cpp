
#include "AiPlayer.h"
#include <cstdlib>
int getRandomCoordinate() {
	// Ensure srand(...) is called in main
	return std::rand() % 10;
}

void BattleshipsHW::AiPlayer::placeAllShips() {
	for (const auto &ship: ships) {
		const bool horizontal = std::rand() % 2;
		int		   row = getRandomCoordinate(), col = getRandomCoordinate();

		while (!grid.inBounds(row, col, ship->getSize(), ship->getPivot(), horizontal)) {
			row = getRandomCoordinate();
			col = getRandomCoordinate();
		}

		grid.placeShip(row, col, ship->getSize(), ship->getPivot(), horizontal);
	}
}
void BattleshipsHW::AiPlayer::makeMove(Player *opponent, int row, int col) {}
