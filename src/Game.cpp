#include <Game.h>
#include <GridRenderer.h>
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
namespace BattleshipsHW {
// --------------------------------------------------
// Constructors
// Default constructor
Game::Game(Player *p1, Player *p2) : player1(p1), player2(p2) {}
// --------------------------------------------------
// Destructor
Game::~Game() {
	delete player1;
	delete player2;
}


// ---------------- Helper Functions ----------------
bool Game::isGameOver() const { return player1->allShipsSunk() || player2->allShipsSunk(); }

// ---------------- Screen Functions ----------------
void Game::MainGameScreen() const {
	auto screen = ScreenInteractive::Fullscreen();
	using namespace ftxui;

	int selected_y = 0, selected_x = 0;

	auto on_click = [&] { player1->makeMove(player2, selected_x, selected_y); };

	GridRenderer p1GridRenderer(player1, &selected_x, &selected_y, on_click);
	GridRenderer p2GridRenderer(player2, &selected_x, &selected_y, on_click);

	p1GridRenderer.on_click = on_click;
	p2GridRenderer.on_click = on_click;

	const auto layout = Container::Horizontal({p1GridRenderer.gridRenderer, p2GridRenderer.gridRenderer});

	screen.Loop(layout);
} // namespace BattleshipsHW

Component Exit(ScreenInteractive &screen, bool &exit_confirmed) {
	auto exit_btn	= Button("Exit", screen.ExitLoopClosure()) | center;
	auto return_btn = Button("Return to Main Menu", [&] { exit_confirmed = false; }) | center;
	auto layout		= Container::Horizontal({exit_btn, return_btn}) | center;
	layout |= Renderer([&](const Element &inner) {
		return vbox({text("Are you sure you want to exit?") | bold | center, separator(), inner | center}) | border;
	});
	return layout;
}

void Game::run() const {
	auto	   screen	 = ScreenInteractive::Fullscreen();
	bool	   exit_menu = false;
	const auto exit		 = Exit(screen, exit_menu);
	auto	   main_menu = Container::Horizontal({

			  Button("Play", [&] { screen.Exit(); }) | center,
			  Button("Exit", [&] { exit_menu = true; }) | center,
	  });
	main_menu |= Renderer([&](Element inner) {
		auto e = vbox({text("Choose!") | bold | center, separator(), inner}) | border | center;
		if (exit_menu)
			e |= dim;
		return e;
	});
	main_menu |= Modal(exit, &exit_menu);
	screen.Loop(main_menu);

	MainGameScreen();
}
void Game::setup() const {}
void Game::start() const {}
} // namespace BattleshipsHW
