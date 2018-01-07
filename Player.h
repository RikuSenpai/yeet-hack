#include "SDK.h"

class CBaseWeapon;
class CBaseAnimating;

class CPlayer : public IClientEntity
{
public:
	CPlayer();
	~CPlayer();

	bool IsValid();
	bool IsValid(CPlayer* pPlayer);

	Vector3 GetEyePosition();
	Vector3 GetPunchAngles();
	Vector3 GetViewPunchAngles();
	Vector3 GetVelocity();
	Vector3 GetBonePosition(int bone);
	Vector3 GetHitboxPosition(int hitbox);
	IClientEntity* CPlayer::GetObserverTarget();
	bool IsScoped();
	bool GetDormant();
	MoveType_t GetMoveType();
	byte GetLifeState();
	int GetFlags();
	int GetHealth();
	int GetTeam();
	int GetGlowIndex();
	int GetShotsFired();
	int GetHitboxSet();
	int GetUserId();
	int TickBase();
	float* GetFlashMaxAlpha();
	int ArmorValue();
	bool isArmored();
	UINT* GetActiveWeapon();
	int* GetWeapons();
	int* GetWearables();

	CBaseWeapon* GetWeap();
};

