#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"


#include <vector>

using namespace std;

#ifndef DATABASEPROXY
#define DATABASEPROXY
class DatabaseProxy {
	private:
		sql::Driver *driver;
	    sql::Connection *con;
	    DatabaseProxy();
	public:
		static DatabaseProxy& instance();
		int createUser(string, string, string, string, string, int, int, string, int, int);
		vector<string> getUser(string username, string password);
		vector<string> getParkingLot(int);
		vector<vector<string>> getParkingLots();
		vector<vector<string>> getParkingSpaces(int);
		vector<string> getSpace(int, int);
		void setSpaceOccupied(int, int);
		void setSpaceReserved(int, int);
		void setLotTime(int, string, string);
		void setLotRate(int, int);
		void setLotName(int, string);
		void setLotAddress(int, string);
};
#endif
