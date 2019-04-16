#ifndef PARKINGSPACE_H
#define PARKINGSPACE_H

#include<ctime>
#include <string>

#include "Sensor.h"

class ParkingSpace{
	private:
		bool occupied;
		int spotID;
		std::string type;
		struct tm reservedStart;
		struct tm reservedEnd;
		Sensor sensor;
	public:
		ParkingSpace(int, std::string);
		int getSpotID() const;
		void setSpotID(int);
		bool getOccupied() const;
		void setOccupied(bool);
		std::string getType() const;
		void setType(std::string);
		tm getReservedStart() const;
		void setReservedStart(tm);
		tm getReservedEnd() const;
		void setReservedEnd(tm);
		void reserve(tm);
		
};

#endif