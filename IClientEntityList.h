#pragma once
#include "Includes.h"
#include "IClientEntity.h"

class IClientEntityList
{
public:

	///<summary>Returns entity with index (index) and cast's it to template</summary>
	template <typename t>
	t* GetClientEntity(int index)
	{
		typedef t* (__thiscall* GetClientEntityFn)(void*, int);
		return CallVFunc <GetClientEntityFn>(this, 3)(this, index);
	}

	///<summary>Is this event needed?</summary>
	IClientEntity* GetClientEntityFromHandle(DWORD handle)
	{
		typedef IClientEntity* (__thiscall* GetClientEntityFromHandleFn)(void*, int);
		return CallVFunc<GetClientEntityFromHandleFn>(this, 4)(this, handle);
	}

	///<summary>Returns count of all entities on the map</summary>
	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* GetHighestEntityIndexFn)(void*);
		return CallVFunc<GetHighestEntityIndexFn>(this, 6)(this);
	}
};