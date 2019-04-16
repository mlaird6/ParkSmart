#include "../../include/IAction.h"

#ifndef CHANGELOTADDY
#define CHANGELOTADDY
using namespace std;

/** @file changeLotAddress.cpp
 *  @brief change parking lot address
 *
 *  promp user for lot ID and lot address
 *	update database with new information
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco; primary author
 *  @author Katherine Zambrano
 *  @bug No know bugs.
 */
class changeLotAddress: public IAction{
	public:
		/**
		 *  @brief connect to mysql database
		 *
		 *  promp user for lot ID and lot address
		 *	update database with new information
		 *
		 *  @bug No know bugs.
		 *  @param userid - the userID of the lotowner chaning the lotowner
		 *  @param sock - socket
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

    	    string s2 = "Enter new address:";

	    // sending request and receiving response from user (new address)
            char *y1 = new char[s2.length() + 1];
            std::strcpy(y1, s2.c_str());
            sock.send_msg(y1);
            string address = sock.receive();
            address = address.substr(0, address.length() - 2);

	    // update the database
	    db.setLotAddress(responseID, address);
        }

};
#endif
