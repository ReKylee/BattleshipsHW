#ifndef PLAYER_H
#define PLAYER_H
#include <Grid.h>
#include <Ship.h>

namespace BattleshipsHW {

class Player {
public:
	explicit Player(const char *str);
	virtual ~Player();
	virtual void placeAllShips()							  = 0;
	virtual void makeMove(Player *opponent, int row, int col) = 0;
	bool		 allShipsSunk() const;
	char		 getCell(int row, int col) const { return grid.getCell(row, col); }

protected:
	char *playerName;
	Ship *ships[5];
	Grid  grid;
};

} // namespace BattleshipsHW

#endif // PLAYER_H
