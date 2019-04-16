//---------------------------------------------------------//
//  WebServer.hpp                                          //   
//  CS3307_stage3                                          //       
//  Created by Jake McLaughlin on 2018-11.                 //       
//  Copyright © 2018 Jake McLaughlin. All rights reserved. //
//---------------------------------------------------------//

#include <iostream>
#include <string>
#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>

#include <vector>
#include <ctime>
#include <string>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <map>
#include <utility>
#include <sstream>

#include "../../Hardware/ParkingLot.h"
#include "../models/LoggedInUser.hpp"
#include "../Threads.hpp"
#include "../servers/AuthenticationServer.hpp"
#include "../models/Socket.hpp"
#include "../DatabaseProxy.hpp"

#define PORT_NO 7999
//#define IP_ADDRESS "10.170.90.191"
#define BUFFER_LEN 2048

void *handle_client(void *arg);
LoggedInUser* register_menu(Socket socket, AuthenticationServer auth);
LoggedInUser* login_menu(Socket socket, AuthenticationServer auth);
LoggedInUser *create_user(std::string username, std::string password,std::string fname,std::string lname, std::string license_num, 
							int pregnant, int disability, std::string vehicle_type, int driver, int lot_owner);
LoggedInUser *login(std::string username, std::string password);
void user_menu(Socket socket, LoggedInUser* user);
std::string getIPAddress ();
