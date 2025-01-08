#ifndef PLAYER_H
#define PLAYER_H
#include <Grid.h>
#include <Ship.h>

namespace BattleshipsHW {

class Player {
public:
	explicit Player(const char *str, bool shouldHideShips = false);
	virtual ~Player();

	bool		 allShipsSunk() const;
	virtual void placeAllShips() = 0;
	virtual void makeMove(Player *opponent, int row, int col);

	void markHit(int row, int col);
	void markMiss(int row, int col);

	char getCell(int row, int col) const;
	bool shipsHidden() const;

protected:
	char *playerName;
	Ship *ships[5];
	Grid  grid;
	bool  hideShips;
};

} // namespace BattleshipsHW

#endif // PLAYER_H
