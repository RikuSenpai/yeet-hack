#pragma once
#include "Includes.h"

class IPanel
{
public:
	const char* GetName(int panel)
	{
		typedef const char* (__thiscall* GetNameFn)(void*, int);
		return CallVFunc<GetNameFn>(this, 36)(this, panel);
	}
};