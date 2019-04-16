#ifndef I2CPI_H
#define I2CPI_H

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <cstdio>

class I2CPi{
	private:
		static bool inUse;

	public:
		int writeI2C(void* buffer,int bufferSize, int slaveAddress);
		int readI2C (void* buffer,int bufferSize, int slaveAddress);
};

#endif
