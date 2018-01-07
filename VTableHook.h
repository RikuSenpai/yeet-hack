#pragma once
#include <Windows.h>

void Protect(void* reg, int protectType)
{
	MEMORY_BASIC_INFORMATION memInf;

	VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
	VirtualProtect(memInf.BaseAddress, memInf.RegionSize, protectType, &memInf.Protect);
}

int Unprotect(void* reg)
{
	MEMORY_BASIC_INFORMATION memInf;

	VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
	VirtualProtect(memInf.BaseAddress, memInf.RegionSize, PAGE_READWRITE, &memInf.Protect);

	return memInf.Protect;
}

void* hook(void* instance, void* hook, int offset)
{
	int vtable = *((int*)instance);
	int entry = vtable + sizeof(int) * offset;
	int org = *((int*)entry);

	int org_protect = Unprotect((void*)entry);
	*((int*)entry) = (int)hook;
	Protect((void*)entry, org_protect);

	return (void*)org;

}

