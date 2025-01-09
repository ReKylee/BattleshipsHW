#include <cstdlib> // For std::rand(), std::srand()
#include <ctime>   // For std::time()
#include "AiPlayer.h"
#include "Game.h"
#include "HumanPlayer.h"

using namespace BattleshipsHW;

int main() {
	// Seed the random number generator for AI placement and moves
	// You need it to stay HERE when you use random in the AiPlayer class
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Create two players: one human, one AI
	Player *p1 = new HumanPlayer("Human");
	Player *p2 = new AiPlayer("Computer", true);

	// Create the Game object with the two players
	const Game game(p1, p2);

	game.run();
	game.start();
	return 0;
}
