#pragma once
#include "Includes.h"
#include "CGlobalVars.h"

class IPlayerInfoManager
{
public:
	CGlobalVars* GetGlobalVars()
	{
		typedef CGlobalVars*(__thiscall* GetGlobalVarsFn)(void*);
		return CallVFunc<GetGlobalVarsFn>(this, 1)(this);
	}
};