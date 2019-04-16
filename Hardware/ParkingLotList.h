#ifndef PARKINGLOTLIST_H
#define PARKINGLOTLIST_H

#include <map>
#include <vector>
#include <iterator>
#include <utility>
#include "ParkingLot.h"

class ParkingLotList{
	private:
		std::map<int, ParkingLot> idToLot;
	public:
		ParkingLot getLot(int);
		void addLot(ParkingLot);
};

#endif