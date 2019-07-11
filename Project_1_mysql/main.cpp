#include <iostream>
#include <exception>
#include "Datatable.h"

using namespace std;

int main(int argc, char* argv[])
{
	Datatable myDB;

	while(1)
	{
		int option;
		cout << "\nPlease select one of the below options:\n";
		cout << "1. List current DB\n";
		cout << "2. Connect to DB\n";
		cout << "3. Create a DB\n";
		cout << "4. Delete a DB\n";
		cout << "5. List Table\n";
		cout << "6. Display Table data\n";
		cout << "7. Exit\n";
		cin >> option;

		try { 
			switch(option){
				case 1: myDB.listDB();
						break;
				case 2: myDB.connectDB();
						break;
				case 3: myDB.createDB();
						break;
				case 4: myDB.deleteDB();
						break;
				case 5: myDB.listTable();
						break;
				case 6: myDB.displayTable();
						break;
				case 7: myDB.quit();
						break;
				default: cout << "Unknown input. Please enter again.\n";
						 break;
			}
		}
		catch(mysqlpp::BadQuery err) {
			cerr << "Bad query: " << err.what() << endl;
			return -1;
		}
		catch(const mysqlpp::Exception& err) {
			cerr << "Exception error: " << err.what() << endl;
			return -1;
		}
	}
	
	/* close connection */
	return (EXIT_SUCCESS);
}
