/** @file ParkingSpace.cpp
 *  @brief Contains information associated to a parking space.
 *
 *  Parking space holds information that is useful when setting
 *  and retrieving occupancy and reservation status, end and start time of reservation, and type of space.
 *
 *  @param spotID ; unique id used to identify a parking space
 *  @param type ; type can be a regular, for people with disabilities, or pregnant women;
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include "ParkingSpace.h"

/**
 *  @brief Create a new parking space object using spotID, sensor, and type
 *  @param N/A
 *  @return - spotID
 */
ParkingSpace::ParkingSpace(int spotID, std::string type){
    this->spotID=spotID;
    this->type=type;
    occupied=false;
}

/**
 *  @brief return spot id as an integer
 *  @param N/A
 *  @return - spotID
 */
int ParkingSpace::getSpotID() const{
    return spotID;
}

/**
 *  @brief set spot id
 *  @param spotID - the spotid you would like to set
 *  @return N/A
 */
void ParkingSpace::setSpotID(int spotID){
    this->spotID=spotID;
}

/**
 *  @brief get occupation status
 *  @param N/A
 *  @return occupied - a boolean status off occupancy
 */
bool ParkingSpace::getOccupied() const{
    return occupied;
}

/**
 *  @brief set space occupancy
 *  @param occupied - the booean status of occupancy
 *  @return N/A
 */
void ParkingSpace::setOccupied(bool occupied){
    this->occupied=occupied;
}

/**
 *  @brief return space type as a string
 *  @param N/A
 *  @return type - the string type of the parking space
 */
std::string ParkingSpace::getType() const{
    return type;
}

/**
 *  @brief set parking space type
 *  @param type - the type of parking space to set
 *  @return N/A
 */
void ParkingSpace::setType(std::string type){
    this->type=type;
}

/**
 *  @brief get the start time of the reservation
 *  @param N/A
 *  @return reservedStart - the reservation start time
 */
tm ParkingSpace::getReservedStart() const{
    return reservedStart;
}

/**
 *  @brief set reserved start time using a tm struct
 *  @param reservedStart - the start time for the parking spot reservation
 *  @return N/A
 */
void ParkingSpace::setReservedStart(tm reservedStart){
    this->reservedStart=reservedStart;
}

/**
 *  @brief return reserved end time as a tm struct
 *  @param N/A
 *  @return reservedEnd - the end time of the parking space reservation
 */
tm ParkingSpace::getReservedEnd() const{
    return reservedEnd;
}

/**
 *  @brief set reserved end time using a struct
 *  @param reservedEnd the end time of the parking space reservation
 *  @return N/A
 */
void ParkingSpace::setReservedEnd(tm reservedEnd){
    this->reservedEnd=reservedEnd;
}

/**
 *  @brief reseve parking space using tm struct
 *  @param reservedEnd the end time of the parking space reservation
 *  @return N/A
 */
void ParkingSpace::reserve(tm reservedEnd){
    time_t TheTime;
    time(&TheTime);
    reservedStart=*(localtime(&TheTime));
    this->reservedEnd=reservedEnd;
    occupied=true;
    //user suff
    //this->reserveID=reserveID;
    
}
