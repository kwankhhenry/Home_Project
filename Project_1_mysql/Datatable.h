#ifndef DATATABLE_DATATABLE_H
#define DATATABLE_DATATABLE_H

#include <mysql++.h>
#include "Database.h"

class Datatable : public Database {
	public:
		Datatable();
		void displayTable();
		std::string checkFieldType(mysqlpp::StoreQueryResult res, int fieldIDX);
	
	private:
		mysqlpp::Connection con;
		mysqlpp::StoreQueryResult res;
};

#endif //DATATABLE_DATATABLE_H
