
#include "GridRenderer.h"

#include <ftxui/dom/table.hpp>

#include "ftxui/component/component.hpp"
using namespace BattleshipsHW;

GridRenderer::GridRenderer(Player &p, int *og_selected_x, int *og_selected_y, std::function<void()> on_click_func) :
	on_click(on_click_func), selected_x(og_selected_x), selected_y(og_selected_y), player(p) {

	gridComponent = Container::Vertical({}, selected_x);
	for (int j = 0; j < Grid::GRID_SIZE; ++j) {
		Component buttons_in_row = Container::Horizontal({}, selected_y);

		for (int i = 0; i < Grid::GRID_SIZE; ++i) {

			ButtonOption option = ButtonOption::Ascii();
			option.on_click		= on_click;
			option.transform	= [this, i, j](const EntryState &s) {
				   std::string cell(1, player.getCell(i, j));

				   const bool ships_hidden	   = player.shipsHidden();
				   const auto ship			   = player.getCurrentlySelectedShip();
				   const bool is_placing_ships = player.isPlacingShips();
				   if (ships_hidden && cell[0] == Grid::OCCUPIED)
					   cell = Grid::EMPTY;

				   const std::string label = s.focused ? "[" + cell + "]" //
													   : " " + cell + " ";

				   auto element = text(label);

				   if (is_placing_ships && !ships_hidden) {

					   if (const auto extents = ship.getAABBat(*selected_y, *selected_x);
						   i >= extents[0] && i <= extents[1] && j >= extents[2] && j <= extents[3]) {
						   element |= bgcolor(Color::Red);
					   }
				   }

				   return element;
			};

			buttons_in_row->Add(Button(std::move(option)));
		}
		gridComponent->Add(std::move(buttons_in_row));
	}

	gridRenderer = Renderer(gridComponent, [&] {
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
			const auto button_row = gridComponent->ChildAt(i);
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
}
