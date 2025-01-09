
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
	}
}
void BattleshipsHW::AiPlayer::makeMove(Player *opponent, const int row = getRandomCoordinate(),
									   const int col = getRandomCoordinate()) {
	Player::makeMove(opponent, row, col);
}
