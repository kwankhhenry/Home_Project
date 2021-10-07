#ifndef CONSOLETABLE_CONSOLETABLE_H
#define CONSOLETABLE_CONSOLETABLE_H

#include <string>
#include <vector>
#include <sstream>
#include "ConsoleTableRow.h"

enum Style {
	BASIC,
	SINGLE_LINE,
	DOUBLE_LINE
};

enum HorizontalSeperator {
	SEPERATOR_TOP,
	SEPERATOR_MIDDLE,
	SEPERATOR_BOTTOM
};

class ConsoleTable {
	public:
		ConsoleTable(Style style);
		void setPadding(unsigned int width);
		void addColumn(std::string name);
		void addRow(ConsoleTableRow *item);
		bool removeRow(unsigned int index);
		bool editRow(std::string data, unsigned int row, unsigned int col);
		void printTable();
	private:
		unsigned int padding;

		std::vector<std::string> columns;
		std::vector<ConsoleTableRow *> entries;

		// Table Style variables
		std::string style_line_horizontal;
		std::string style_line_vertical;
		std::string style_line_cross;
		std::string style_t_intersect_right;
		std::string style_t_intersect_left;
		std::string style_t_intersect_top;
		std::string style_t_intersect_bottom;
		std::string style_edge_topleft;
		std::string style_edge_topright;
		std::string style_edge_buttomleft;
		std::string style_edge_buttomright;

		void printHorizontalSeperator(const std::vector<unsigned int> &maxWidths, HorizontalSeperator seperator) const;
		void setTableStyle(Style style);
		std::string repeatString(std::string input, int n) const;
};
#endif //CONSOLETABLE_CONSOLETABLE_H
