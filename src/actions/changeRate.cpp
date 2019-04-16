#include "../../include/IAction.h"

#ifndef CHANGERATE
#define CHANGERATE
using namespace std;

/** @file changeRate.cpp
 *  @brief change parking lot rate
 *
 *  promp user for lot ID and new lot parking rate
 *	update database with new information
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco; primary author
 *  @author Katherine Zambrano
 *  @bug No know bugs.
 */
class changeRate: public IAction{
	public:
        virtual void perform(int userid, Socket sock){
            // get an instance of the database (singleton)
	    DatabaseProxy db = db.instance();
	    string s = "Enter lot ID:";

	    // send response and receive response (lot ID)
            char *y = new char[s.length() + 1];
            std::strcpy(y, s.c_str());
            sock.send_msg(y);
            int responseID = stoi(sock.receive());

    	    string s2 = "What will be the new parking rate (/hr):";

	    // send request and receive response (new parking rate)
            char *y1 = new char[s2.length() + 1];
            std::strcpy(y1, s2.c_str());
            sock.send_msg(y1);
            int responseRate = stoi(sock.receive());

	    // update the database
	    db.setLotRate(responseID, responseRate);
        }

};
#endif
