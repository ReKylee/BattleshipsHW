
#include "AiPlayer.h"
#include <cstdlib>
int getRandomCoordinate() {
	// Ensure srand(...) is called in main
	return std::rand() % 10;
}

void BattleshipsHW::AiPlayer::placeAllShips() {
	for (const auto &ship: ships) {
		ship->setHorizontal(std::rand() % 2);
		int row = getRandomCoordinate(), col = getRandomCoordinate();

		while (!grid.inBounds(row, col, *ship)) {
			row = getRandomCoordinate();
			col = getRandomCoordinate();
		}

		grid.placeShip(row, col, *ship);
	}
}
void BattleshipsHW::AiPlayer::makeMove(Player *opponent, const int row = getRandomCoordinate(),
									   const int col = getRandomCoordinate()) {
	Player::makeMove(opponent, row, col);
}
