#include "SDK.h"

// ATTENTION: STRUCT INCOMPLETE AND EBANUTAYA
struct CCSWeaponInfo_t
{
	char __pad0x0063[0x0063];
	char m_pszName[32];		        //0x63
	char __pad0x0023[0x0023];
	char m_pszModel[32];		        //0xA6
	char __pad0x0682[0x0682];
	int m_nType;				//0x748
	char __pad0x0004[0x0004];
	int m_nID;				//0x750
	char __pad0x0234[0x0234];
	BYTE m_IsFullAuto;			//0x988
	char __pad0x001F[0x001F];
	float m_flPenetration;		        //0x9A8
	int m_nDamage;			        //0x9AC
	float m_flRange;			//0x8B0
	float m_flRangeModifier;		//0x9B4
	int m_nBullets;				//0x9B8
};

class CBaseWeapon : IClientEntity
{
public:
	CBaseWeapon();
	~CBaseWeapon();

	float NextPrimaryAttack();
	float NextSecondaryAttack();
	int GetItemDefinitionIndex();
	int ClipAmmo();
	int ClipAmmo2();
	int ShotsFired();
	CCSWeaponInfo_t* GetWpnData();

	void UpdateAccuracyPenalty();
	/*float GetWeaponCone();
	float GetWeaponSpread();
	float GetAccuracyPenalty();*/
};

