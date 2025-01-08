
#ifndef GRIDRENDERER_H
#define GRIDRENDERER_H

#include <player.h>
namespace BattleshipsHW {
using namespace ftxui;
class GridRenderer {
public:
	GridRenderer(Player &p, int *og_selected_x, int *og_selected_y, std::function<void()> on_click_func = [] {});

	GridRenderer(const GridRenderer &)			  = delete;
	GridRenderer &operator=(const GridRenderer &) = delete;

	Component			  gridComponent;
	Component			  gridRenderer;
	std::function<void()> on_click;
	int					 *selected_x;
	int					 *selected_y;

private:
	Player &player;
};


} // namespace BattleshipsHW
#endif // GRIDRENDERER_H
