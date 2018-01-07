#pragma once
#include "Includes.h"
#include "IClientEntity.h"

class IGameMovement
{
public:
	void ProcessMovement(IClientEntity* ent, void* data)
	{
		typedef void(__thiscall* ProcessMovementFn)(void*, IClientEntity*, void*);
		CallVFunc<ProcessMovementFn>(this, 1)(this, ent, data);
	}

	void DecayPunchangle()
	{
		typedef void(__thiscall* DecayPunchangleFn)(void*);
		return CallVFunc<DecayPunchangleFn>(this, 76)(this);
	}
};
