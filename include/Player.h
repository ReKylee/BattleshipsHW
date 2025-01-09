#ifndef PLAYER_H
#define PLAYER_H
#include <Grid.h>
#include <Ship.h>

namespace BattleshipsHW {

class Player {

public:
	constexpr static int NUM_SHIPS = 5;
	explicit Player(const char *str, bool shouldHideShips = false);
	virtual ~Player();

	bool allShipsSunk() const;
	bool shipsHidden() const;
	bool isPlacingShips() const;

	char		getCell(int row, int col) const;
	std::string getName() const;
	Ship	   &getShip(int index) const;
	Ship	   &getCurrentlySelectedShip() const;

	void		 selectShip(int index);
	void		 placeSelectedShip(int row, int col);
	void		 rotateSelectedShip() const;
	virtual void placeAllShips() = 0;
	virtual void makeMove(Player *opponent, int row, int col);

	void markHit(int row, int col);
	void markMiss(int row, int col);


protected:
	std::string playerName;
	Ship	   *ships[NUM_SHIPS];
	int			currentlySelectedShipIndex;

	Grid grid;
	bool hideShips;
};

} // namespace BattleshipsHW

#endif // PLAYER_H
