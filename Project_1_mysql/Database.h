#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <mysql++.h>

class Database {
	public:
		Database();
		int connectDB();
		int connectDB(const char* targetDB);
		void listDB();
		void createDB();
		void deleteDB();
		void quit();
		void listTable();
		mysqlpp::Connection getConnection();
		mysqlpp::StoreQueryResult sendQuery(mysqlpp::Query query);

	private:
		mysqlpp::Connection con;
		const char *server;
		const char *user;
		const char *password;		
		unsigned int port;
		const char *database;
};

#endif //DATABASE_DATABASE_H
