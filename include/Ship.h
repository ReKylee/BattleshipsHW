#pragma once
#include <array>
#include <string>

namespace BattleshipsHW {

// ---------------- Base Ship Class ----------------
class Ship {
public:
	/**
	 * @brief Construct a new Ship object
	 *
	 * @param shipName Name of the ship
	 * @param shipSize Size of the ship
	 * @param shipPivot Pivot point of the ship
	 */
	Ship(const char *shipName, int shipSize, int shipPivot);

	virtual ~Ship();

	/**
	 * @brief Take a hit on the ship, may be implemented in derived classes
	 *
	 */
	virtual void takeHit();

	/**
	 * @brief Check if the ship is sunk
	 *
	 * @return true if the ship is sunk, false otherwise
	 */
	bool isSunk() const;

	/**
	 * @brief Check if the ship is horizontal
	 *
	 * @return true if the ship is horizontal, false otherwise
	 */
	bool isHorizontal() const;

	/**
	 * @brief Get the size of the ship
	 *
	 * @return size of the ship
	 */
	int getSize() const;

	/**
	 * @brief Get the position of the ship
	 *
	 * @return position of the ship
	 */
	std::array<int, 2> getPosition() const;

	/**
	 * @brief Get the pivot point of the ship
	 *
	 * @return pivot point of the ship
	 */
	int getPivot() const;

	/**
	 * @brief Get the number of hits taken by the ship
	 *
	 * @return number of hits taken by the ship
	 */
	int getHitsTaken() const;

	/**
	 * @brief Get the name of the ship
	 *
	 * @return name of the ship
	 */
	std::string getName() const;

	/**
	 * @brief Get the AABB of the ship at a given position
	 *
	 * @param row Row of the ship
	 * @param col Column of the ship
	 * @param expand Expand the AABB by this amount
	 * @return AABB of the ship
	 */
	std::array<int, 4> getAABBat(int row, int col, int expand = 0) const;

	/**
	 * @brief Get the AABB of the ship at its current position
	 *
	 * @return AABB of the ship
	 */
	std::array<int, 4> getAABB() const;

	/**
	 * @brief Check if the ship is placed
	 *
	 * @return true if the ship is placed, false otherwise
	 */
	bool isPlaced() const;

	/**
	 * @brief Set the placed state of the ship
	 *
	 * @param place Placed state of the ship
	 */
	void setPlaced(bool place);

	/**
	 * @brief Set the position of the ship
	 *
	 * @param row Row of the ship
	 * @param col Column of the ship
	 */
	void setPos(int row, int col);

	/**
	 * @brief Set the horizontal state of the ship
	 *
	 * @param h Horizontal state of the ship
	 */
	void setHorizontal(bool h);

	/**
	 * @brief Rotate the ship, horizontal = !horizontal
	 *
	 */
	void rotate();

private:
	std::string		   name;	   ///< Name of the ship
	int				   size;	   ///< Size of the ship
	int				   pivot;	   ///< Pivot point of the ship
	std::array<int, 2> pos;		   ///< Position of the ship
	int				   hitsTaken;  ///< Number of hits taken by the ship
	bool			   horizontal; ///< Horizontal state of the ship
	bool			   placed;	   ///< Placed state of the ship
};

// ---------------- Derived Ship Classes ----------------
class Carrier : public Ship {
public:
	Carrier() : Ship("Carrier", 5, 2) {}
};

class Battleship : public Ship {
public:
	Battleship() : Ship("Battleship", 4, 1) {}
};

class Cruiser : public Ship {
public:
	Cruiser() : Ship("Cruiser", 3, 1) {}
};

class Submarine : public Ship {
public:
	Submarine() : Ship("Submarine", 3, 1) {}
};

class Destroyer : public Ship {
public:
	Destroyer() : Ship("Destroyer", 2, 0) {}
};

} // namespace BattleshipsHW
