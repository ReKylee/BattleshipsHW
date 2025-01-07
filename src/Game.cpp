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
	int selected_y, selected_x;

	auto GridComponent = [&](const Player *p, const std::function<void()> &on_click) {
		auto gridComponent = Container::Vertical({}, &selected_y);
		for (int y = 0; y < Grid::GRID_SIZE; y++) {
			const auto row = Container::Horizontal({}, &selected_x);
			for (int x = 0; x < Grid::GRID_SIZE; x++) {
				const char single_char[2] = {p->getCell(x, y), '\0'};

				const auto button = Button(single_char, on_click, ButtonOption::Ascii());

				row->Add(button);
			}

			gridComponent->Add(row);
		}
		return gridComponent;
	};

	// TODO: Theory, combine both GridRenderer and renderer into one renderer.
	const auto GridRenderer = [&](const Component &grid) {
		return Renderer(grid, [&] {
			std::vector<Elements> elements;
			elements.reserve(Grid::GRID_SIZE + 1);

			// Add the header row (column letters)
			Elements header_row;
			header_row.reserve(Grid::GRID_SIZE + 1);
			header_row.emplace_back(text("")); // Empty corner cell (top-left)

			for (int x = 0; x < Grid::GRID_SIZE; x++) {
				const char single_char[2] = {static_cast<char>('A' + x), '\0'};
				header_row.emplace_back(text(single_char)); // Letters A, B, C, ...
			}
			elements.push_back(header_row);

			// Add the rows of buttons for the player's grid
			for (int y = 0; y < Grid::GRID_SIZE; y++) {
				Elements render_row;
				render_row.reserve(Grid::GRID_SIZE + 1);

				// Add the number at the start of each row (1, 2, 3, ...)
				render_row.emplace_back(text(std::to_string(y + 1)));

				// Create a row container for the player's buttons (initialized once per row)
				const auto row = grid->ChildAt(y);
				for (int x = 0; x < Grid::GRID_SIZE; x++) {
					const auto btn = row->ChildAt(x);
					render_row.emplace_back(btn->Render());
				}

				// Add the row to the container and push the rendered row to the elements vector
				elements.push_back(render_row);
			}

			// Create a table from the elements
			auto table = Table(elements);
			table.SelectAll().Border(LIGHT);
			table.SelectAll().Separator(EMPTY);

			return table.Render();
		});
	};

	const auto p1Grid = GridComponent(player1, [&] { player1->makeMove(player2, selected_x, selected_y); });
	const auto p2Grid = GridComponent(player2, [&] { player2->makeMove(player1, selected_x, selected_y); });

	const auto p1Renderer = GridRenderer(p1Grid);
	const auto p2Renderer = GridRenderer(p2Grid);

	const auto layout	= Container::Horizontal({p1Renderer, p2Renderer});
	const auto renderer = Renderer(layout, [&] { return hbox({p1Renderer->Render(), p2Renderer->Render()}); });

	screen.Loop(renderer);
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

	MainGameScreen();
}
void Game::setup() const {}
void Game::start() const {}
} // namespace BattleshipsHW
