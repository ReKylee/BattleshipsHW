#include <Game.h>
#include <GridRenderer.h>
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
namespace BattleshipsHW {

// ---------------- Constructors ----------------
Game::Game(Player *p1, Player *p2) : player1(p1), player2(p2) {}

// ---------------- Destructor ----------------
Game::~Game() {
	delete player1;
	delete player2;
}


// ---------------- Main Game Screen ----------------
void Game::MainGameScreen() const {
	auto screen = ScreenInteractive::Fullscreen();
	using namespace ftxui;

	// Place all ships for player 2
	player2->placeAllShips();

	// Variables for UI state
	int			selected_y = 0, selected_x = 0;
	std::string winnerName;
	bool		showWinner = false;

	// Helper: Handles game moves and checks for winner
	auto handleGameMove = [&]() {
		if (!player1->isPlacingShips() && !player2->isPlacingShips()) {
			player1->makeMove(player2, selected_y % Grid::GRID_SIZE, selected_x % Grid::GRID_SIZE);

			if (player2->allShipsSunk()) {
				winnerName = player1->getName();
				showWinner = true;
				return;
			}
			player2->makeMove(player1, selected_y % Grid::GRID_SIZE, selected_x % Grid::GRID_SIZE);

			if (player1->allShipsSunk()) {
				winnerName = player2->getName();
				showWinner = true;
			}
		}
	};

	// Helper: Handles placing a ship for player 1
	auto placeShipForPlayer1 = [&]() { player1->placeSelectedShip(selected_y, selected_x); };

	// Create grid renderers
	GridRenderer p1GridRenderer(*player1, &selected_x, &selected_y);
	GridRenderer p2GridRenderer(*player2, &selected_x, &selected_y, handleGameMove);

	// Create radiobox for player 1's ship selection
	std::vector<std::string> p1ShipNames;
	for (int i = 0; i < Player::NUM_SHIPS; ++i) {
		p1ShipNames.emplace_back(player1->getShip(i).getName());
	}

	int			   p1ShipsIndex	  = 0;
	RadioboxOption radioboxOption = RadioboxOption::Simple();
	radioboxOption.entries		  = &p1ShipNames;
	radioboxOption.selected		  = &p1ShipsIndex;
	radioboxOption.on_change	  = [&]() { player1->selectShip(p1ShipsIndex); };

	const auto p1ShipsList = Radiobox(radioboxOption);

	// UI Components
	const auto placeShipButton = Button("Place Ship", placeShipForPlayer1);
	const auto quitButton	   = Button("Quit", [&screen] { screen.Exit(); });
	const auto winnerComponent = Renderer(quitButton, [&]() {
		return vbox({text(winnerName), quitButton->Render()}) | center | border | bgcolor(Color::Blue) |
			   color(Color::DarkBlue);
	});

	// Layout for the main game screen
	auto gameLayout = Container::Horizontal({p1GridRenderer.gridRenderer, p2GridRenderer.gridRenderer,
											 Container::Vertical({placeShipButton, p1ShipsList})}) |
					  bgcolor(Color::Blue) | color(Color::DarkBlue);

	// Event handling
	gameLayout |= CatchEvent([&](Event event) {
		if (player1->isPlacingShips() && event.is_mouse() && event.mouse().button == Mouse::Right &&
			event.mouse().motion == Mouse::Pressed) {
			player1->rotateSelectedShip();
			return true;
		}
		return false;
	});

	// Show winner modal if a player wins
	gameLayout |= Modal(winnerComponent, &showWinner);

	// Start the main screen loop
	screen.Loop(gameLayout);
}

// ---------------- Exit Screen ----------------
Component Exit(ScreenInteractive &screen, bool &exit_confirmed) {
	auto exit_btn	= Button("Exit", screen.ExitLoopClosure()) | center;
	auto return_btn = Button("Return to Main Menu", [&] { exit_confirmed = false; }) | center;
	auto layout		= Container::Horizontal({exit_btn, return_btn}) | center;
	layout |= Renderer([&](const Element &inner) {
		return vbox({text("Are you sure you want to exit?") | bold | center, separator(), inner | center}) | border;
	});
	return layout;
}

// ---------------- Start Game ----------------
void Game::start() const { MainGameScreen(); }

// ---------------- Main Menu Screen ----------------
// ReSharper disable once CppMemberFunctionMayBeStatic
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
		return e | bgcolor(Color::Blue) | color(Color::DarkBlue);
	});
	main_menu |= Modal(exit, &exit_menu);
	screen.Loop(main_menu);
}

} // namespace BattleshipsHW
