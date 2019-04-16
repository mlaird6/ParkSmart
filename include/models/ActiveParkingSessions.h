//
//  ActiveParkingSessions.h
//  CS3307_stage3
//  Created by Katherine Zambrano on 2018-11.
//  Copyright © 2018 Katherine Zambrano. All rights reserved.
//
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

#include "../../include/models/ParkingSession.h"

#ifndef ActiveParkingSessions_h
#define ActiveParkingSessions_h
using namespace std;
class ActiveParkingSessions{
    private:
        unordered_map<int,ParkingSession> activeSessions;
        int count;
        void increaseCount();
        bool checkParkingSession(int id);//checks if session exists
    public:
        ActiveParkingSessions();
        vector<ParkingSession> getAllActiveParkingSessions();
        ParkingSession getParkingSession(int id);
        vector<ParkingSession >getParkingSessions(vector<int> parkingSessions);
        void addActiveSession(int id, ParkingSession session);
        void removeActiveSession(int id, ParkingSession session);
        int getCount();
    
};

#endif /* ActiveParkingSessions_h */
