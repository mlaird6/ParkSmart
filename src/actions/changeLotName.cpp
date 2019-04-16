#include "../../include/IAction.h"

#ifndef CHANGELOTNAME
#define CHANGELOTNAME
using namespace std;
/** @file changeLotName.cpp
 *  @brief change parking lot name
 *
 *  promp user for lot ID and lot name
 *	update database with new information
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco; primary author
 *  @author Katherine Zambrano
 *
 *  @bug No know bugs.
 */
class changeLotName: public IAction{
	public:
		/**
		 *  @brief change the name of a parking lot
		 *
		 *  promp user for lot ID and lot name
		 *	update database with new information
		 *
		 *  @bug No know bugs.
		 *  @param userID userID of the owner of the lot
		 *  @param sock socket
		 *  @return N/A
		 */
        virtual void perform(int userid, Socket sock){
	    // get an instance of the database (singleton)
	    DatabaseProxy db = db.instance();
	    string s = "Enter lot ID:";

	    // sending request and receiving response from user (lot ID)
            char *y = new char[s.length() + 1];
            std::strcpy(y, s.c_str());
            sock.send_msg(y);
            int responseID = stoi(sock.receive());

    	    string s2 = "Enter new name:";

	    // sending request and receiving response from user (new lot name)
            char *y1 = new char[s2.length() + 1];
            std::strcpy(y1, s2.c_str());
            sock.send_msg(y1);
            string name = sock.receive();
            name = name.substr(0, name.length() - 2);

	    // update the database
	    db.setLotName(responseID, name);
        }
};
#endif
