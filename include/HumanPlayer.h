
#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
namespace BattleshipsHW {

class HumanPlayer : public Player {
public:
	explicit HumanPlayer(const char *str) : Player(str) {};
	void placeAllShips() override;
	void makeMove(Player *opponent, int row, int col) override;
};

} // namespace BattleshipsHW

#endif // HUMANPLAYER_H
