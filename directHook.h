#pragma once

class DirectHook
{
private:
	int offset;

public:
	DirectHook(DWORD instance)
	{
		offset = instance;
		//offset = *((int*)instance);
	}

	DWORD dwHookMethod(DWORD dwNewFunc)
	{
		/*int entry = offset;
		int org = *((int*)entry);

		int org_protect = Unprotect((void*)entry);
		*((int*)entry) = (int)dwNewFunc;

		return org;*/

		DWORD_PTR* g_pHook;
		g_pHook = (DWORD_PTR*)offset;
		DWORD orig = *g_pHook;
		*g_pHook = (DWORD_PTR)&dwNewFunc;

		return orig;
	}
};