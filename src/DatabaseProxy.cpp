/** @file DatabaseProxy.cpp
 *  @brief connect to mysql database
 *
 *  A Socket class can be used to create socket objects which can send and receive messages.
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */
#include "../include/DatabaseProxy.hpp"

using namespace std;

DatabaseProxy& DatabaseProxy::instance(){
    static DatabaseProxy instance;
    return instance;
}

/**
 *  @brief connect to mysql database
 *
 *  use the IP, port, username and password to connect to mysql
 *  connect to ParkSmart database
 *
 *  @bug No know bugs.
 *  @param - none
 *  @return - none
 */
DatabaseProxy::DatabaseProxy(){
	/* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("127.0.0.1:3306", "username", "password");
    /* Connect to the MySQL test database */
    con->setSchema("ParkSmart");
}

/**
 *  @brief access database to create user
 *
 *  using username, password, firstname, lastname, licence place number, pregnancy status, disability status, vehicle type, driver status, and owner status
 *  run a select query to see if someone with that username already exists
 *  userID is set to auto increment
 *  if user doesnt exist, run a query to insert these values into the user table
 *
 *  @bug No know bugs.
 *  @param username is the chosen username for the user being added
 *  @param password is the chosen password for the user being added
 *  @param fname is the chosen first name for the user being added
 *  @param lname is the chosen last name for the user being added
 *  @param license_num is the chosen license plate number for the user
 *  @param pregnant is the pregnancy status of the user being added
 *  @param disability is the disability status of the user being added
 *  @param vehichle_type is the type of vehicle of the user being added
 *  @param driver is the driver status of the user being added
 *  @param lot_owner is the lot owner status of the user being added ie weather or not they own a lot
 *  @return -1 for failure or the database return value
 */
