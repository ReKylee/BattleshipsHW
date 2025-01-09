#pragma once

#include <functional>
#include <player.h>
#include "ftxui/component/component_base.hpp"

namespace BattleshipsHW {
using namespace ftxui;
class GridRenderer {
public:
	/**
	 * @brief Construct a new Grid Renderer object
	 *
	 * @param p Player object, for the grid
	 * @param og_selected_x Original selected x index, set by FTXUI
	 * @param og_selected_y Original selected y index, set by FTXUI
	 * @param on_click_func Function to call when clicking on cell
	 */
	GridRenderer(Player &p, int *og_selected_x, int *og_selected_y, std::function<void()> on_click_func = [] {});

	GridRenderer(const GridRenderer &)			  = delete;
	GridRenderer &operator=(const GridRenderer &) = delete;

	/**
	 * @brief A component holding the grid
	 *
	 * @return Component
	 */
	Component gridComponent;

	/**
	 * @brief A renderer for the grid
	 *
	 * @return Component
	 */
	Component gridRenderer;
	/**
	 * @brief Function to call when clicking on a cell
	 *
	 */
	std::function<void()> on_click;
	/**
	 * @brief Selected x and y indices
	 *
	 */
	int *selected_x;
	int *selected_y;

private:
	Player &player;
};


} // namespace BattleshipsHW
