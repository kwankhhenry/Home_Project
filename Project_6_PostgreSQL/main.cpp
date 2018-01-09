#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]){
	try{
		connection C("dbname = TX user = postgres password = john771160 \ 
				hostaddr = 192.168.1.126 port = 5432");

		if(C.is_open()){
			cout << "Opened database successfully: " << C.dbname() << endl;
		}
		else {
			cout << "Cannot open database" << endl;
			return 1;
		}
		C.disconnect();
	} catch (const std::exception &e){
		cerr << e.what() << endl;
		return 1;
	}

}
