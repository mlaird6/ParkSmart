/** @file ParkingSession.cpp
 *  @brief Contains information related to an user parking session.
 *
 *  Parking session holds information that can be useful to perform actions like checking which
 *  user is parking in which space, as well as how long they will stay there.
 *  Since parking lot rates may vary and change while an user is already parked, the initial
 *  price rate is saved in each parking session. The price rate and stay time can be later used
 *  to compute how much a user will be paying at the end of a session.
 *  The parking time limit and stay time can be used to check whether a user has gone over the time limit.
 *
 *  @param rate ; price charged per hour set by owner of parking lot
 *  @param parkingSpotID ; unique id used to identify a parking space
 *  @param parkingTimeLimit ; maximum and minimum time a user can stay in a spot
 *  @param stayTime ; time a user will stay in a parking space
 *  @param userID ; unique id used to identify user
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include "../../include/models/ParkingSession.h"

ParkingSession::ParkingSession(double p_rate, int spotID, int timeLimit, int theStayTime, int theUserID){
    rate = p_rate;
    parkingSpotID = spotID;
    parkingTimeLimit = timeLimit;
    stayTime = theStayTime;
    userID = theUserID;
}

/**
 *  @brief return parking lot rate
 *
 *  @param N/A
 *  @return rate - double
 */
double ParkingSession::getRate(){
    return rate;
}

/**
 *  @brief set parking lot rate
 *
 *  @param newRate - double
 *  @return N/A
 */
void ParkingSession::setRate(double newRate){
    rate = newRate;
}

/**
 *  @brief return parking spotID
 *
 *  @param N/A
 *  @return parkingSpotID
 */
int ParkingSession::getSpotID(){
    return parkingSpotID;
}

/**
 *  @brief set parking lot rate
 *
 *  @param newSpotID - int
 *  @return N/A
 */
void ParkingSession::setSpotID(int newSpotID){
    parkingSpotID = newSpotID;
}

/**
 *  @brief return parking time limit
 *
 *  @param N/A
 *  @return parkingTimeLimit
 */
int ParkingSession::getTimeLimit(){
    return parkingTimeLimit;
}

/**
 *  @brief set parking lot rate
 *
 *  @param newTimeLimit - int
 *  @return N/A
 */
void ParkingSession::setTimeLimit(int newTimeLimit){
    parkingTimeLimit = newTimeLimit;
}

/**
 *  @brief return stay time
 *
 *  @param N/A
 *  @return stayTime - int
 */
int ParkingSession::getStayTime(){
    return stayTime;
}

/**
 *  @brief set stay time
 *
 *  @param newStayTime - int
 *  @return N/A
 */
void ParkingSession::setStayTime(int newStayTime){
    stayTime = newStayTime;
}

/**
 *  @brief return user ID
 *
 *  @param N/A
 *  @return userID - int
 */
int ParkingSession::getUserID(){
    return userID;
}

/**
 *  @brief set user ID
 *
 *  @param newUserID
 *  @return N/A
 */
void ParkingSession::setUserID(int newUserID){
    userID = newUserID;
}
