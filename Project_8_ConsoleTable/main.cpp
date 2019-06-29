#include <iostream>
#include "ConsoleTable.h"

int main() {

    ConsoleTable ct(BASIC);
    ct.setPadding(1);

    ct.addColumn("Country");
    ct.addColumn("Name");
    ct.addColumn("Profession");
    ct.addColumn("Age");

    ConsoleTableRow* entry = new ConsoleTableRow(4);
    entry->addEntry("Germany", 0);
    entry->addEntry("Michael", 1);
    entry->addEntry("Computer Engineer", 2);
    entry->addEntry("19", 3);
    ct.addRow(entry);

    ConsoleTableRow* entry2 = new ConsoleTableRow(4);
    entry2->addEntry("England", 0);
    entry2->addEntry("Robert", 1);
    entry2->addEntry("Artist", 2);
    entry2->addEntry("34", 3);
    ct.addRow(entry2);

    ConsoleTableRow* entry3 = new ConsoleTableRow(4);
    entry3->addEntry("United Kingdom", 0);
    entry3->addEntry("Julia", 1);
    entry3->addEntry("Designer", 2);
    entry3->addEntry("42", 3);
    ct.addRow(entry3);

    ConsoleTableRow* entry4 = new ConsoleTableRow(4);
    entry4->addEntry("United Staates", 0);
    entry4->addEntry("Jo", 1);
    entry4->addEntry("Actor", 2);
    entry4->addEntry("21", 3);
    ct.addRow(entry4);

    // Print all entries
    ct.printTable();

    return 0;
}
