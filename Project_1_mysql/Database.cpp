#include <iostream>
#include <exception>
#include "Database.h"
#include "../Project_8_ConsoleTable/ConsoleTable.h"

using namespace mysqlpp;

Database::Database()
{
	con = false;
	server = "192.168.1.126";
	user = "root";
	password = "admin";
	port = 3306;	
}

int Database::Connect(const char* targetDB)
{
	/* Connect to DB */
	database = targetDB;
	if (!con.connect(database, server, user, password, port))
	{
		std::cerr << "Error in connection!"  <<  std::endl;
		return -1;
	}
	else
	{
		std::cout << "Connected to " << database << " successfully." << std::endl;
		return 0;
	}
}

StoreQueryResult Database::sendQuery(Query query)
{
	StoreQueryResult result = query.store();

	/* Send SQL query */
	if (!result) {
		std::cerr << "Failed to send query: "
		     	  << query.error() << std::endl;
	}
	return result;
}

void Database::displayData()
{
	Query myQuery = con.query();
	myQuery << "SELECT * FROM TB_TRADE_TABLE";

	StoreQueryResult res = sendQuery(myQuery);

	if(res)
	{
		// output table contents
		std::cout << "Total number of rows: " << res.num_rows() << std::endl;	
		for (Row::size_type i = 0; i < res.fields().size(); i++)
		{
			std::cout << std::left << std::setw(22) << std::setfill('-') << std::left << '+' << std::left << '+' << std::endl;
			std::cout << std::setfill(' ') << '|' << std::left << std::setw(21)
					  << res.field_name(i)
					  << std::setfill(' ') << '|' << std::endl;
			std::cout << std::left << std::setw(22) << std::setfill('-') << std::left << '+' << std::left << '+' << std::endl;
		}

		StoreQueryResult::const_iterator it;
		for(it = res.begin(); it != res.end(); ++it)
		{
			Row row = *it;
			std::cout << std::setfill(' ') << "|" << std::left << std::setw(21) << row[0] 
				 	  << std::setfill(' ') << "|" << std::endl;
		}
		std::cout << std::left << std::setw(22) << std::setfill('-') << std::left << '+' << std::left << '+' << std::endl;
	}
}

void Database::listDB()
{
	std::cout << "Currently available DB:\n";
	Query myQuery = con.query();
	myQuery << "show databases";
	StoreQueryResult res = sendQuery(myQuery);
	
	if(res) {
		// Printer Header
		std::cout << "Records Found: " << res.size() << std::endl;

		ConsoleTable outputTable(BASIC);
		for(size_t i = 0; i < res.num_fields(); i++)
		{
			outputTable.addColumn(res.field_name(i));
		}

		// Add row contents
		for(size_t i = 0; i < res.num_rows(); i++)
		{
			ConsoleTableRow* entry = new ConsoleTableRow(res.num_fields());
			for(size_t j = 0; j < res.num_fields(); j++)
			{
				std::string field = res.field_name(j);
				entry->addEntry(res[i][field.c_str()],j);
			}
		}
		outputTable.addRow(entry);
		outputTable.printTable();
		/*
		std::cout << std::left << std::setw(22) << std::setfill('-') << std::left << '+' << std::left << '+' << std::endl;
		std::cout << std::setfill(' ') << '|' << std::left << std::setw(21)
			 	  << "Database"
			 	  << std::setfill(' ') << '|' << std::endl;
		std::cout << std::left << std::setw(22) << std::setfill('-') << std::left << '+' << std::left << '+' << std::endl;
		*/
		/*
		StoreQueryResult::const_iterator it;
		for(it = res.begin(); it != res.end(); ++it)
		{
			Row row = *it;
			
			std::cout << std::setfill(' ') << "|" << std::left << std::setw(21) << row[0] 
				 	  << std::setfill(' ') << "|" << std::endl;
		}
		*/
	}
	//std::cout << std::left << std::setw(22) << std::setfill('-') << std::left << '+' << std::left << '+' << std::endl;
}

void Database::createDB()
{
	std::string dbName;
	SimpleResult result;
	std::cout << "Please input the name of DB you want to create: ";
	std::cin >> dbName;

	Query myQuery = con.query();
	myQuery << "CREATE DATABASE " << dbName;
	result = myQuery.execute();
	if(result)
	{
		std::cout << "Database is created successfully." << std::endl;
	}
	else
	{
		std::cout << "Failed to create database." << std::endl;
	}
}

void Database::deleteDB()
{
	std::string dbName;
	SimpleResult result;
	std::cout << "Please enter the name of DB you want to delete: ";
	std::cin >> dbName;

	Query myQuery = con.query();
	myQuery << "DROP DATABASE " << dbName;
	result = myQuery.execute();
	
	if(result)
	{
		std::cout << "Database is deleted successfully." << std::endl;
	}
	else
	{
		std::cout << "Failed to delete database." << std::endl;
	}
}

void Database::quit()
{
	con.disconnect();
	exit(EXIT_SUCCESS);
}
