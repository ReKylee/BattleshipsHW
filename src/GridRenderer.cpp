
#include "GridRenderer.h"

#include <ftxui/dom/table.hpp>

#include "ftxui/component/component.hpp"
using namespace BattleshipsHW;

GridRenderer::GridRenderer(Player &p, int *og_selected_x, int *og_selected_y, std::function<void()> on_click_func) :
	on_click(on_click_func), selected_x(og_selected_x), selected_y(og_selected_y), player(p) {

	gridComponent = Container::Vertical({}, selected_y);
	for (int j = 0; j < Grid::GRID_SIZE; ++j) {
		Component buttons_in_row = Container::Horizontal({}, selected_x);

		for (int i = 0; i < Grid::GRID_SIZE; ++i) {

			ButtonOption option = ButtonOption::Ascii();
			option.on_click		= on_click;
			option.transform	= [this, i, j](const EntryState &s) {
				   std::string cell(1, player.getCell(j, i));

				   const bool ships_hidden	   = player.shipsHidden();
				   const auto ship			   = player.getCurrentlySelectedShip();
				   const bool is_placing_ships = player.isPlacingShips();
				   if (ships_hidden && cell[0] == Grid::OCCUPIED)
					   cell = Grid::EMPTY;

				   const std::string label = s.focused ? "[" + cell + "]" //
													   : " " + cell + " ";

				   auto element = text(label);

				   if (!ship.isPlaced() && is_placing_ships && !ships_hidden) {

					   //{startRow, endRow, startCol, endCol};
					   if (const auto extents = ship.getAABBat(*selected_y, *selected_x);
						   j >= extents[0] && j <= extents[1] && i >= extents[2] && i <= extents[3]) {
						   element = text(label) | bgcolor(Color::Pink3) | color(Color::Black);
					   }
				   }
				   element = text(label) | bgcolor(Color::Blue) | color(Color::DarkBlue);

				   return element;
			};

			buttons_in_row->Add(Button(std::move(option)));
		}
		gridComponent->Add(std::move(buttons_in_row));
	}

	gridRenderer = Renderer(gridComponent, [&] {
		// Create a vector to hold the rows of the table
		std::vector<Elements> rows;

		// Add the header row with column labels
		Elements header_row;
		header_row.push_back(text("")); // Empty corner cell for the top-left
		for (int count = 0; count < Grid::GRID_SIZE; ++count) {
			const char label[2] = {static_cast<char>('A' + count), '\0'};
			header_row.push_back(text(label)); // Column labels (A, B, C, ...)
		}
		rows.push_back(header_row);

		// Loop through rows to create buttons and add them to the table
		for (int j = 0; j < Grid::GRID_SIZE; ++j) {
			Elements row;
			row.push_back(text(std::to_string(j + 1))); // Row labels (1, 2, 3, ...)
			const auto button_row = gridComponent->ChildAt(j);
			// Create a row of buttons for this row
			for (int i = 0; i < Grid::GRID_SIZE; ++i) {

				// Add the button to the row
				const auto button = button_row->ChildAt(i);
				row.push_back(button->Render());
			}

			// Add the row to the elements vector
			rows.push_back(row);
		}

		// Create the table from the elements
		auto table = Table(rows);
		table.SelectAll().Border(LIGHT);


		return table.Render();
	});
}
