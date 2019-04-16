
#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
	private:
		int trigPin;
		int echoPin;
		int sensorID;
		double rangeThreshold;
		double calibrationConstant;
		double calibrationScaling;
		double rawRange;
	public:
		Sensor(int trigPin, int echoPin, int sensorID, double rangeThreshold= 100, double calibrationScaling=(1.0/56.0), double calibrationConstant=0);
		void setCalibrationConstant(double);
		void setCalibrationScalling(double);
		void setRangeThreshold(double);
		double getCallibrationConstant() const;
		double getCallibrationScalling() const;
		double getRangeThreshold() const;
		double getRawRange() const;
		bool carInRange();
		void update();
		int getSensorID();
};

#endif