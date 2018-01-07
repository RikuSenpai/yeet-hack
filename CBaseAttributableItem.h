#pragma once

class C_BaseAttributableItem : public CBaseWeapon {
public:
	unsigned int* GetAccountID() {
		return reinterpret_cast<unsigned int*>(uintptr_t(this) + NetVars.m_iAccountID);
	}

	int* GetItemDefinitionIndex() {
		return reinterpret_cast<int*>(uintptr_t(this) + NetVars.m_iItemDefinitionIndex);
	}

	unsigned int* GetItemIDHigh() {
		return reinterpret_cast<unsigned int*>(uintptr_t(this) + NetVars.m_iItemIDHigh);
	}

	int* GetEntityQuality() {
		return reinterpret_cast<int*>(uintptr_t(this) + NetVars.m_iEntityQuality);
	}

	char* GetCustomName() {
		return reinterpret_cast<char*>(uintptr_t(this) + NetVars.m_szCustomName);
	}

	unsigned int* GetFallbackPaintKit() {
		return reinterpret_cast<unsigned int*>(uintptr_t(this) + NetVars.m_nFallbackPaintKit);
	}

	unsigned int* GetFallbackSeed() {
		return reinterpret_cast<unsigned int*>(uintptr_t(this) + NetVars.m_nFallbackSeed);
	}

	float* GetFallbackWear() {
		return reinterpret_cast<float*>(uintptr_t(this) + NetVars.m_flFallbackWear);
	}

	int* GetFallbackStatTrak() {
		return reinterpret_cast<int*>(uintptr_t(this) + NetVars.m_nFallbackStatTrak);
	}

	int* GetOriginalOwnerXuidLow()
	{
		return reinterpret_cast<int*>(uintptr_t(this) + NetVars.m_OriginalOwnerXuidLow);
	}

	int* GetOriginalOwnerXuidHigh()
	{
		return reinterpret_cast<int*>(uintptr_t(this) + NetVars.m_OriginalOwnerXuidHigh);
	}
};