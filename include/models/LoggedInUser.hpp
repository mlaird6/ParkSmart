//---------------------------------------------------------//
//  LoggedInUser.h                                         //   
//  CS3307_stage3                                          //       
//  Created by Jake McLaughlin on 2018-11.                 //       
//  Copyright © 2018 Jake McLaughlin. All rights reserved. //
//---------------------------------------------------------//

#include <string>
#include <vector>

#include "../IAction.h"
#include "../IRole.h"

#ifndef LOGGEDINUSER_H
#define LOGGEDINUSER_H
class LoggedInUser {

    private:
        std::string username;
        int UID;
        std::string license_num;
        bool pregnant;
        bool disability;
        std::string vehicle_type;
        std::vector<IRole> roles;

    public:
        LoggedInUser(std::string new_username, int new_id, std::string new_license_num, int new_pregnant, 
                            int new_disability, std::string new_vehicle_type, int isdriver, int isowner);
        std::vector<IAction*> getActions();
        int getID();
};
#endif
