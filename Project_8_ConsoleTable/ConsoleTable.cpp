#include "ConsoleTable.h"
#include <iostream>

static const std::string markers[3][11] {
    { "-","|",
    "+","+","+",
    "+","+","+",
    "+","+","+"},
    { "━","┃", 
    "┏","┳","┓",
    "┣","╋","┫",
    "┗","┻","┛"},
    { "═","║",
    "╔","╦","╗",
    "╠","╬","╣",
    "╚","╩","╝"},
};

ConsoleTable::ConsoleTable(Style style) {
	padding = 1;

    setTableStyle(style);
}

void ConsoleTable::addColumn(std::string name) {
    columns.push_back(name);
}

void ConsoleTable::printTable() {
    // Calculate column maxima
    std::vector<unsigned int> maxWidths(columns.size());
    for (std::vector<ConsoleTableRow *>::size_type row = 0; row < entries.size(); row++) {
        for (std::vector<ConsoleTableRow *>::size_type col = 0; col < columns.size(); col++) {
            std::string cellText = entries[row]->getEntry()[col];
            if (columns[col].length() > maxWidths[col])
                maxWidths[col] = columns[col].length();
            if (maxWidths[col] < cellText.length()) {
                maxWidths[col] = cellText.length();
            }
        }
    }

    printHorizontalSeperator(maxWidths, SEPERATOR_TOP);

    // Print column values
    for (std::vector<std::string>::size_type col = 0; col < columns.size(); col++) {
        std::string cellText = columns[col];
        int len = cellText.length();
        std::string paddedText = cellText + std::string(maxWidths[col] - len, ' ');
        std::cout << style_line_vertical << std::string(padding, ' ') << paddedText
                  << std::string(padding, ' ');
        std::cout << (col == columns.size() - 1 ? style_line_vertical + "\n" : "");
    }

    printHorizontalSeperator(maxWidths, SEPERATOR_MIDDLE);

    // Print cell values
    for (std::vector<ConsoleTable *>::size_type row = 0; row < entries.size(); row++) {
        for (std::vector<std::string>::size_type col = 0; col < columns.size(); col++) {
            std::string cellText = entries[row]->getEntry()[col];
            std::string paddedText = cellText + std::string(maxWidths[col] - cellText.length(), ' ');
            std::cout << style_line_vertical << std::string(padding, ' ') << paddedText
                      << std::string(padding, ' ');
        }
        std::cout << style_line_vertical << std::endl;
        if (row == entries.size() - 1)
            printHorizontalSeperator(maxWidths, SEPERATOR_BOTTOM);
        //else
        //    printHorizontalSeperator(maxWidths, SEPERATOR_MIDDLE);
    }
}

void ConsoleTable::printHorizontalSeperator(const std::vector<unsigned int> &maxWidths, HorizontalSeperator seperator) const {
    for (std::vector<std::string>::size_type col = 0; col < columns.size(); ++col) {

        switch (seperator) {
            case SEPERATOR_TOP: {
                std::cout << (col == 0 ? style_edge_topleft : "");
                std::cout << repeatString(style_line_horizontal, padding);
                std::cout << repeatString(style_line_horizontal, maxWidths[col]);
                std::cout << repeatString(style_line_horizontal, padding);
                std::cout << (col != columns.size() - 1 ? style_t_intersect_top : style_edge_topright);
                std::cout << (col == columns.size() - 1 ? "\n" : "");
                break;
            }
            case SEPERATOR_MIDDLE: {
                std::cout << (col == 0 ? style_t_intersect_left : "");
                std::cout << repeatString(style_line_horizontal, padding);
                std::cout << repeatString(style_line_horizontal, maxWidths[col]);
                std::cout << repeatString(style_line_horizontal, padding);
                std::cout << (col != columns.size() - 1 ? style_line_cross : style_t_intersect_right);
                std::cout << (col == columns.size() - 1 ? "\n" : "");
                break;
            }
            case SEPERATOR_BOTTOM: {
                std::cout << (col == 0 ? style_edge_buttomleft : "");
                std::cout << repeatString(style_line_horizontal, padding);
                std::cout << repeatString(style_line_horizontal, maxWidths[col]);
                std::cout << repeatString(style_line_horizontal, padding);
                std::cout << (col != columns.size() - 1 ? style_t_intersect_bottom : style_edge_buttomright);
                std::cout << (col == columns.size() - 1 ? "\n" : "");
                break;
            }
        }
    }
}

void ConsoleTable::addRow(ConsoleTableRow *item) {
    entries.push_back(item);
}

bool ConsoleTable::removeRow(unsigned int index) {
    if (index > entries.size())
        return false;
    entries.erase(entries.begin() + index);
    return true;
}

bool ConsoleTable::editRow(std::string data, unsigned int row, unsigned int col) {
    if(row > entries.size())
        return false;

    if(col > columns.size())
        return false;

	ConsoleTableRow* entry = entries[row];
    entry->editEntry(data, col);
    return true;
}

void ConsoleTable::setPadding(unsigned int width) {
    padding = width;
}

void ConsoleTable::setTableStyle(Style style) {
    switch (style) {
        case BASIC: {
            style_line_horizontal = "-";
            style_line_vertical = "|";
            style_line_cross = "+";

            style_t_intersect_right = "+";
            style_t_intersect_left = "+";
            style_t_intersect_top = "+";
            style_t_intersect_bottom = "+";

            style_edge_topleft = "+";
            style_edge_topright = "+";
            style_edge_buttomleft = "+";
            style_edge_buttomright = "+";
            break;
        }
        case SINGLE_LINE: {
            style_line_horizontal = "━";
            style_line_vertical = "┃";
            style_line_cross = "╋";

            style_t_intersect_right = "┫";
            style_t_intersect_left = "┣";
            style_t_intersect_top = "┳";
            style_t_intersect_bottom = "┻";

            style_edge_topleft = "┏";
            style_edge_topright = "┓";
            style_edge_buttomleft = "┗";
            style_edge_buttomright = "┛";
            break;
        }
        case DOUBLE_LINE: {
            style_line_horizontal = "═";
            style_line_vertical = "║";
            style_line_cross = "╬";

            style_t_intersect_right = "╣";
            style_t_intersect_left = "╠";
            style_t_intersect_top = "╦";
            style_t_intersect_bottom = "╩";

            style_edge_topleft = "╔";
            style_edge_topright = "╗";
            style_edge_buttomleft = "╚";
            style_edge_buttomright = "╝";
            break;
        }
    }
}

std::string ConsoleTable::repeatString(std::string input, int n) const {
    std::ostringstream os;
    for (int i = 0; i < n; i++)
        os << input;
    return os.str();
}
