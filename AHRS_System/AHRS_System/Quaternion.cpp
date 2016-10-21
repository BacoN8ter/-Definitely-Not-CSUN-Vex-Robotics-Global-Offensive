#include "Quaternion.h"
#include "math.h"

Quaternion::Quaternion(float a, float b, float c, float d)
{
	Values[0] = a;
	Values[1] = b;
	Values[2] = c;
	Values[3] = d;
}

Quaternion::Quaternion(float a, Vector3 v)
{
	Values[0] = a;
	for (int i = 0; i < 3; i++)
	{
		Values[i + 1] = v.Values[i];
	}
}

Quaternion::Quaternion()
{
	for (int i = 0; i < 4; i++)
	{
		Values[i] = 0;
	}
}

float Quaternion::Norm()
{
	return sqrt(Values[0] * Values[0] + Values[1] * Values[1] + Values[2] * Values[2] + Values[3] * Values[3]);
}
