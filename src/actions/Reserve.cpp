#include "../../include/IAction.h"
#include "../../include/DatabaseProxy.hpp"

#ifndef RESERVE
#define RESERVE
using namespace std;

/** @file reserve.cpp
 *  @brief reserving a parking space
 *
 *  prompt user for lot ID and spot to reserve
 *	if spot is already occupied or already reserved, inform user
 *	else, update database
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; co-author
 *  @author Nicholas Tocco; co-author
 *  @author Katherine Zambrano; co-author
 *  @bug No know bugs.
 */
class Reserve: public IAction{
	public:
		virtual void perform(int userid, Socket sock){
            //Create database instace
			DatabaseProxy db = db.instance();
            //get parking lot id
            sock.send_msg((char *) "Which lot do you want to access: ");
            int lot = stoi(sock.receive());
            //get parking spaces using lot is
            vector<vector<string>> spaces = db.getParkingSpaces(lot);
            //get parking space id
            sock.send_msg((char *) "Which parking space do you want to reserve: ");
            //cast response and store space id
            int space = stoi(sock.receive());
            //Look for space id in list of parking spaces
            vector<string> selected = db.getSpace(lot, space);
            if(selected[0] == "1"){//occupied
                sock.send_msg((char *) "Spot is already occupied.\n");
            }
            else if(selected[1] == "1"){//reserved
                sock.send_msg((char *) "Spot is already reserved.\n");
            }
            else{
                db.setSpaceReserved(space,1);
            }
		}
};
#endif
