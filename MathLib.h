#pragma once

#define M_PI		3.14159265358979323846
#define M_PI_F		((float)(M_PI))

#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

enum
{
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};

inline void MatrixPosition(const matrix3x4 &matrix, Vector3 &position)
{
	position[0] = matrix[0][3];
	position[1] = matrix[1][3];
	position[2] = matrix[2][3];
}

void inline SinCos(float radians, float *sine, float *cosine)
{
#if defined( _X360 )
	XMScalarSinCos(sine, cosine, radians);
#elif defined( COMPILER_MSVC32 )
	_asm
	{
		fld		DWORD PTR[radians]
		fsincos

		mov edx, DWORD PTR[cosine]
		mov eax, DWORD PTR[sine]

		fstp DWORD PTR[edx]
		fstp DWORD PTR[eax]
	}
#elif defined( GNUC )
	register double __cosr, __sinr;
	__asm __volatile__("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));

	*sine = __sinr;
	*cosine = __cosr;
#else
	*sine = sinf(radians);
	*cosine = cosf(radians);
#endif
}

void AngleVectors(const Vector3 &angles, Vector3 *forward)
{
	float	sp, sy, cp, cy;

	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}