int DatabaseProxy::createUser(string username, string password, string fname, string lname, string license_num, int pregnant, int disability, string vehicle_type, int driver, int lot_owner){
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res;
	try{
		string query = "SELECT * FROM user WHERE username = '" + username + "' OR license_num = '" + license_num + "'";
        res = stmt->executeQuery(query);
        if (res->next()){
            cout << "A user with that username or license plate already exists (from USER)." << endl;
            return -1;
            //failure, user already exists
        }
        else {
            string query = "INSERT INTO user (id, username, password, fname, lname, vehicle_type , license_num, pregnant, disability, driver, lot_owner) VALUES (0, '"
            + username + "', '" + password + "', '" + fname + "', '" + lname + "', '" + vehicle_type + "', '" + license_num + "', " + to_string(pregnant) + ", " + to_string(disability) + ", " + to_string(driver) + ", "+ to_string(lot_owner) + ")" ;
            res = stmt->executeQuery(query);
            //insert into database
            if(res){
            	//do nothing
            }else{
                query = "SELECT id FROM user WHERE username = " + username;
                res = stmt->executeQuery(query);
                return res->getInt(1);
            }
            //success, user added in to database
        }
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to get user
 *
 *  using username and password to run a select query to see the person exists and the username and password is correct
 *  add all information from the database to a vector of strings
 *
 *  @bug No know bugs.
 *  @param username is the chosen username for the user being added
 *  @param password is the chosen password for the user being added
 *  @return user vector
 */
vector<string> DatabaseProxy::getUser(string username, string password){
	vector<string> user;
	sql::Statement *stmt = con->createStatement();
	sql::ResultSet *res;
	try{
		string query = "SELECT * FROM user WHERE username = '" + username + "' AND password = '" + password + "'";
        res = stmt->executeQuery(query);
        if (!res->next()){
            cout << "A invalid username or password." << endl;
            return user;
        }
        else{
        	user.push_back(res->getString("username"));
        	user.push_back(res->getString("id"));
        	user.push_back(res->getString("license_num"));
        	user.push_back(res->getString("pregnant"));
        	user.push_back(res->getString("disability"));
        	user.push_back(res->getString("vehicle_type"));
        	user.push_back(res->getString("driver"));
        	user.push_back(res->getString("lot_owner"));
        	return user;
        }
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to get parkinglot
 *
 *  use lotID to perform a select query that returns the lot with the specified ID
 *  add all information from the database to a vector of strings
 *
 *  @bug No know bugs.
 *  @param lotID - the lotID of the lot to return, the primary key of ParkingLot table
 *  @return data vector
 */
vector<string> DatabaseProxy::getParkingLot(int lotid){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    vector<string> data;
    try{
        string query = "SELECT * FROM parkingLot WHERE id = "+ to_string(lotid);
        res = stmt->executeQuery(query);
        res->next();
        data.push_back(res->getString("id"));
        data.push_back(res->getString("address"));
        data.push_back(res->getString("rate"));
        data.push_back(res->getString("open_time"));
        data.push_back(res->getString("close_time"));
        data.push_back(res->getString("lot_name"));
        return data;
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to get all lots with IDs
 *
 *  run SELECT query to return all lots from the database, showing the lot ID and the lot name
 *  put id and lot name into a vector of vectors of strings
 *
 *  @bug No know bugs.
 *  @param no paramerts for getParkingLots()
 *  @return data , a vector of vectors
 */
vector<vector<string>> DatabaseProxy::getParkingLots(){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    vector<vector<string>> data;
    try{
        string query = "SELECT id, lot_name FROM parkingLot";
        res = stmt->executeQuery(query);
        int i = 0;
        while(res->next()){
            vector<string> meta;
            meta.push_back(res->getString("id"));
            meta.push_back(res->getString("lot_name"));
            data.push_back(meta);
            i++;
        }
        return data;
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to get parking space
 *
 *  run SELECT query to return all spaces from the lot with the specified ID
 *  put id, parking space type, space occupancy, and spot reservation status into a vector of vectors of strings
 *  return this vector of vector of strings containing all spaces and data
 *
 *  @bug No know bugs.
 *  @param lotid - the id of the lot containing parking spaces (primary key for database)
 *  @return data , a vector of vectors
 */
vector<vector<string>> DatabaseProxy::getParkingSpaces(int lotid){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    vector<vector<string>> data;
    try{
        string query = "SELECT * FROM parkingSpace WHERE lotid = " + to_string(lotid);
        res = stmt->executeQuery(query);
        int i = 0;
        while(res->next()){
            vector<string> meta;
            meta.push_back(res->getString("id"));
            meta.push_back(res->getString("lotid"));
            meta.push_back(res->getString("type"));
            meta.push_back(res->getString("occupied"));
            meta.push_back(res->getString("reserved"));
            data.push_back(meta);
            i++;
        }
        return data;

    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to set a parking space as occupied
 *
 *  run UPDATE query update parkingspace table, updating the occupancy status of the specified parking space
 *
 *  @bug No know bugs.
 *  @param spaceid - the id of the space to be set occupied/not (primary key for database)
 *  @param occupied - boolean where 1 = occupied, 0 = unoccupied
 *  @return data , a vector of vectors
 */
void DatabaseProxy::setSpaceOccupied(int spaceid, int occupied){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    vector<string> data;
    try{
        string query = "UPDATE parkingSpace SET occupied = " + to_string(occupied) + " WHERE id = "+ to_string(spaceid);
        res = stmt->executeQuery(query);
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to set a parking space as reserved
 *
 *  run UPDATE query update parkingspace table, updating the reserved status of the specified parking space
 *
 *  @bug No know bugs.
 *  @param spaceid - the id of the space to be set occupied/not (primary key for database)
 *  @param reserved - boolean where 1 = reserved, 0 = not reserved
 *  @return no return value
 */
void DatabaseProxy::setSpaceReserved(int spaceid, int reserved){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    try{
        string query = "UPDATE parkingSpace SET reserved = " + to_string(reserved) + " WHERE id = "+ to_string(spaceid);
        res = stmt->executeQuery(query);
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to set parking lot opening and closing times
 *
 *  run UPDATE query update parkinglot table, updating open and close time of the specified parking space using the primary key, lotid
 *
 *  @bug No know bugs.
 *  @param lotid - the id of the lot to change the time (primary key for database)
 *  @param opentime - opening time for parking lot
 *  @param closetime - closing time for parking lot
 *  @return no return value
 */
void DatabaseProxy::setLotTime(int lotid, string opentime, string closetime){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    try{
        string query = "UPDATE parkingLot SET open_time = '" + opentime + "', close_time = '" + closetime + "' WHERE id = "+to_string(lotid);
        res = stmt->executeQuery(query);
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to set parking lot rate
 *
 *  run UPDATE query update parkinglot table, updating open and close time of the specified parking lot using the primary key, lotid
 *
 *  @bug No know bugs.
 *  @param lotid - the id of the lot (primary key for database)
 *  @param rate - the new rate for the parking lot
 *  @return no return value
 */
void DatabaseProxy::setLotRate(int lotid, int rate){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    try{
        string query = "UPDATE parkingLot SET rate = '" + to_string(rate) + "' WHERE id = "+to_string(lotid);
        res = stmt->executeQuery(query);
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to set parking lot name
 *
 *  run UPDATE query update parkinglot table, updating name of the specified parking lot using the primary key, lotid
 *
 *  @bug No know bugs.
 *  @param lotid - the id of the lot (primary key for database)
 *  @param name - the new name for the parking lot
 *  @return no return value
 */
void DatabaseProxy::setLotName(int lotid, string name){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    try{
        string query = "UPDATE parkingLot SET lot_name = '" + name + "' WHERE id = "+to_string(lotid);
        res = stmt->executeQuery(query);
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to set parking lot address
 *
 *  run UPDATE query update parkinglot table, updating address of the specified parking lot using the primary key, lotid
 *
 *  @bug No know bugs.
 *  @param lotid - the id of the lot (primary key for database)
 *  @param addy - the address for the parking lot
 *  @return no return value
 */
void DatabaseProxy::setLotAddress(int lotid, string addy){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    try{
        string query = "UPDATE parkingLot SET address = '" + addy + "' WHERE id = "+to_string(lotid);
        res = stmt->executeQuery(query);
    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}

/**
 *  @brief access database to access parking space
 *
 *  run SELECT query access results from parkingSpace table, returning the parking space specified by the spaceID and the parkinglot matches the parkinglot ID'
 *  push the occupied and reserved status into a vector to return
 *
 *  @bug No know bugs.
 *  @param lotid - the id of the lot (primary key for database)
 *  @param spotid - the id of the parking spot of the specified lot
 *  @return meta - a vector that holds the parking space information
 */
vector<string> DatabaseProxy::getSpace(int lotid, int spotid){
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res;
    try{
        string query = "SELECT * FROM parkingSpace WHERE lotid = "+to_string(lotid)+" AND id ="+to_string(spotid);
        res = stmt->executeQuery(query);
        vector<string> meta;
        res->next();
        meta.push_back(res->getString("occupied"));
        meta.push_back(res->getString("reserved"));
        return meta;

    }
    catch (sql::SQLException &e) {
        cout << "Exception caught: no query returned" << endl;
    }
}
