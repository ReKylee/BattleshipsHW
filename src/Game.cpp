#include <Game.h>
#include <GridRenderer.h>
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
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

	auto on_click_on_opponent = [&] {
		player1->makeMove(player2, selected_y % Grid::GRID_SIZE, selected_x % Grid::GRID_SIZE);
	};

	GridRenderer p1GridRenderer(*player1, &selected_x, &selected_y);
	GridRenderer p2GridRenderer(*player2, &selected_x, &selected_y);

	std::vector<std::string> p1ShipNames;
	p1ShipNames.reserve(player1->NUM_SHIPS);

	int p1ShipsIndex = 0;

	for (int i = 0; i < Player::NUM_SHIPS; ++i) {
		p1ShipNames.emplace_back(player1->getShip(i).getName());
	}
	RadioboxOption radiobox_option = RadioboxOption::Simple();
	radiobox_option.entries		   = &p1ShipNames;
	radiobox_option.on_change	   = [&] { player1->selectShip(p1ShipsIndex); };
	radiobox_option.selected	   = &p1ShipsIndex;

	const auto p1ShipsList = Radiobox(radiobox_option);


	auto	   p1_on_click		 = [&] { player1->placeSelectedShip(selected_y, selected_x); };
	const auto place_ship_button = Button("Place Ship", p1_on_click);

	auto layout = Container::Horizontal({//
										 p1GridRenderer.gridRenderer, p2GridRenderer.gridRenderer,
										 Container::Vertical({place_ship_button, p1ShipsList})}) //
				  | bgcolor(Color::Blue) | color(Color::DarkBlue);

	layout |= CatchEvent([&](Event event) {
		if (event.is_mouse() && event.mouse().button == Mouse::Right && event.mouse().motion == Mouse::Pressed) {
			player1->rotateSelectedShip();
			return true;
		}
		return false;
	});
	player2->placeAllShips();
	screen.Loop(layout);
}

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
}
void Game::setup() const { MainGameScreen(); }
void Game::start() const {}
} // namespace BattleshipsHW
