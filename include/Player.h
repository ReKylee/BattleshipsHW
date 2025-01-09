#pragma once

#include <Grid.h>
#include <Ship.h>

namespace BattleshipsHW {

class Player {

public:
	constexpr static int NUM_SHIPS = 5;
	/**
	 * @brief Construct a new Player object
	 *
	 * @param str
	 * @param shouldHideShips
	 */
	explicit Player(const char *str, bool shouldHideShips = false);
	virtual ~Player();

	/**
	 * @brief Check if all ships are sunk
	 *
	 * @return true if all ships are sunk
	 */
	bool allShipsSunk() const;

	/**
	 * @brief Check if the user should view the ships
	 *
	 * @return true if ships are hidden
	 */
	bool shipsHidden() const;

	/**
	 * @brief Check if the player is still placing ships
	 *
	 * @return true if the player is placing ships
	 */
	bool isPlacingShips() const;

	/**
	 * @brief Get a cell in the grid
	 *
	 * @param row
	 * @param col
	 * @return char
	 */
	char getCell(int row, int col) const;

	/**
	 * @brief Get the player's name
	 *
	 * @return std::string
	 */
	std::string getName() const;

	/**
	 * @brief Get a ship at a specific index
	 *
	 * @param index index in the ship array
	 * @return Reference to the Ship
	 */
	Ship &getShip(int index) const;

	/**
	 * @brief Get the currently selected ship
	 *
	 * @return Reference to the Ship
	 */
	Ship &getCurrentlySelectedShip() const;

	/**
	 * @brief Sets currently selected ship
	 *
	 * @param index index in the ship array
	 */
	void selectShip(int index);

	/**
	 * @brief Places the selected ship
	 *
	 * @param row
	 * @param col
	 */
	void placeSelectedShip(int row, int col);

	/**
	 * @brief Rotates the selected ship
	 */
	void rotateSelectedShip() const;

	/**
	 * @brief Implemented by the derived classes, places all ships on the grid
	 */
	virtual void placeAllShips() = 0;

	/**
	 * @brief May be implemented by the derived classes, makes a move and marks it on the grid
	 *
	 * @param opponent
	 * @param row
	 * @param col
	 */
	virtual void makeMove(Player *opponent, int row, int col);

	/**
	 * @brief Marks a hit on the grid
	 *
	 * @param row
	 * @param col
	 */
	void markHit(int row, int col);

	/**
	 * @brief Marks a miss on the grid
	 *
	 * @param row
	 * @param col
	 */
	void markMiss(int row, int col);


protected:
	std::string playerName;

	Ship *ships[NUM_SHIPS];
	int	  currentlySelectedShipIndex;

	Grid grid;
	bool hideShips;
};
} // namespace BattleshipsHW
