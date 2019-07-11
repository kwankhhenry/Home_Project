#include <iostream>
#include "Datatable.h"
#include "../Project_8_ConsoleTable/ConsoleTable.h"

Datatable::Datatable()
{
	Database DB;
	std::cout << "Datatable constructor" << std::endl;
}

void Datatable::displayTable()
{
	std::string DBTable;
	std::cout << "Select the table to be displayed: ";
	std::cin >> DBTable;

	con = getConnection();
	mysqlpp::Query myQuery = con.query();
	myQuery << "SELECT * FROM " << DBTable;

	res = sendQuery(myQuery);

	if(res)
	{
		// Print row number
		std::cout << "Rows Found: " << res.size() << std::endl;

		// Add Header
		ConsoleTable outputTable(BASIC);
		for(size_t i = 0; i < res.num_fields(); i++) 
		{
			outputTable.addColumn(res.field_name(i));
		}

		// Add field type
		ConsoleTableRow* header = new ConsoleTableRow(res.num_fields());
		for(size_t i = 0; i < res.num_fields(); i++) 
		{
			header->addEntry(checkFieldType(res, i),i);
		}
		outputTable.addRow(header);

		// Add row contents
		for(size_t i = 0; i < res.num_rows(); i++)
		{
			ConsoleTableRow* entry = new ConsoleTableRow(res.num_fields());
			for(size_t j = 0; j < res.num_fields(); j++)
			{
				std::string field = res.field_name(j);

				//checkFieldType(res, j);	
				std::string field_content = static_cast<std::string>(res[i][field.c_str()]);
				entry->addEntry(field_content,j);
			}
			outputTable.addRow(entry);
		}
		outputTable.printTable();
	}
}

std::string Datatable::checkFieldType(mysqlpp::StoreQueryResult res, int fieldIDX)
{
	mysqlpp::FieldTypes::value_type ft = res.field_type(int(fieldIDX));
	std::ostringstream os;
	os << ft.sql_name() << " (" << ft.id() << ")";
	//std::cout << os.str() << std::endl;

	if(ft == typeid(std::string)) {
		//std::cout << "Type is: STRING" << std::endl;
		return "STRING";
	}
	else if(ft == typeid(int)) {
		//std::cout << "Type is: INT" << std::endl;
		return "INT";
	}
	else if(ft == typeid(float)) {
		//std::cout << "Type is: FLOAT" << std::endl;
		return "FLOAT";
	}
	else if(ft == typeid(double)) {
		//std::cout << "Type is: DOUBLE" << std::endl;
		return "DOUBLE";
	}
	else if(ft == typeid(mysqlpp::sql_date)) {
		//std::cout << "Type is: DATE" << std::endl;
		return "DATE";
	}
	else if(ft == typeid(mysqlpp::sql_time)) {
		//std::cout << "Type is: TIME" << std::endl;
		return "TIME";
	}
	else if(ft == typeid(mysqlpp::sql_timestamp)) {
		//std::cout << "Type is: TIMESTAMP" << std::endl;
		return "TIMESTAMP";
	}
	else if(ft == typeid(mysqlpp::sql_datetime)) {
		//std::cout << "Type is: DATETIME" << std::endl;
		return "DATETIME";
	}
	else if(ft == typeid(mysqlpp::Null<mysqlpp::String>)) {
		std::cout << "SQL type of 'description' field resembles a nullable variant of the C++ string type." << std::endl;
		return "N/A";
	}
	else {
		std::cout << "Unknown field type: " << res.field_type(int(fieldIDX)).name() << std::endl;
		return "N/A";
	}
}
