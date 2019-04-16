#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <vector>
#include <ctime>
#include <string>

#include "ParkingSpace.h"

class ParkingLot{
	private:
		std::vector<ParkingSpace> spaces;
		int lotID;
		struct tm openingTime;
		struct tm closingTime;
		std::string name;
		std::string address;
		double parkingRate;
		
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
		ParkingSpace getSpace(int spaceID);
		void removeSpace(int spaceID);
		void setRate(double);
		double getRate();
		void setLotID(int);
		int getLotID();
		
};

#endif