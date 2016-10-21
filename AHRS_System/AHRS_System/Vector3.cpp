#include "Vector3.h"
#include "math.h"

Vector3::Vector3()
{
	for (short i = 0; i < 3; i++)
	{
		Values[i] = 0;
	}
}
Vector3::Vector3(float x, float y, float z)
{
	Values[0] = x;
	Values[1] = y;
	Values[2] = z;
}

float Vector3::Norm()
{
	return sqrt(Values[0] * Values[0] + Values[1] * Values[1] + Values[2] * Values[2]);
}
