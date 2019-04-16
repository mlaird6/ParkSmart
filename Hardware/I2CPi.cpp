/** @file I2CPi.cpp
 *  @brief Class handles Pi specific I2C communication
 *
 *  The hatdware specific implementation of I2C communication on the raspverry pi, with the pi as the master in a master-slave configuration. A static variable is used to lock the I2C lines from other programs using this class.
 *
 *
 *  @param inUse ; static boolean variable to prevent programs from using the I2C lines at the same time as another
 *
 *  @author Melina Laird
 *  @author Mike Levis; primary author
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */
#include "I2CPi.h"

bool I2CPi::inUse=false;
/** @brief write data to the I2C from the buffer
 *  @param buffer ; buffer of data to be written
 *  @param bufferSize ; size of buffer to be written
 *  @param slaveAddress ; address of the slave device to be acsessed
 *  @return
 */
int I2CPi::writeI2C(void* buffer, int bufferSize, int slaveAddress){
int file_i2c;
#if I2CPI_DEBUG
fprintf(stderr, "bufferSize: %i, slaveAddress: %i", bufferSize, slaveAddress);
perror("");
for(int i =0; i<bufferSize;i++){
fprintf(stderr, "buffer[%i]: %i", i, (int) buffer[i]);
perror("");
}
#endif
while (inUse==true){
//do nothing
}
#if I2CPI_DEBUG
perror("Now running");
#endif
inUse=true;//once the loop has been exited reserve use
char *filename = (char*)"/dev/i2c-1";
if ((file_i2c = open(filename, O_RDWR)) < 0)
{
//ERROR HANDLING: you can check errno to see what went wrong
perror("Failed to open the i2c bus");
inUse=false;
return 1;
}
#if I2CPI_DEBUG
perror("Open file");
#endif

if (ioctl(file_i2c, I2C_SLAVE, slaveAddress) < 0)
{
perror("Failed to acquire bus access and/or talk to slave.\n");
//ERROR HANDLING; you can check errno to see what went wrong
inUse=false;
return 2;
}
#if I2CPI_DEBUG
perror("Connect to slave");
#endif
if (write(file_i2c, (char*)buffer, bufferSize) != bufferSize)//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
{
/* ERROR HANDLING: i2c transaction failed */
perror("Failed to write to the i2c bus.\n");
inUse=false;
return 3;
}
inUse=false;
#if I2CPI_DEBUG
perror("Write finished");
#endif
}
/** @Reads from I2C and puts bytes into buffer.
 *  @param buffer ; holds data that has been recived
 *  @param bufferSize ; the size of the buffer pointer and number of bytes expected
 *  @param slaveAddress ; address of the slave device to be acsessed
 *  @return int representing an error
 */
int I2CPi::readI2C(void* buffer, int bufferSize, int slaveAddress){
int file_i2c;
#if I2CPI_DEBUG
fprintf(stderr, "bufferSize: %i, slaveAddress: %i", bufferSize, slaveAddress);
perror("");
for(int i =0; i<bufferSize;i++){
fprintf(stderr, "buffer[%i]: %i", i, (int) buffer[i]);
perror("");
}
#endif
while (inUse==true){
//do nothing
}
#if I2CPI_DEBUG
perror("Now running");
#endif
inUse=true;//once the loop has been exited reserve use
char *filename = (char*)"/dev/i2c-1";
if ((file_i2c = open(filename, O_RDWR)) < 0)
{
//ERROR HANDLING: you can check errno to see what went wrong
perror("Failed to open the i2c bus");
inUse=false;
return 1;
}
#if I2CPI_DEBUG
perror("Open file");
#endif

if (ioctl(file_i2c, I2C_SLAVE, slaveAddress) < 0)
{
perror("Failed to acquire bus access and/or talk to slave.\n");
//ERROR HANDLING; you can check errno to see what went wrong
inUse=false;
return 2;
}
#if I2CPI_DEBUG
perror("Connect to slave");
#endif
if (read(file_i2c, (char*)buffer, bufferSize) != bufferSize)//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
{
//ERROR HANDLING: i2c transaction failed
perror("Failed to read from the i2c bus.\n");
inUse=false;
return 3;
}
inUse=false;
#if I2CPI_DEBUG
perror("Read finished");
for(int i =0; i<bufferSize;i++){
fprintf(stderr, "buffer[%i]: %i", i, (int) buffer[i]);
perror("");
}
#endif
}
