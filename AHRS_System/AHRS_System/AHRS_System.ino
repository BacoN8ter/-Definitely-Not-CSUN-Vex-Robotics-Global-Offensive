/*
Name:		AHRS.ino
Created:	10/19/2016 10:42:57 AM
Author:	Kevin Joyce

This is an AHRS based off the open source Madgwick algorithm
The algorithm in question is explained in the paper
An effcient orientation filter for inertial and inertial/magnetic sensor arrays
Sebastian O.H. Madgwick - April 30, 2010


*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

#include "MadgwickAHRS.h"
#include "Quaternion.h"
#include "Vector3.h"	
#include "math.h"
float samplesPerSecond = 200;
MadgwickAHRS AHRS = MadgwickAHRS(1 / samplesPerSecond);

/* Assign a unique ID to the sensors */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyro = Adafruit_L3GD20_Unified(20);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	Serial.println(("AHRS Test")); Serial.println("");

	/* Initialise the sensors */
	if (!accel.begin())
	{
		/* There was a problem detecting the ADXL345 ... check your connections */
		Serial.println(("Ooops, no LSM303 detected ... Check your wiring!"));
		while (1);
	}
	if (!mag.begin())
	{
		/* There was a problem detecting the LSM303 ... check your connections */
		Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
		while (1);
	}
	if (!gyro.begin())
	{
		/* There was a problem detecting the L3GD20 ... check your connections */
		Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
		while (1);
	}

}

sensors_event_t event;
Vector3 accel3, gyro3, mag3;

void loop() {

	accel.getEvent(&event);//get acceleration data
	accel3 = Vector3(event.acceleration.x, event.acceleration.y, event.acceleration.z);
	/*Serial.print("Acceleration : ");
	for (int i = 0; i < 3; i++)
	{
		Serial.print(accel3.Values[i]); Serial.print("  ");
	}
	Serial.println(accel3.Norm());*/

	mag.getEvent(&event);//get magnometer data
	mag3 = Vector3(event.magnetic.x, event.magnetic.y, event.magnetic.z);
	/*Serial.print("Magnometer : ");
	for (int i = 0; i < 3; i++)
	{
		Serial.print(mag3.Values[i]); Serial.print("  ");
	}
	Serial.println();*/

	gyro.getEvent(&event);//get gyroscope data
	gyro3 = Vector3(event.gyro.x, event.gyro.y, event.gyro.z);
	//Serial.print("Gyroscope : ");
	//for (int i = 0; i < 3; i++)
	//{
	//	Serial.print(gyro3.Values[i]); Serial.print("  ");
	//}
	//Serial.println(gyro3.Norm());

	AHRS.Update(gyro3, accel3, mag3);

	//
	//Serial.print("AHRS Q: ");

	//for (int i = 0; i < 4; i++)
	//{
	//	 Serial.print(AHRS.qDot.Values[i]); Serial.print("  ");
	//}
	//Serial.println();
	float x = atan2(2 * (AHRS.Q.Values[0] * AHRS.Q.Values[1] + AHRS.Q.Values[2] * AHRS.Q.Values[3]), 1 - 2 * (AHRS.Q.Values[1] * AHRS.Q.Values[1] + AHRS.Q.Values[2] * AHRS.Q.Values[2]));
	float y = asin(2 * (AHRS.Q.Values[0] * AHRS.Q.Values[2] - AHRS.Q.Values[3] * AHRS.Q.Values[1]));
	float z = atan2(2 * (AHRS.Q.Values[0] * AHRS.Q.Values[3] + AHRS.Q.Values[1] + AHRS.Q.Values[2]), 1 - 2 * (AHRS.Q.Values[2] * AHRS.Q.Values[2] + AHRS.Q.Values[3] * AHRS.Q.Values[3]));
	z = z * 180 / PI;
	z += z < 0 ? 360 : 0;
	Serial.print("Yaw :"); Serial.print(z); Serial.print(" Pitch: "); Serial.print(y * 180 / PI); Serial.print(" Roll: "); Serial.println(x * 180 / PI);
	delay(1000 / samplesPerSecond);

}
