/** @file ParkingLot.cpp
 *  @brief Contains information related to a parking lot.
 *
 *  Each parking lot has an opening and closing time, a rate,
 *  an address, and parking spaces ids which can be set and retrieved through the class.
 *  Parking spaces can be retrieved, added, and removed from a parking lot
 *
 *  @param lotID ; unique id used to identify a parking space
 *  @param parkingRate ; price rate for a parking lot
 *  @param openingTime ; time when parking lot and spaces become available
 *  @param closingTime ; time when parking lot and spaces are not availanle anymore
 *  @param address; location of parking lot
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include "ParkingLot.h"


ParkingLot::ParkingLot(std::string name, std::string address, int lotID, double parkingRate, tm closingTime, tm openingTime){
	this->lotID=lotID;
	this->parkingRate=parkingRate;
	this->openingTime=openingTime;
	this->closingTime=closingTime;
	this->address=address;

}

/**
 * @brief set parking lot opening time
 *
 * @param openingTime - tm struct
 * @return openingTime - tm struct
 */
void ParkingLot::setOpeningTime(tm openingTime){
	this->openingTime=openingTime;
}

/**
 * @brief get parking lot opening time
 *
 * @param N/A
 * @return openingTime - tm struct
 */
tm ParkingLot::getOpeningTime(){
	return openingTime;
}

/**
 * @brief set parking lot closing time
 *
 * @param tm - tm struct
 * @return N/A
 */
void ParkingLot::setClosingTime(tm){
	this->closingTime=closingTime;
}

/**
 * @brief get parking lot closing time
 *
 * @param N/A
 * @return closingTime - tm struct
 */
tm ParkingLot::getClosingTime(){
	return closingTime;
}

/**
 * @brief set parking lot name
 *
 * @param name - string
 * @return N/A
 */
void ParkingLot::setName(std::string name){
	this->name=name;
}

/**
 * @brief get parking lot name
 *
 * @param N/A
 * @return name - string
 */
std::string ParkingLot::getName(){
	return name;
}

/**
 * @brief set parking lot address
 *
 * @param address - string
 * @return N/A
 */
void ParkingLot::setAddress(std::string address){
	this->address=address;
}

/**
 * @brief get parking lot address
 *
 * @param N/A
 * @return address - string
 */
std::string ParkingLot::getAddress(){
	return address;
}

/**
 * @brief add a parking space to parking lot
 *
 * @param  space - ParkingSpace
 * @return N/A
 */
void ParkingLot::addSpace(ParkingSpace space){
	spaces.push_back(space);
}

/**
 * @brief get a space from parking lot
 *
 * @param  spaceID - int
 * @return ParkingSpace
 */
ParkingSpace ParkingLot::getSpace(int spaceID){
	for (int i = 0; i < spaces.size(); i++){
		if (spaces.at(i).getSpotID()==spaceID)
			return spaces.at(i);
	}
}

/**
 * @brief remove a space from parking lot
 *
 * @param spaceID
 * @return N/A
 */
void ParkingLot::removeSpace(int spaceID){
	std::vector<ParkingSpace>::iterator ptr;
	ptr=spaces.begin();
	for (int i =0; i<spaces.size(); i++){
		if (ptr->getSpotID()==spaceID)
			spaces.erase(ptr);
		ptr++;
	}
}

/**
 * @brief set rate of parking lot
 *
 * @param parkingRate - double
 * @return parkingRate
 */
void ParkingLot::setRate(double parkingRate){
	this->parkingRate=parkingRate;
}

/**
 * @brief get rate of parking lot
 *
 * @param N/A
 * @return parkingRate - double
 */
double ParkingLot::getRate(){
	return parkingRate;
}

/**
 * @brief set parking lot id
 *
 * @param lotID - int
 * @return N/A
 */
void ParkingLot::setLotID(int lotID){
	this->lotID=lotID;
}

/**
 * @brief get parking lot id
 *
 * @param N/A
 * @return lotID - int
 */
int ParkingLot::getLotID(){
	return lotID;
}

/**
 * @brief updates parking lot and its spaces
 *
 * @param N/A
 * @return N/A
 */
void ParkingLot::update(){
	std::map<int,ParkingSpace*>::iterator ptr;
	for (int i=0; i<blocks.size();i++){
		blocks.at(i).update();
		SensorPacket packet=blocks.at(i).getPacket();
		for(int j=0; j<packet.getNumberOfSensors();j++){
			ptr=sensorToLot.find(packet.sensorID[j]);
			ptr->second->setOccupied(packet.sensorID[j]);
		}
	}

	for(int i = 0; i < spaces.size(); i++){
		if(spaces[i].getOccupied()){
			database.setSpaceOccupied(spaces[i].getSpotID(), 1);
		}else{
			database.setSpaceOccupied(spaces[i].getSpotID(), 0);
		}
	}

}

/**
 * @brief inserts sensors in parking spaces
 * @param sensorID - int
 * @param space - ParkingSpace
 * @return N/A
 */
int ParkingLot::mapSensorToLot(int sensorID, ParkingSpace* space){
	//TODO add duplicate error handiling
	sensorToLot.insert(std::make_pair(sensorID,space));
}

/**
 * @brief inserts sensors in parking spaces
 * @param sensorID - int
 * @param spaceID - ParkingSpace
 * @return 0 or 1 based on success
 */
int ParkingLot::mapSensorToLot(int sensorID, int spaceID){
	//TODO add duplicate error handiling
	for(int i=0; i<spaces.size(); i++){
		if(spaces[i].getSpotID()==spaceID){
			this->mapSensorToLot(sensorID,&spaces[i]);
			return 0;
		}
	}
	return 1;
}

/**
 * @brief adds sensor block
 * @param block ; sensor block
 * @return N/A
 */
void ParkingLot::addSensorBlock(SensorBlock block){
	blocks.push_back(block);
}
