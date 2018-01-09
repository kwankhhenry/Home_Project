#include <iostream>
#include <exception>
#include <mysql++.h>

using namespace std;
using namespace mysqlpp;

int main(int argc, char* argv[])
{
	const char *server = "192.168.1.126";
	const char *user = "root";
	const char *password = "admin";
	const char *database = "TX";
	const unsigned int port = 3306;
	
	Connection con(false);

	/* Connect to DB */
	if (!con.connect(database, server, user, password, port))
	{
		cerr << "Error in connection!"  <<  endl;
		return -1;
	}

	Query query = con.query();
	query << "SELECT * FROM TB_TRADE_TABLE";
	
	StoreQueryResult res = query.store();

	/* Send SQL query */
	if (!res) {
		cerr << "Failed to send query: "
		     << query.error() << endl;
		return -1;
	}
	else
	{
	/* output table contents */
		Row row;
		Row::size_type i;
		/*
		for (i = 0; row = res.at(0); ++i)
		{
			cout << "Total number of rows: " << res[0]["ROWS_READ"];
		}
		*/
		for (i = 0; i < res.num_rows(); i++)
		{
			cout 
			<< "Trade_Key: " << res[i]["ID"] 
			<< " - Name: " << res[i]["NAMES"] 
			<< endl;
		}
	}

	/* close connection */
	return 0;
}
