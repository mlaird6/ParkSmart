/** @file Sensor.cpp
 *  @brief Contains information related to a sensor.
 *
 *  Sensors are used to detect whether a parking space is occupied or not.
 *
 *  @author Melina Laird
 *  @author Mike Levis; primary author
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */


#include "Sensor.h"
#include "Arduino.h"
//implimentation specific functions for the arduino

/**
 *  @brief Initialize sensor
 *
 * 	Initialize sensor with range threshold, calibration scaling, and callibration constant
 *
 *  @param rangeThreshold - range threshold
 *  @param calibrationScaling - calibration scaling
 *  @param calibrationConstant - calibration constant
 *  @return N/A
 */
Sensor::Sensor(int trigPin, int echoPin, int sensorID, double rangeThreshold, double calibrationScaling, double calibrationConstant){
	this->rangeThreshold=rangeThreshold;
	this->calibrationScaling=calibrationScaling;
	this->calibrationConstant=calibrationConstant;
	this->trigPin=trigPin;
	this->echoPin=echoPin;
	this->sensorID=sensorID;

	pinMode(trigPin, OUTPUT);//configures pins
	pinMode(echoPin, INPUT);
}

/**
 *  @brief brief update sensor
 *
 * 	send and recieve pulse to update
 *
 *  @param N/A
 *  @return N/A
 */
void Sensor::update(){
	//send pulse
	digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

	//recive pulse
    rawRange = pulseIn(echoPin, HIGH);

}

/**
 *  @brief set sensor calibration constant
 *
 * 	simple setter for the calibration constant
 *
 *  @param calibrationConstant - the calibration constant to be set
 *  @return N/A
 */
void Sensor::setCalibrationConstant(double calibrationConstant){
	this->calibrationConstant=calibrationConstant;
}

/**
 *  @brief set sensor calibration scaling
 *
 * 	simple setter for the calibration scaling
 *
 *  @param setCalibrationScalling - the calibration scaling to be set
 *  @return N/A
 */
void Sensor::setCalibrationScalling(double calibrationScaling){
	this->calibrationScaling=calibrationScaling;
}

/**
 *  @brief set sensor range threshold
 *
 * 	simple setter for the calibration threshold
 *
 *  @param setCalibrationScalling - the calibration threshold to be set
 *  @return N/A
 */
void Sensor::setRangeThreshold(double rangeThreshold){
	this->rangeThreshold=rangeThreshold;
}

/**
 *  @brief get sensor calibration constant
 *
 * 	simple getter for the calibration constant
 *
 *  @param N/A
 *  @return calibrationConstant - the calibration constant
 */
double Sensor::getCallibrationConstant() const{
	return this->calibrationConstant;
}

/**
 *  @brief get sensor calibration Scalling
 *
 * 	simple getter for the calibration Scalling
 *
 *  @param N/A
 *  @return calibrationScaling - the calibration Scaling
 */
double Sensor::getCallibrationScalling() const{
	return this->calibrationScaling;
}

/**
 *  @brief get sensor calibration threshold
 *
 * 	simple getter for the calibration threshold
 *
 *  @param N/A
 *  @return calibrationThreshold - the calibration threshold
 */
double Sensor::getRangeThreshold() const{
	return this->rangeThreshold;
}

/**
 *  @brief get sensor sensor raw range
 *
 * 	simple getter for the raw range
 *
 *  @param N/A
 *  @return rawRange - raw range
 */
double Sensor::getRawRange() const{
	return this->rawRange;
}

/**
 *  @brief Check if there is a car in the parking spot near sensor
 *
 * 	Check if there is a car in the parking spot near sensor using current range = RR*scaling+scaling
 *
 *  @param N/A
 *  @return true or false (whether the car is in range)
 */
bool Sensor::carInRange(){
	double currentRange=rawRange * calibrationScaling + calibrationScaling;
	if(currentRange < rangeThreshold)//something is there
		return true;
	return false;
}

/**
 *  @brief retrieves this sensor id
 *
 *  @param N/A
 *  @return sensorID; int
 */
int Sensor::getSensorID(){
	return this->sensorID;
}
