
#include "GridRenderer.h"

#include <ftxui/dom/table.hpp>

#include "ftxui/component/component.hpp"
using namespace BattleshipsHW;

GridRenderer::GridRenderer(Player *p, int *selected_x, int *selected_y, std::function<void()> on_click_func) :
	on_click(on_click_func), player(p) {

	if (!player) {
		throw std::invalid_argument("Player cannot be null");
	}

	gridComponent = Container::Vertical({}, selected_y);
	for (int j = 0; j < Grid::GRID_SIZE; ++j) {
		Component buttons_in_row = Container::Horizontal({}, selected_x);

		for (int i = 0; i < Grid::GRID_SIZE; ++i) {

			ButtonOption option = ButtonOption::Ascii();
			option.on_click		= on_click;
			option.transform	= [this, i, j](const EntryState &s) {
				   std::string cell(1, player->getCell(i, j));
				   const bool  ships_hidden = player->shipsHidden();

				   if (ships_hidden && cell[0] == Grid::OCCUPIED)
					   cell = Grid::EMPTY;

				   const std::string label = s.focused && !ships_hidden ? "[" + cell + "]" //
																		: " " + cell + " ";

				   const auto element = text(label);

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
