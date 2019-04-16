/** @file ActiveParkingSessions.cpp
 *  @brief Holds information related to all active parking sessions.
 *
 *  Active parking sessions can be retrieved and added.
 *
 *  @param activeSessions; contains all of the current active sessions
 *  @param count; total number of active sessions
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano; primary author
 */

#include "../../include/models/ActiveParkingSessions.h"

ActiveParkingSessions::ActiveParkingSessions(){
    count = 0;
}

/**
 *  @brief retrieved all active parking sessions
 *
 *  retrieved all active parking sessions by accessing all active sessions and pushing them into a vector
 *
 *  @param N/A
 *  @return sessions - a vector of parking sessions
 */
vector<ParkingSession> ActiveParkingSessions::getAllActiveParkingSessions(){
    vector<ParkingSession> sessions;
    for (auto& x: activeSessions) {
      //x.first holds key, x.second holds ParkingSession element
        sessions.push_back(x.second);
    }
    return sessions;
}

/**
 *  @brief check if an active parking session with a spot id already exist
 *
 *  get all active sessions and itterate through them until specified id is found or you reach the end
 *
 *  @param id - the id of the parking session
 *  @return true or false - weather the parking session with that ID was found or not
 */
bool ActiveParkingSessions::checkParkingSession(int id){
    unordered_map<int, ParkingSession>::const_iterator findSession = activeSessions.find(id);
    if(findSession!=activeSessions.end()){
      //active parking session with that ID was found
        return true;
    }else{
      //active parking session with that ID was NOT found
        std::cout << "not active parking session found with that id";
        return false;
    }

}

/**
 *  @brief retrieved a parking session
 *
 *  get all active sessions and itterate through them until specified id is found or you reach the end
 *  return the parking session
 *
 *  @param id - the id of the parking session
 *  @return session - the parking session with the specified ID
 */
ParkingSession ActiveParkingSessions::getParkingSession(int id){
    unordered_map<int, ParkingSession>::const_iterator findSession = activeSessions.find(id);
    ParkingSession session = ParkingSession(0,0,0,0,0);
    if(checkParkingSession(id)){
       session = findSession->second;
        return session;
    }else{
        std::cout << "not active parking session found with that id";
        //return empty parking session
        return session;
    }
}

/**
 *  @brief retrieves specific parking sessions
 *
 *  itterate through the vector of parking sessions and push parking sessions still in use
 *  return the parking sessions
 *
 *  @param parkingSessions - a vector of parking sessions
 *  @return session - the parking session in use
 */
vector<ParkingSession> ActiveParkingSessions::getParkingSessions(vector<int> parkingSessions){
    vector<ParkingSession> sessions;
    for (int i = 0; i < parkingSessions.size(); i++) {
        if(checkParkingSession(parkingSessions[i])){
            sessions.push_back(getParkingSession(parkingSessions[i]));
        }
    }
    return sessions;
}

/**
 *  @brief add an active parking session
 *
 *  given a session, add to active sessions using insert
 *
 *  @param session - a parking session to add
 *  @return N/A
 */
void ActiveParkingSessions::addActiveSession(int id, ParkingSession session){
    activeSessions.insert(make_pair(id, session));
    //insert active session
}

/**
 *  @brief remove an active parking sessions
 *
 *  given a session, remove from active sessions using erase
 *
 *  @param session - a parking session to delete
 *  @return N/A
 */
void ActiveParkingSessions::removeActiveSession(int id, ParkingSession session){
     activeSessions.erase (id);
     //erase active session
}

/**
 *  @brief retrieves total number of active parking sessions
 *
 *  return count, the total number of active parking sessions
 *
 *  @param N/A
 *  @return count - the number of active parking sessions
 */
int ActiveParkingSessions::getCount(){
    return count;
}

/**
 *  @brief used to increase active parking sessions count once a new active session is added
 *
 *  increment the count of parking sessions
 *
 *  @param N/A
 *  @return N/A
 */
void ActiveParkingSessions::increaseCount(){
    count += 1;
}
