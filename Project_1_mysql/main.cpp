#include <iostream>
#include <exception>
#include "Database.h"

using namespace std;
using namespace mysqlpp;

int main(int argc, char* argv[])
{
	Database myDB;
	int DBresult;
	DBresult = myDB.Connect("TX");

	if(DBresult)
	{
		cout << "Failed to connect to DB." << endl;
		return 0;
	}

	while(1)
	{
		int option;
		cout << "\nPlease select one of the below options:\n";
		cout << "1. List current DB\n";
		cout << "2. Create a DB\n";
		cout << "3. Delete a DB\n";
		cout << "4. Display Data\n";
		cout << "5. Exit\n";
		cin >> option;

		try { 
			switch(option){
				case 1: myDB.listDB();
						break;
				case 2: myDB.createDB();
						break;
				case 3: myDB.deleteDB();
						break;
				case 4: myDB.displayData();
						break;
				case 5: myDB.quit();
						break;
				default: cout << "Unknown input. Please enter again.\n";
						 break;
			}
		}
		catch(BadQuery err) {
			cerr << "Bad query: " << err.what() << endl;
			return -1;
		}
		catch(const Exception& err) {
			cerr << "Exception error: " << err.what() << endl;
			return -1;
		}
	}
	
	//displayData(con);

	/* close connection */
	return (EXIT_SUCCESS);
}
