#ifndef SENSORBLOCK_H
#define SENSORBLOCK_H

#include <string>

#include "SensorPacket.h"	
#include "I2CPi.h"

class SensorBlock{
	private:
		int numberOfSensors;
		int blockAddress;
		SensorPacket* packet;
		I2CPi i2C;
	public:
		SensorBlock(int numberOfSensors, int blockAddress);
		void update();
		SensorPacket getPacket();
		
};

#endif