#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <vector>
#include <ctime>
#include <string>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <utility>

#include "ParkingSpace.h"
#include "SensorBlock.h"
#include "SensorPacket.h"
#include "../include/DatabaseProxy.hpp"

class ParkingLot{
	private:
		std::vector<ParkingSpace> spaces;
		std::vector<SensorBlock> blocks;
		std::map<int, ParkingSpace*> sensorToLot;
		int lotID;
		struct tm openingTime;
		struct tm closingTime;
		std::string name;
		std::string address;
		double parkingRate;
		DatabaseProxy database = database.instance();
		
	public:
		ParkingLot(std::string name, std::string address, int lotID, double parkingRate, tm closingTime, tm openingTime);
		void setOpeningTime(tm);
		tm getOpeningTime();
		void setClosingTime(tm);
		tm getClosingTime();
		void setName(std::string);
		std::string getName();
		void setAddress(std::string);
		std::string getAddress();
		void addSpace(ParkingSpace);
		void removeSpace(int spaceID);
		ParkingSpace getSpace(int spaceID);
		void setRate(double);
		double getRate();
		void setLotID(int);
		int getLotID();
		void update();
		int mapSensorToLot(int, ParkingSpace*);
		void addSensorBlock(SensorBlock);
		int mapSensorToLot(int, int);
		
		
};

#endif