//---------------------------------------------------------//
//  AuthenticationServer.h								   //	
//  CS3307_stage3										   //		
//  Created by Jake McLaughlin on 2018-11.				   //		
//  Copyright © 2018 Jake McLaughlin. All rights reserved. //
//---------------------------------------------------------//

#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#ifndef AUTHSERVER_H
#define AUTHSERVER_H
class AuthenticationServer{
	public:
		AuthenticationServer();
		bool AuthenticateUsername(std::string username);
		bool AuthenticatePassword(std::string password);
		bool AuthenticateLicense(std::string license_num);
};
#endif
