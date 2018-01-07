#pragma once
#include "directHook.h"

#include <map>

/*typedef DWORD** PPDWORD;
class CVMTHookManager
{
	CVMTHookManager(const CVMTHookManager&) = delete;
public:
	CVMTHookManager(PPDWORD ppClass, bool bReplace = true)
	{
		m_ppClassBase = ppClass;
		m_bReplace = bReplace;
		if (bReplace) {
			m_pOriginalVMTable = *ppClass;
			uint32_t dwLength = CalculateLength();

			m_pNewVMTable = new DWORD[dwLength];
			memcpy(m_pNewVMTable, m_pOriginalVMTable, dwLength * sizeof(DWORD));

			DWORD old;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*m_ppClassBase = m_pNewVMTable;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), old, &old);

		}
		else {
			m_pOriginalVMTable = *ppClass;
			m_pNewVMTable = *ppClass;
		}
	}
	~CVMTHookManager()
	{
		RestoreTable();
		if (m_bReplace && m_pNewVMTable) delete[] m_pNewVMTable;
	}

	void RestoreTable()
	{
		if (m_bReplace) {
			DWORD old;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*m_ppClassBase = m_pOriginalVMTable;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), old, &old);
		}
		else {
			UnHook();
		}
	}

	DWORD dwHookMethod(DWORD fnNew, uint32_t index)
	{
		DWORD dwOld = (DWORD)m_pOriginalVMTable[index];
		m_pNewVMTable[index] = (DWORD)fnNew;
		m_vecHookedIndexes.insert(std::make_pair(index, (DWORD)dwOld));
		return dwOld;
	}
	void UnHook()
	{
		for (auto& pair : m_vecHookedIndexes) {
			UnHook(pair.first);
		}
	}

	void UnHook(uint32_t index)
	{
		auto it = m_vecHookedIndexes.find(index);
		if (it != m_vecHookedIndexes.end()) {
			m_pNewVMTable[index] = (DWORD)it->second;
			m_vecHookedIndexes.erase(it);
		}
	}

	template<class Type>
	Type GetOriginal(uint32_t index)
	{
		return (Type)m_pOriginalVMTable[index];
	}

private:
	uint32_t CalculateLength()
	{
		uint32_t dwIndex = 0;
		if (!m_pOriginalVMTable) return 0;
		for (dwIndex = 0; m_pOriginalVMTable[dwIndex]; dwIndex++) {
			if (IsBadCodePtr((FARPROC)m_pOriginalVMTable[dwIndex])) {
				break;
			}
		}
		return dwIndex;
	}

private:
	std::map<uint32_t, DWORD> m_vecHookedIndexes;

	PPDWORD m_ppClassBase;
	PDWORD m_pOriginalVMTable;
	PDWORD m_pNewVMTable;
	bool m_bReplace;
};*/

class CVMTHookManager
{
private:
	int vtable;
	int orig;
	int orig_protect;
	DWORD hk;
	int ent;
	int offs;
public:
	CVMTHookManager(void* instance)
	{
		vtable = *((int*)instance);
	}

	DWORD dwHookMethod(DWORD dwNewFunc, unsigned int iIndex)
	{
		int entry = vtable + sizeof(int) * iIndex;
		int org = *((int*)entry);

		int org_protect = Unprotect((void*)entry);
		*((int*)entry) = (int)dwNewFunc;

		orig = org;
		hk = dwNewFunc;
		ent = entry;

		return orig;
	}

	void* GetOriginal()
	{
		return (void*)orig;
	}

	void* ReHook()
	{
		*((int*)ent) = (int)hk;
		return (void*)orig;
	}

	void UnHook()
	{
		*((int*)ent) = (int)orig;
	}

	void Revert()
	{
		*((int*)ent) = (int)orig;
		Protect((void*)ent, orig_protect);
	}

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
};

//class CVMTHookManager
//{
//public:
//	CVMTHookManager()
//	{
//		memset(this, 0, sizeof(CVMTHookManager));
//	}
//
//	CVMTHookManager(PDWORD* ppdwClassBase)
//	{
//		bInitialize(ppdwClassBase);
//	}	
//
//	~CVMTHookManager()
//	{
//		UnHook();
//	}
//
//	bool bInitialize(PDWORD* ppdwClassBase)
//	{
//		m_ppdwClassBase = ppdwClassBase;
//		m_pdwOldVMT = *ppdwClassBase;
//		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
//		m_pdwNewVMT = new DWORD[m_dwVMTSize];
//		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD) * m_dwVMTSize);
//		*ppdwClassBase = m_pdwNewVMT;
//		return true;
//	}
//	bool bInitialize(PDWORD** pppdwClassBase) // fix for pp
//	{
//		return bInitialize(*pppdwClassBase);
//	}
//
//	void UnHook()
//	{
//		if (m_ppdwClassBase)
//		{
//			*m_ppdwClassBase = m_pdwOldVMT;
//		}
//	}
//
//	void ReHook()
//	{
//		if (m_ppdwClassBase)
//		{
//			*m_ppdwClassBase = m_pdwNewVMT;
//		}
//	}
//
//	int iGetFuncCount()
//	{
//		return (int)m_dwVMTSize;
//	}
//
//	DWORD dwGetMethodAddress(int Index)
//	{
//		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
//		{
//			return m_pdwOldVMT[Index];
//		}
//		return NULL;
//	}
//
//	PDWORD pdwGetOldVMT()
//	{
//		return m_pdwOldVMT;
//	}
//
//	DWORD dwHookMethod(DWORD dwNewFunc, unsigned int iIndex)
//	{
//		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
//		{
//			m_pdwNewVMT[iIndex] = dwNewFunc;
//			return m_pdwOldVMT[iIndex];
//		}
//
//		return NULL;
//	}
//
//	DWORD dwGetVMTCount(PDWORD pdwVMT)
//	{
//		DWORD dwIndex = 0;
//
//		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
//		{
//			if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
//			{
//				break;
//			}
//		}
//		return dwIndex;
//	}
//	PDWORD*	m_ppdwClassBase;
//	PDWORD	m_pdwNewVMT, m_pdwOldVMT;
//	DWORD	m_dwVMTSize;
//};