#include "Ship.h"

#include <cstring>
#include <iostream>

bool BattleshipsHW::Ship::isSunk() const { return hitsTaken >= size; }

BattleshipsHW::Ship::Ship(const char *shipName, int shipSize, int shipPivot) :
	name(new char[strlen(shipName) + 1]), size(shipSize), pivot(shipPivot), hitsTaken(0) {
	strcpy(name, shipName);
}

BattleshipsHW::Ship::~Ship() { delete[] name; }

void BattleshipsHW::Ship::takeHit() {
	if (hitsTaken < size) {
		hitsTaken++;
		std::cout << name << " got hit!" << std::endl;
	}
}
int	  BattleshipsHW::Ship::getSize() const { return size; }
int	  BattleshipsHW::Ship::getPivot() const { return pivot; }
int	  BattleshipsHW::Ship::getHitsTaken() const { return hitsTaken; }
char *BattleshipsHW::Ship::getName() const { return name; }
