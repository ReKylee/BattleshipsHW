#ifndef SHIP_H
#define SHIP_H
#include <array>
#include <string>

namespace BattleshipsHW {
class Ship {
public:
	Ship(const char *shipName, int shipSize, int shipPivot);

	virtual ~Ship();

	virtual void takeHit();

	bool			   isSunk() const;
	bool			   isHorizontal() const;
	int				   getSize() const;
	std::array<int, 2> getPosition() const;
	int				   getPivot() const;
	int				   getHitsTaken() const;
	std::string		   getName() const;
	std::array<int, 4> getAABBat(int row, int col, int expand = 0) const;
	std::array<int, 4> getAABB() const;
	void			   setPlaced(bool place);
	void			   setPos(int row, int col);
	bool			   isPlaced() const;
	void			   setHorizontal(bool h);
	void			   rotate();

private:
	std::string		   name;
	int				   size;
	int				   pivot;
	std::array<int, 2> pos;
	int				   hitsTaken;
	bool			   horizontal;
	bool			   placed;
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
