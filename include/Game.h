
#ifndef GAME_H
#define GAME_H

#include <Player.h>
#include <ftxui/component/loop.hpp>
#include <ftxui/dom/elements.hpp>

namespace BattleshipsHW {
using namespace ftxui;
class Game {
public:
	// Constructors
	Game(Player *p1, Player *p2);
	// Destructor
	~Game();

	// Methods
	void setup() const;
	void start() const;
	bool isGameOver() const;
	// These control the different screens you see.
	void run() const;
	void MainGameScreen() const;

private:
	Player *player1;
	Player *player2;
};

} // namespace BattleshipsHW

#endif // GAME_H
