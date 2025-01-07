#ifndef SHIP_H
#define SHIP_H

namespace BattleshipsHW {
class Ship {
public:
	Ship(const char *shipName, int shipSize, int shipPivot);

	virtual ~Ship();

	virtual void takeHit();

	bool  isSunk() const;
	int	  getSize() const;
	int	  getPivot() const;
	int	  getHitsTaken() const;
	char *getName() const;

private:
	char *name;
	int	  size;
	int	  pivot;
	int	  hitsTaken;
};

class Carrier : public Ship {
public:
	Carrier() : Ship("Carrier", 5, 2) {};
};

class Battleship : public Ship {
public:
	Battleship() : Ship("Battleship", 4, 1) {};
};

class Cruiser : public Ship {
public:
	Cruiser() : Ship("Cruiser", 3, 1) {};
};

class Submarine : public Ship {
public:
	Submarine() : Ship("Submarine", 3, 1) {};
};

class Destroyer : public Ship {
public:
	Destroyer() : Ship("Destroyer", 2, 0) {};
};
} // namespace BattleshipsHW


#endif // SHIP_H
