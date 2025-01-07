#include <cstdlib> // For std::rand(), std::srand()
#include <ctime>   // For std::time()
#include <iostream>
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
	Player *p2 = new AiPlayer("Computer");

	// Create the Game object with the two players
	Game game(p1, p2);

	game.run();
	// Set up the game (place all ships)

	game.start();
	return 0;
}
