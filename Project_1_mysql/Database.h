#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <mysql++.h>

class Database {
	public:
		Database();
		int Connect(const char* targetDB);
		void displayData();
		void listDB();
		void createDB();
		void deleteDB();
		void quit();

	private:
		mysqlpp::StoreQueryResult sendQuery(mysqlpp::Query query);

		mysqlpp::Connection con;
		const char *server;
		const char *user;
		const char *password;		
		unsigned int port;
		const char *database;
};

#endif //DATABASE_DATABASE_H
