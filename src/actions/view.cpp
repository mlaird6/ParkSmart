#include "../../include/IAction.h"
#include "../../include/DatabaseProxy.hpp"

#ifndef VIEW
#define VIEW
using namespace std;

/** @file view.cpp
 *  @brief user can view parking lot
 *
 *  prompt user for lotID
 * 	show spot type, occupancy, and reservation status
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco; primary author
 *  @author Katherine Zambrano
 *  @bug No know bugs.
 */

class view: public IAction{
	public:
		virtual void perform(int userid, Socket sock){
	    // get an instance of the database (singleton)
		    DatabaseProxy db = db.instance();

            sock.send_msg((char *) "Which lot would you like to view:\n");

	    // get and list parking lots from database for user to select from
            vector<vector<string>> lots = db.getParkingLots();
            for(int i = 0; i< lots.size(); i++){
            	string msg = "[" + lots[i][0] + "]" +"\t"+lots[i][1]+"\n";
                char *y = new char[msg.length() + 1];
                std::strcpy(y, msg.c_str());
                sock.send_msg(y);
                delete y;
            }

	    // get response from user for which database to view (lot ID)
            sock.send_msg((char *) "Input:");
            string response = sock.receive();

            // get and list all parking space information from database for selected lot
	    vector<vector<string>> spaces = db.getParkingSpaces(stoi(response));
            for(int i = 0; i< spaces.size(); i++){
            	string msg = "[" + spaces[i][0] + "]" +"\tType: "+spaces[i][1] + "\tOccupied: "+spaces[i][2] + "\tReserved: "+spaces[i][3] + "\n";
            	char *y = new char[msg.length() + 1];
                std::strcpy(y, msg.c_str());
                sock.send_msg(y);
                delete y;
            }

		}

};

#endif
