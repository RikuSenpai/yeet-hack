#pragma once

#include "Includes.h"
#include "ITraceFilter.h"

class IEngineTrace
{
public:
	void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) throw()
	{
		typedef void(__thiscall* TraceRayFn)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		return CallVFunc<TraceRayFn>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
};