#include "MadgwickAHRS.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "math.h"

MadgwickAHRS::MadgwickAHRS()
{
	Q = Quaternion(1, 0, 0, 0);
	SamplePeriod = 1 / (float)256;
	Beta = 0.1;
}

MadgwickAHRS::MadgwickAHRS(float samplePeriod)
{
	Q = Quaternion(1, 0, 0, 0);
	h = Quaternion(1, 0, 0, 0);
	b = Quaternion(1, 0, 0, 0);
	
	SamplePeriod = samplePeriod;
	Beta = 1;
}

void MadgwickAHRS::Update(Vector3 Gyroscope, Vector3 Accelerometer, Vector3 Magnometer)
{
	
	//Normalize Acceleromete and Magnometer, return to not divide by zero
	if (Accelerometer.Norm() != 0)
	{
		Accelerometer = Accelerometer / Accelerometer.Norm();
	}
	else
	{
		return;
	}

	if (Magnometer.Norm() != 0)
	{
		Magnometer = Magnometer / Magnometer.Norm();
	}
		else
	{
		return;
	}	

	h = Quaternion::Product(Q, Quaternion::Product(Quaternion(0, Magnometer), Quaternion::Conjugate(Q)));
	b = Quaternion(0, sqrt(h.Values[1] * h.Values[1] + h.Values[2] * h.Values[2]), 0, h.Values[3]);

	F[0] = 2 * (Q.Values[1] * Q.Values[3] - Q.Values[0] * Q.Values[2]) - Accelerometer.Values[0];
	F[1] = 2 * (Q.Values[0] * Q.Values[1] + Q.Values[2] * Q.Values[3]) - Accelerometer.Values[1];
	F[2] = 2 * (0.5 - Q.Values[1] * Q.Values[1] - Q.Values[2] * Q.Values[2]) - Accelerometer.Values[2];

	F[3] = 2 * b.Values[1] * (0.5 - Q.Values[2] * Q.Values[2] - Q.Values[3] * Q.Values[3]) + 2 * b.Values[3] * (Q.Values[1] * Q.Values[3] - Q.Values[0] * Q.Values[2]) - Magnometer.Values[0];
	F[4] = 2 * b.Values[1] * (Q.Values[1] * Q.Values[2] - Q.Values[0] * Q.Values[3]) + 2 * b.Values[3] * (Q.Values[0] * Q.Values[1] + Q.Values[2] * Q.Values[3]) - Magnometer.Values[1];
	F[5] = 2 * b.Values[1] * (Q.Values[0] * Q.Values[2] + Q.Values[1] * Q.Values[3]) + 2 * b.Values[3] * (0.5 - Q.Values[1] * Q.Values[1] - Q.Values[2] * Q.Values[2]) - Magnometer.Values[2];

	J[0][0] = -2 * Q.Values[2];
	J[0][1] = 2 * Q.Values[3];
	J[0][2] = -2 * Q.Values[0];
	J[0][3] = 2 * Q.Values[1];

	J[1][0] = 2 * Q.Values[1];
	J[1][1] = 2 * Q.Values[0];
	J[1][2] = 2 * Q.Values[3];
	J[1][3] = 2 * Q.Values[2];

	J[2][0] = 0;
	J[2][1] = -4 * Q.Values[1];
	J[2][2] = -4 * Q.Values[2];
	J[2][3] = 0;

	J[3][0] = -2 * b.Values[3] * Q.Values[2];
	J[3][1] = 2 * b.Values[3] * Q.Values[3];
	J[3][2] = -4 * b.Values[1] * Q.Values[2] - 2 * b.Values[3] * Q.Values[0];
	J[3][3] = -4 * b.Values[1] * Q.Values[3] + 2 * b.Values[3] * Q.Values[1];
	//

	J[4][0] = -2 * b.Values[1] * Q.Values[3] + 2 * b.Values[3] * Q.Values[1];
	J[4][1] = 2 * b.Values[1] * Q.Values[2] + 2 * b.Values[3] * Q.Values[0];
	J[4][2] = 2 * b.Values[1] * Q.Values[1] + 2 * b.Values[3] * Q.Values[3];
	J[4][3] = -2 * b.Values[1] * Q.Values[0] + 2 * b.Values[3] * Q.Values[2];

	J[5][0] = 2 * b.Values[1] * Q.Values[2];
	J[5][1] = 2 * b.Values[1] * Q.Values[3] - 4 * b.Values[3] * Q.Values[1];
	J[5][2] = 2 * b.Values[1] * Q.Values[0] - 4 * b.Values[3] * Q.Values[2];
	J[5][3] = 2 * b.Values[1] * Q.Values[1];
	//F 6x1
	//J 4x6
	//J'XF = 4x1

	Step.Values[0] = J[0][0] * F[0] + J[1][0] * F[1] + J[2][0] * F[2] + J[3][0] * F[3] + J[4][0] * F[4] + J[5][0] * F[5];
	Step.Values[1] = J[0][1] * F[0] + J[1][1] * F[1] + J[2][1] * F[2] + J[3][1] * F[3] + J[4][1] * F[4] + J[5][1] * F[5];
	Step.Values[2] = J[0][2] * F[0] + J[1][2] * F[1] + J[2][2] * F[2] + J[3][2] * F[3] + J[4][2] * F[4] + J[5][2] * F[5];
	Step.Values[3] = J[0][3] * F[0] + J[1][3] * F[1] + J[2][3] * F[2] + J[3][3] * F[3] + J[4][3] * F[4] + J[5][3] * F[5];

	Step = Step / Step.Norm();

    qDot = Quaternion::Product(Quaternion(0, Gyroscope), Q) * 0.5 + Step * -Beta;

	Q = Q + qDot * SamplePeriod;
	Q = Q / Q.Norm();

}
