﻿#pragma once

#include "Player.h"
namespace BattleshipsHW {

class AiPlayer : public Player {
public:
	explicit AiPlayer(const char *str, const bool shouldHideShips = false) : Player(str, shouldHideShips) {};
	void placeAllShips() override;
	void makeMove(Player *opponent, int row, int col) override;
};

} // namespace BattleshipsHW
