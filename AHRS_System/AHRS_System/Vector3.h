#pragma once
class Vector3 {
public:
	float Values[3];

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator/(float value)
	{
		Vector3 v;
		for (short i = 0; i < 3; i++)
		{
			v.Values[i] = Values[i] / value;
		}
		return v;
	}
	Vector3 operator*(float value)
	{
		Vector3 v;
		for (short i = 0; i < 3; i++)
		{
			v.Values[i] = Values[i] * value;
		}
		return v;
	}
	Vector3 operator+(float value)
	{
		Vector3 v;
		for (short i = 0; i < 3; i++)
		{
			v.Values[i] = Values[i] + value;
		}
		return v;
	}

	float Norm();

};