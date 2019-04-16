/** @file SensorBlock.cpp
 *  @brief Contains information associated to a block of sensors
 *
 *  Handles the data transfer from a device containing sensors to the pi.
 *
 *  @param numberOfSensors ;
 *  @param blockAddress ; address of slave device
 *  @param packet ; holds the data to be transfered
 *
 *  @author Melina Laird
 *  @author Mike Levis ; primary author
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */
#include "SensorBlock.h"
/** @brief initialize a sensor block
 *  @param numberOfSensor
 *  @param blockAddress
 *  @return N/A
 */
SensorBlock::SensorBlock(int numberOfSensors, int blockAddress){
	
	this->numberOfSensors=numberOfSensors;
	this->blockAddress=blockAddress;
	packet=new SensorPacket(numberOfSensors);
}

/** @brief update sensor
 *  @param N/A
 *  @return N/A
 */
void SensorBlock::update(){
	I2CPi i2C;
	i2C.readI2C((*packet).charArray, (*packet).getNumberOfBytes(), blockAddress);
	(*packet).fromCharArray();
	
}

/** @brief retrieve a packet
 *  @return packet - SensorPacket
 */
SensorPacket SensorBlock::getPacket(){
	return (*packet);
}
