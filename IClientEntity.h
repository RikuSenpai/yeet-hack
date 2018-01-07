#pragma once
#include "Includes.h"

#include "IClientNetworkable.h"
#include "IClientRenderable.h"
#include "IClientUnknown.h"
#include "IClientThinkable.h"

struct SpatializationInfo_t;

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void             Release(void) = 0;
	virtual const Vector3    GetAbsOrigin(void) const = 0;
	virtual const Vector3    GetAbsAngles(void) const = 0;
	virtual void*            GetMouth(void) = 0;
	virtual bool             GetSoundSpatialization(SpatializationInfo_t info) = 0;
	virtual bool             IsBlurred(void) = 0;

	void SetModelIndexVirtual(int index)
	{
		typedef void(__thiscall* SetModelIndexFn)(void*, int);
		CallVFunc<SetModelIndexFn>(this, 75)(this, index);
	}

	int GetModelIndex()
	{
		return *(int*)((DWORD)this + 0x254);
	}

	void SetModelIndex(int index)
	{
		*(reinterpret_cast<int*>(uintptr_t(this) + 0x254)) = index;
	}

	Vector3 GetOrigin()
	{
		return *(Vector3*)((DWORD)this + 0x134);
	}
};