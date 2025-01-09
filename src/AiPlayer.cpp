
#include "AiPlayer.h"
#include <cstdlib>
int getRandomCoordinate() {
	// Ensure srand(...) is called in main
	return std::rand() % 10;
}

void BattleshipsHW::AiPlayer::placeAllShips() {
	for (Ship *ship: ships) {
		ship->setHorizontal(static_cast<bool>(std::rand()) % 2);
		int row = getRandomCoordinate(), col = getRandomCoordinate();

		while (!grid.inBounds(row, col, *ship)) {
			row = getRandomCoordinate();
			col = getRandomCoordinate();
		}

		grid.placeShip(row, col, *ship);
		ship->setPlaced(true);
		ship->setPos(row, col);
	}
}
void BattleshipsHW::AiPlayer::makeMove(Player *opponent, const int row, const int col) {
	int rand_row = getRandomCoordinate(), rand_col = getRandomCoordinate();

	while (opponent->getCell(rand_row, rand_col) == Grid::MISS || opponent->getCell(rand_row, rand_col) == Grid::HIT) {
		rand_row = getRandomCoordinate();
		rand_col = getRandomCoordinate();
	}
	Player::makeMove(opponent, rand_row, rand_col);
}
