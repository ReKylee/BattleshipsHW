#ifndef SHIP_H
#define SHIP_H
#include <array>

namespace BattleshipsHW {
class Ship {
public:
	Ship(const char *shipName, int shipSize, int shipPivot);

	virtual ~Ship();

	virtual void takeHit();

	bool			   isSunk() const;
	bool			   isHorizontal() const;
	int				   getSize() const;
	int				   getPivot() const;
	int				   getHitsTaken() const;
	char			  *getName() const;
	std::array<int, 4> getAABBat(int row, int col, int expand = 0) const;
	void			   setHorizontal(bool h);

private:
	char *name;
	int	  size;
	int	  pivot;
	int	  hitsTaken;
	bool  horizontal;
};

class Carrier : public Ship {
public:
	Carrier() : Ship("Carrier", 5, 2) {};
};

class Battleship : public Ship {
public:
	Battleship() : Ship("Battleship", 5, 1) {};
};

class Cruiser : public Ship {
public:
	Cruiser() : Ship("Cruiser", 5, 1) {};
};

class Submarine : public Ship {
public:
	Submarine() : Ship("Submarine", 5, 1) {};
};

class Destroyer : public Ship {
public:
	Destroyer() : Ship("Destroyer", 5, 0) {};
};
} // namespace BattleshipsHW


#endif // SHIP_H
