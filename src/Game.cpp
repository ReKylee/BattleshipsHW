#include <Game.h>
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

	const auto on_click = [&] { player1->makeMove(player2, selected_x, selected_y); };


	const Component grid = Container::Vertical({}, &selected_y);

	for (int j = 0; j < Grid::GRID_SIZE; ++j) {
		Component buttons_in_row = Container::Horizontal({}, &selected_x);

		for (int i = 0; i < Grid::GRID_SIZE; ++i) {

			ButtonOption option = ButtonOption::Ascii();
			option.on_click		= on_click;
			option.transform	= [this, i, j](const EntryState &s) {
				   const char single_cell[2] = {player1->getCell(i, j), '\0'};

				   auto element = text(single_cell);

				   return element;
			};

			buttons_in_row->Add(Button("", on_click, std::move(option)));
		}
		grid->Add(std::move(buttons_in_row));
	}

	const auto renderer = Renderer(grid, [&] {
		// Create a vector to hold the rows of the table
		std::vector<Elements> elements;

		// Add the header row with column labels
		Elements header_row;
		header_row.push_back(text("")); // Empty corner cell for the top-left
		for (int j = 0; j < Grid::GRID_SIZE; ++j) {
			const char label[2] = {static_cast<char>('A' + j), '\0'};
			header_row.push_back(text(label)); // Column labels (A, B, C, ...)
		}
		elements.push_back(header_row);

		// Loop through rows to create buttons and add them to the table
		for (int i = 0; i < Grid::GRID_SIZE; ++i) {
			Elements row;
			row.push_back(text(std::to_string(i + 1))); // Row labels (1, 2, 3, ...)
			const auto button_row = grid->ChildAt(i);
			// Create a row of buttons for this row
			for (int j = 0; j < Grid::GRID_SIZE; ++j) {

				// Add the button to the row
				const auto button = button_row->ChildAt(j);
				row.push_back(button->Render());
			}

			// Add the row to the elements vector
			elements.push_back(row);
		}

		// Create the table from the elements
		auto table = Table(elements);
		table.SelectAll().Border(LIGHT);

		return table.Render();
	});


	screen.Loop(renderer);
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
