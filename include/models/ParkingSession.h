//
//  ParkingSession.h
//  CS3307_stage3
//  Created by Katherine Zambrano on 2018-11.
//  Copyright © 2018 Katherine Zambrano. All rights reserved.
//
#ifndef ParkingSession_h
#define ParkingSession_h
class ParkingSession{
    private:
        double rate;
        int parkingSpotID;
        int parkingTimeLimit;
        int stayTime;
        int userID;
    public:
       ParkingSession(double p_rate, int spotID, int timeLimit, int theStayTime, int theUserID);
        double getRate();
        void setRate(double newRate);
        int getSpotID();
        void setSpotID(int newSpotID);
        int getTimeLimit();
        void setTimeLimit(int newTimeLimit);
        int getStayTime();
        void setStayTime(int newStayTime);
        int getUserID();
        void setUserID(int newUserID);

};

#endif /* ParkingSession_h */
