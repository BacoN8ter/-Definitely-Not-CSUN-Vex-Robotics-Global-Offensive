#pragma once
#include "Vector3.h"

class Quaternion {
public:
	float Values[4];

	Quaternion(float a, float b, float c, float d);
	Quaternion(float a, Vector3 v);
	Quaternion();

	Quaternion operator+(float value)
	{
		Quaternion q;
		for (int i = 0; i < 4; i++)
		{
			q.Values[i] = Values[i] + value;
		}
		return q;
	}
	Quaternion operator+(Quaternion q)
	{
		Quaternion r;
		for (int i = 0; i < 4; i++)
		{
			r.Values[i] = q.Values[i] + Values[i];
		}
		return r;
	}
	Quaternion operator*(float value)
	{
		Quaternion q = Quaternion(0, 0, 0, 0);
		for (int i = 0; i < 4; i++)
		{
			q.Values[i] = Values[i] * value;
		}
		return q;
	}


	Quaternion operator/(float value)
	{
		Quaternion q = Quaternion(0, 0, 0, 0);
		for (int i = 0; i < 4; i++)
		{
			q.Values[i] = Values[i] / value;
		}
		return q;
	}



	float Norm();

	static Quaternion Product(Quaternion q, Quaternion r)
	{
		Quaternion a;
		a.Values[0] = q.Values[0] * r.Values[0] - q.Values[1] * r.Values[1] - q.Values[2] * r.Values[2] - q.Values[3] * r.Values[3];

		a.Values[1] = q.Values[0] * r.Values[1] + q.Values[1] * r.Values[0] + q.Values[2] * r.Values[3] - q.Values[3] * r.Values[2];

		a.Values[2] = q.Values[0] * r.Values[2] - q.Values[1] * r.Values[3] + q.Values[2] * r.Values[0] + q.Values[3] * r.Values[1];

		a.Values[3] = q.Values[0] * r.Values[3] + q.Values[1] * r.Values[2] - q.Values[2] * r.Values[1] + q.Values[3] * r.Values[0];

		return a;
	}
	static Quaternion Conjugate(Quaternion q)
	{
		return Quaternion(q.Values[0], -q.Values[1], -q.Values[2], -q.Values[3]);
	}

};
