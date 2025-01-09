
#pragma once

#include <Player.h>
#include <ftxui/component/loop.hpp>

namespace BattleshipsHW {
using namespace ftxui;
class Game {
public:
	// Constructors
	Game(Player *p1, Player *p2);
	// Destructor
	~Game();

	// Methods
	/**
	 * @brief This function starts the game.
	 */
	void start() const;
	/**
	 * @brief This function shows the main menu screen.
	 */
	void run() const;
	// These control the different screens you see.
	void MainGameScreen() const;

private:
	Player *player1;
	Player *player2;
};

} // namespace BattleshipsHW
