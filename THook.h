#pragma once
#include <windows.h>

class CTHook
{
public:
	CTHook::CTHook(void* original, void* hook);
	CTHook(void * instance, void * hook, int offset);
	void* GetOriginal();
	void* Rehook();
	void Unhook();
	void Revert();
private:
	int orig;
	int orig_protect;
	void* hk;
	int ent;
	int offs;
	void Protect(void * reg, int protectType);
	int Unprotect(void * reg);
};

