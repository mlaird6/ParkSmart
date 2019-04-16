#ifndef SENSORPACKET_H
#define SENSORPACKET_H
#include<cstdint> //for Pi
//#include<stdint.h> //for arduino
class SensorPacket{
	private:
		int numberOfSensors;
		int numberOfBytes;
	public :
		
		uint16_t* sensorID;//to ensure size is the same on multiple devieces
		bool* sensorState;
		char* charArray;
		
		SensorPacket(int numberOfSensors);
		void toCharArray();
		void fromCharArray();
		int getNumberOfBytes();
		int getNumberOfSensors();
		
};

#endif