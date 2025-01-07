
#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
namespace BattleshipsHW
{

class AiPlayer : public Player {
public:
	explicit AiPlayer(const char* str) : Player(str) {};
	void placeAllShips() override;
	void makeMove(Player *opponent, int row, int col) override;
};

}


#endif //AIPLAYER_H
