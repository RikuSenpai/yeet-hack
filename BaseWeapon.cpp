#include "BaseWeapon.h"


CBaseWeapon::CBaseWeapon()
{
}


CBaseWeapon::~CBaseWeapon()
{
}

float CBaseWeapon::NextPrimaryAttack()
{
	return ReadPtr<float>(this, NetVars.m_flNextPrimaryAttack);
}

float CBaseWeapon::NextSecondaryAttack()
{
	return ReadPtr<float>(this, NetVars.m_flNextSecondaryAttack);
}

int CBaseWeapon::ClipAmmo()
{
	return ReadPtr<int>(this, NetVars.m_iClip1);
}

int CBaseWeapon::ClipAmmo2()
{
	return ReadPtr<int>(this, NetVars.m_iClip2);
}

int CBaseWeapon::ShotsFired()
{
	return ReadPtr<int>(this, NetVars.m_iShotsFired);
}

CCSWeaponInfo_t* CBaseWeapon::GetWpnData()
{
	typedef CCSWeaponInfo_t*(__thiscall* OriginalFn)(void*);
	return CallVFunc<OriginalFn>(this, 456)(this);
}

void CBaseWeapon::UpdateAccuracyPenalty()
{
	typedef void(__thiscall *FunctionFn)(void*);
	reinterpret_cast<FunctionFn>(*reinterpret_cast<PDWORD>(*reinterpret_cast<PDWORD>(this) + 0x748))((void*)this);
}

/*float CBaseWeapon::GetAccuracyPenalty()
{
	return *(float*)((DWORD)this + NetVars.m_fAccuracyPenalty);
}*/

