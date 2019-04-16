#include "../../include/IAction.h"
#include <string>
#include <cstring>

using namespace std;

/** @file changeTime.cpp
 *  @brief change parking lot opening and closing time
 *
 *  promp user for lot ID, new opeing time, and new closing time
 *	update database with new information
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco; primary author
 *  @author Katherine Zambrano
 *  @bug No know bugs.
 */
class changeTime: public IAction{
    public:
        virtual void perform(int userid, Socket sock){

	    // getting an instance of the db (singleton)
	    DatabaseProxy db = db.instance();
            string question = "For which lot would you like to change the time:";

	    // send request and receive respone (lot ID)
            char *y = new char[question.length() + 1];
            std::strcpy(y, question.c_str());
            sock.send_msg(y);
            int responseID = stoi(sock.receive());

    	    string q2 = "What is the new opening time (xx:xx):";

	    // send request and receive response (new opening time)
            char *y1 = new char[q2.length() + 1];
            std::strcpy(y1, q2.c_str());
            sock.send_msg(y1);
            string responseOTime = sock.receive();
            responseOTime = responseOTime.substr(0, responseOTime.length() - 2);

	    string q3 = "What is the new closing time (xx:xx):";

	    // send request and receive response (new closing time)
            char *y2 = new char[q3.length() + 1];
            std::strcpy(y2, q3.c_str());
            sock.send_msg(y2);
            string responseCTime = sock.receive();
            responseCTime = responseCTime.substr(0, responseCTime.length() - 2);

	    // update the database
            db.setLotTime(responseID, responseOTime, responseCTime);


        }
};
