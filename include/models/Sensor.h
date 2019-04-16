#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
	private:
		double rangeThreshold;
		double calibrationConstant;
		double calibrationScaling;
		double rawRange;
		void update();
	public:
		Sensor(double rangeThreshold= 200, double calibrationScaling=(1.0/56.0), double calibrationConstant=0);
		void setCalibrationConstant(double);
		void setCalibrationScalling(double);
		void setRangeThreshold(double);
		double getCallibrationConstant() const;
		double getCallibrationScalling() const;
		double getRangeThreshold() const;
		double getRawRange() const;
		bool carInRange();
};

#endif