
#ifndef GRIDRENDERER_H
#define GRIDRENDERER_H

#include <player.h>
namespace BattleshipsHW {
using namespace ftxui;
class GridRenderer {
public:
	GridRenderer(Player *p, int *selected_x, int *selected_y);

private:
	Player				 *player;
	Component			  gridComponent;
	Component			  gridRenderer;
	std::function<void()> on_click;
};


} // namespace BattleshipsHW
#endif // GRIDRENDERER_H
