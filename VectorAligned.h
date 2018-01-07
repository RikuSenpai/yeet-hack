#pragma once

#include "Includes.h"

class __declspec(align(16))VectorAligned : public Vector3
{
public:
	VectorAligned& operator=(const Vector3 &vOther)
	{
		Set(vOther.x, vOther.y, vOther.z);
		return *this;
	}
	float w;
};