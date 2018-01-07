#pragma once
#include "Includes.h"

class IVRenderView
{
public:
	void SetBlend(float blend)
	{
		typedef void(__thiscall* SetBlendFn)(void*, float);
		CallVFunc<SetBlendFn>(this, 4)(this, blend);
	}

	void SetColorModulation(float const* blend)
	{
		typedef void(__thiscall* SetColorModulationFn)(void*, float const*);
		CallVFunc<SetColorModulationFn>(this, 6)(this, blend);
	}
};
