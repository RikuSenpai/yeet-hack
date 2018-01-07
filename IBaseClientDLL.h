#pragma once
#include "Includes.h"
#include "ClientClass.h"

class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses()
	{
		typedef ClientClass* (__thiscall* GetAllClassesFn)(void*);
		return CallVFunc<GetAllClassesFn>(this, 8)(this);
	}
};