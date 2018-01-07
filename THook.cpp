#include "THook.h"


CTHook::CTHook(void* instance, void* hook)
{
	int vtable = *((int*)instance);
	int entry = vtable;
	int org = *((int*)entry);

	int org_protect = Unprotect((void*)entry);
	*((int*)entry) = (int)hook;

	orig = org;
	hk = hook;
	ent = entry;
}


CTHook::CTHook(void* instance, void* hook, int offset)
{
	int vtable = *((int*)instance);
	int entry = vtable + sizeof(int) * offset;
	int org = *((int*)entry);

	int org_protect = Unprotect((void*)entry);
	*((int*)entry) = (int)hook;

	orig = org;
	hk = hook;
	ent = entry;
}

void* CTHook::GetOriginal()
{
	return (void*)orig;
}

void* CTHook::Rehook()
{
	*((int*)ent) = (int)hk;
	return (void*)orig;
}

void CTHook::Unhook()
{
	*((int*)ent) = (int)orig;
}

void CTHook::Revert()
{
	*((int*)ent) = (int)orig;
	Protect((void*)ent, orig_protect);
}

void CTHook::Protect(void* reg, int protectType)
{
	MEMORY_BASIC_INFORMATION memInf;

	VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
	VirtualProtect(memInf.BaseAddress, memInf.RegionSize, protectType, &memInf.Protect);
}

int CTHook::Unprotect(void* reg)
{
	MEMORY_BASIC_INFORMATION memInf;

	VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
	VirtualProtect(memInf.BaseAddress, memInf.RegionSize, PAGE_READWRITE, &memInf.Protect);

	return memInf.Protect;
}