#include "Player.h"
#include "Utils.h"
#include "BaseWeapon.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::IsValid()
{
	if (!this)
		return false;

	if (this->GetHealth() < 1)
		return false;

	if (this->GetLifeState() != LIFE_ALIVE)
		return false;

	if (this->IsDormant())
		return false;

	return true;
}

bool CPlayer::IsValid(CPlayer* pPlayer)
{
	if (!this->IsValid())
		return false;

	if (this->IsDormant())
		return false;

	if (this->GetIndex() == pPlayer->GetIndex())
		return false;

	if (this->GetTeam() == pPlayer->GetTeam())
		return false;

	return true;
}

Vector3 CPlayer::GetEyePosition() throw()
{
	return ReadPtr<Vector3>(this, NetVars.m_vecViewOffset) + GetOrigin();
}

Vector3 CPlayer::GetPunchAngles()
{
	return ReadPtr<Vector3>(this, NetVars.m_vecPunchAngles);
}

Vector3 CPlayer::GetViewPunchAngles()
{
	return ReadPtr<Vector3>(this, NetVars.m_vecViewPunchAngles);
}

Vector3 CPlayer::GetVelocity()
{
	return ReadPtr<Vector3>(this, NetVars.m_vecVelocity);
}

Vector3 CPlayer::GetBonePosition(int bone)
{
	matrix3x4 matrix[128];

	if (!this->SetupBones(matrix, 128, 0x100, Interface.Engine->Time()))
		return Vector3();

	return Vector3(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);
}

Vector3 CPlayer::GetHitboxPosition(int hitbox)
{
	model_t* model = this->GetModel();
	if (!model)
		return Vector3(0.0f, 0.0f, 0.0f);

	studiohdr_t* hdr = Interface.ModelInfo->GetStudiomodel(model);
	if (!hdr)
		return Vector3(0.0f, 0.0f, 0.0f);

	matrix3x4 matrix[128];
	if (!this->SetupBones(matrix, 128, 0x100, 0/*Interface.Globals->curtime*/))
		return Vector3(0.0f, 0.0f, 0.0f);

	mstudiohitboxset_t *set = hdr->pHitboxSet(GetHitboxSet());
	if (!set)
		return Vector3(0.0f, 0.0f, 0.0f);

	mstudiobbox_t* box = set->pHitbox(hitbox);
	if (!box)
		return Vector3(0.0f, 0.0f, 0.0f);

	Vector3 center = ((box->bbmin + box->bbmax) * .5f);

	Vector3 hitboxpos;

	U::VectorTransform(center, matrix[box->bone], hitboxpos);

	return hitboxpos;
}

IClientEntity* CPlayer::GetObserverTarget()
{
	return Interface.EntityList->GetClientEntityFromHandle(ReadPtr<DWORD>(this, NetVars.m_hObserverTarget));
}

bool CPlayer::IsScoped()
{
	return ReadPtr<bool>(this, NetVars.m_bIsScoped);
}

bool CPlayer::GetDormant()
{
	return ReadPtr<bool>(this, 0xE9);
}

MoveType_t CPlayer::GetMoveType()
{
	return ReadPtr<MoveType_t>(this, 0x258);
}

byte CPlayer::GetLifeState()
{
	return ReadPtr<byte>(this, NetVars.m_lifeState);
}

int CPlayer::GetFlags()
{
	return ReadPtr<int>(this, NetVars.m_fFlags);
}

int CPlayer::GetHealth()
{
	return ReadPtr<int>(this, NetVars.m_iHealth);
}

int CPlayer::GetTeam() throw()
{
	return ReadPtr<int>(this, NetVars.m_iTeamNum);
}

int CPlayer::GetGlowIndex()
{
	return ReadPtr<int>(this, NetVars.m_iGlowIndex);
}

int CPlayer::GetShotsFired()
{
	return ReadPtr<int>(this, NetVars.m_iShotsFired);
}

int CPlayer::GetHitboxSet()
{
	return ReadPtr<int>(this, NetVars.m_nHitboxSet);
}

int CPlayer::GetUserId()
{
	player_info_t player_info;

	Interface.Engine->GetPlayerInfo(this->GetIndex(), &player_info);

	return player_info.userid;
}

int CPlayer::TickBase()
{
	return ReadPtr<int>(this, NetVars.m_nTickBase);
}

float* CPlayer::GetFlashMaxAlpha()
{
	return (float*)((DWORD)this + NetVars.m_flFlashMaxAlpha);
}

int CPlayer::ArmorValue()
{
	return ReadPtr<int>(this, 0xAA04);
}

bool CPlayer::isArmored()
{
	return ArmorValue() > 0;
}

UINT* CPlayer::GetActiveWeapon()
{
	return ReadPtr<UINT*>(this, NetVars.m_hActiveWeapon);
}

int* CPlayer::GetWeapons()
{
	return reinterpret_cast<int*>(uintptr_t(this) + 0x2DE8);
}

int* CPlayer::GetWearables()
{
	return (int*)((uintptr_t)this + NetVars.m_hMyWearables);
}

CBaseWeapon* CPlayer::GetWeap()
{
	return (CBaseWeapon*)Interface.EntityList->GetClientEntityFromHandle((DWORD)GetActiveWeapon());
}

int CBaseWeapon::GetItemDefinitionIndex()
{
	return ReadPtr<int>(this, NetVars.m_iItemDefinitionIndex);
}
