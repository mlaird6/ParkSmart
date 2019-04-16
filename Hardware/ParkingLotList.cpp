/** @file ParkingLotList.cpp
 *  @brief List of Parking lots
 *
 *	get and add lots by the lot and lotID
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include "ParkingLotList.h"

/**
 * @brief get parking lot by lot ID
 *
 * @param lotID ; ID of lot to access
 * @return parkingLot ; parking lot identified by lotID
 */
ParkingLot ParkingLotList::getLot(int lotID){
	return (idToLot.find(lotID)->second);
}

/**
 * @brief add parking lot ParkingLot object
 *
 * @param lot ; Parking lot to add
 * @return N/A
 */
void ParkingLotList::addLot(ParkingLot lot){
	idToLot.insert(std::make_pair(lot.getLotID(),lot));

}
