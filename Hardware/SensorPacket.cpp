/**
 *	@file SensorPacket.cpp
 *  @brief class to hold the sensor data to be transfered between devices
 *
 * 	This class is used to transfer sensor data between devices by converting the data held in the arrays to a single char array. This char array can then be sent another device wich can extract the data back using this class.
 *
 *  @author Melina Laird
 *  @author Mike Levis; primary auther
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include "SensorPacket.h"

/**
 *  @brief initialize sensor packet with number of sensors
 *
 *  @param numberOfSensors ; number of sensors
 *  @return N/A
 */
SensorPacket::SensorPacket(int numberOfSensors){
	this->numberOfSensors=numberOfSensors;
	sensorID = new uint16_t[numberOfSensors];
	sensorState = new bool[numberOfSensors];
	numberOfBytes = numberOfSensors * (sizeof(uint16_t) + sizeof(bool));
	charArray= new char[numberOfBytes];
}

/**
 *  @brief converts the data held to a single char array
 *
 *  @param N/A
 *  @return N/A
 */
void SensorPacket::toCharArray(){
	for (int i=0; i<(numberOfSensors); i++){
		charArray[(i*3) + 0]=(char)(sensorID[i] & 0x00ff);//low byte
		charArray[(i*3) + 1]=(char)(sensorID[i] >>8);//high byte
		charArray[(i*3) + 2]=(char)(sensorState[i]);//sensor byte
	}
}

/**
 *  @brief Mconverts a char array to the sensor data
 *
 *  @param N/A
 *  @return N/A
 */
void SensorPacket::fromCharArray(){
	uint16_t temp;
	for (int i=0; i<(numberOfSensors); i++){
		temp=(uint16_t)charArray[(i*3) + 0];//low byte
		temp= temp + (((uint16_t)charArray[(i*3) + 1])<<8);//high byte
		sensorID[i]=temp;
		sensorState[i]=(bool)charArray[(i*3) + 2];//sensor byte
	}
}

/**
 *  @brief get the number of bytes
 *
 *  @param N/A
 *  @return numberOfBytes : number of bytes
 */
int SensorPacket::getNumberOfBytes(){
	return numberOfBytes;
}

/**
 *  @brief get the number of sensors
 *
 *  @param N/A
 *  @return numberOfSensors ; the number of sensors
 */
int SensorPacket::getNumberOfSensors(){
	return numberOfSensors;
}
