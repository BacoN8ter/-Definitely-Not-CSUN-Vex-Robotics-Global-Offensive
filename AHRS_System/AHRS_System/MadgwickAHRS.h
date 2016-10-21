#pragma once

#include "Quaternion.h"
#include "Vector3.h"

class MadgwickAHRS {
public:
	float SamplePeriod;
	Quaternion Q;
	float Beta;

	MadgwickAHRS();
	MadgwickAHRS(float samplePeriod);

	void Update(Vector3 Gyroscope, Vector3 Accelerometer, Vector3 Magnometer);

	float F[6];
	float J[6][4];
	Quaternion Step, b, h, qDot;
};