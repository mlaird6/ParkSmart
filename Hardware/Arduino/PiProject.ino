/** @file PiProject.ino
 *  @brief Main function for the arduino, runs the sensors
 *
 *  Creates sensors, gets data from them, and condenses them
 *  into a sensor packet and sends them over I2C when requested
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include <Wire.h>
#include "Sensor.h"
#include "SensorPacket.h"

#define SLAVE_ADDRESS 0x04
#define NUMBER_OF_SENSORS 1//number of sensors to actually run
const int ledPin =  LED_BUILTIN;// the number of the LED pin
const int dataPin =  A4;// the number of the LED pin
const int clkPin =  A5;// the number of the LED pin
const int trigPins[] = {2,4,6,8,10};//trigger pins of sensors
const int echoPins[] = {3,5,7,9,11};//echo pins of sensors
const int sensorIDs[] = {1,2,3,4,5};


int ledState = LOW;             // ledState used to set the LED

Sensor** sensorArray;
SensorPacket packet(NUMBER_OF_SENSORS);


unsigned long previousMillisLED = 0;        // will store last time LED was updated
unsigned long previousMillisTrig1 = 0;

const long intervalLED = 1000;           // interval at which to blink (milliseconds)
const long intervalTrig = 1000;
const long trigSpacing = 100;
const long timeout=(500);
long duration=2;// holds the time between pulse and echo

/**
 *  @brief setup the sensors and hardware
 *
 *  @param N/A
 *  @return N/A
 */
void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  sensorArray=new Sensor*[NUMBER_OF_SENSORS];
  for (int i=0; i<NUMBER_OF_SENSORS; i++) {
    *(sensorArray+i)=new Sensor(trigPins[i],echoPins[i],sensorIDs[i]);

  }

  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendData);

  Serial.begin (115200);
}

/**
 *  @brief checks the sensors periodically updating packet
 *
 *  @param N/A
 *  @return N/A
 */
void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisLED >= intervalLED) {
    // save the last time you blinked the LED
    previousMillisLED = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);

  }
   if (currentMillis - previousMillisTrig1 >= intervalTrig) {
    previousMillisTrig1 = currentMillis;
    for (int i=0; i<NUMBER_OF_SENSORS; i++){
      (*sensorArray[i]).update();
      delayMicroseconds(trigSpacing);
    }
    for (int i=0;i<NUMBER_OF_SENSORS;i++){
      packet.sensorID[i]=(*sensorArray[i]).getSensorID();
      packet.sensorState[i]=(*sensorArray[i]).carInRange();
    }
    packet.toCharArray();
    for(int i=0; i<packet.getSize();i++){
      Serial.print(packet.charArray[i]);
    }
    Serial.println();
    Serial.print((*sensorArray[0]).getRawRange());
    Serial.println();
    Serial.print((*sensorArray[0]).carInRange());
    Serial.println();
    Serial.println(packet.getSize());
   }

}

/**
 *  @brief Sends the data over I2C
 *
 *  @param N/A
 *  @return N/A
 */
void sendData(){
  for (int i=0;i<NUMBER_OF_SENSORS;i++){
    packet.sensorID[i]=(*sensorArray[i]).getSensorID();
    packet.sensorState[i]=(*sensorArray[i]).carInRange();
  }
  packet.toCharArray();

  Wire.write(packet.charArray, packet.getSize());

}
