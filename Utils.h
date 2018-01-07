#include "SDK.h"
class CPlayer;
class CBaseWeapon;
class KeyValues;

#define M_PI 3.14159265358979323846

namespace U
{
	int SafeWeaponID();
	KeyValues* CreateKeyValue(const char* matname, bool flat, bool ignorez);
	IMaterial* CreateMat(const char* matname, bool flat, bool ignorez);
	void InitKeyValues(KeyValues* pKeyValues, const char* name);
	void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = NULL, void* pfnEvaluateSymbolProc = nullptr);
	std::string GetWorkingPath();
	bool IsFileExists(const std::string& name);
	void ForceMaterial(IMaterial* material, float color[3]);
	bool IsHeadshoted(IClientEntity* pLocal, Vector3& vecStart, Vector3& vecEnd);
	bool IsVisible(Vector3& vecAbsStart, Vector3& vecAbsEnd, IClientEntity* pLocal, IClientEntity* pBaseEnt, bool smokeCheck = true);
	bool LineGoesThroughSmoke(Vector3 pos1, Vector3 pos2);
	Vector3 TraceWorld(Vector3& vecStart, Vector3& vecEnd, IClientEntity* pLocal);
	bool WorldToScreen(Vector3 &vOrigin, Vector3 &vScreen);
	void VectorTransform(const Vector3& vSome, const matrix3x4& vMatrix, Vector3& vOut);
	float Rad2Deg(float x);
	float Deg2Rad(float x);
	void SinCos(float x, float* s, float* c);
	void SinCos(float x, float &s, float &c);
	void AngleVectors(const Vector3& angles, Vector3* forward, Vector3* right, Vector3* up);
	void AngleVectors2(const Vector3& angles, Vector3* forward);
	void VectorAngles(const Vector3& forward, Vector3& angles);
	float VectorNormalize(Vector3& v);
	void AngleNormalize(Vector3& v);
	void ClampAngles(Vector3& v);
	float Clamp(float v, float mmin, float mmax);
	Vector3 CalculateAngle(const Vector3& in, Vector3 out);
	Vector2 RotatePoint(Vector3 pointToRotate, Vector3 centerPoint, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck, bool angleInRadians = false);
	bool CanShoot(CPlayer* pLocalPlayer, CBaseWeapon* weapon);
	void LoadKnifeModels();
	void FullUpdate();
	const char* GetKillIconWeapon(int si);
	int GetKnifeDefinitionIndex(int si);
	int GetGloveSkinByMenu(int gloveIndex, int skinIndex);
	char* GetConfigName(int weaponid);
	const char* GetWeaponNameById(int id);
	bool IsWeaponPistol(int weaponid);
	bool IsWeaponSniper(int weaponid);
	bool IsWeaponKnife(int weaponid);
	bool IsWeaponDefaultKnife(int weaponid);
	bool IsWeaponGrenade(int weaponid);
	bool IsWeaponBomb(int weaponid);
	bool IsWeaponTaser(int weaponid);
	bool IsWeaponShotgun(int weaponid);
	bool IsRcsWeapon(int weaponid);
	bool IsNonAimWeapon(int weaponid);
	bool IsModelKnife(int modelIndex);
	bool IsModelDefaultKnife(int modelIndex, int currentKnifeIndex);
	const char* GetModelByIndex(int id);
	int GetCurrentKnifeModel(int currentKnife);
}

/*#include "SDK.h"

#define M_PI 3.14159265358979323846

namespace U
{
	bool IsVisible(Vector3& vecAbsStart, Vector3& vecAbsEnd, IClientEntity* pLocal, IClientEntity* pBaseEnt)
	{
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		filter.pSkip = pLocal;

		ray.Init(vecAbsStart, vecAbsEnd);

		Interface.EngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

		return (tr.m_pEnt == pBaseEnt || tr.fraction > 0.99f);
	}

	Vector3 TraceWorld(Vector3& vecStart, Vector3& vecEnd, IClientEntity* pLocal)
	{
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		filter.pSkip = pLocal;

		ray.Init(vecStart, vecEnd);

		Interface.EngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

		return tr.endpos;
	}

	bool WorldToScreen(Vector3 &vOrigin, Vector3 &vScreen)
	{
		const matrix3x4& worldToScreen = Interface.Engine->WorldToScreenMatrix();

		int ScrW, ScrH;

		Interface.Engine->GetScreenSize(ScrW, ScrH);

		float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];
		vScreen.z = 0;
		if (w > 0.01)
		{
			float inverseWidth = 1 / w;
			vScreen.x = (ScrW / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * inverseWidth) * ScrW + 0.5);
			vScreen.y = (ScrH / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * inverseWidth) * ScrH + 0.5);
			return true;
		}
		return false;
	}

	void VectorTransform(const Vector3& vSome, const matrix3x4& vMatrix, Vector3& vOut)
	{
		for (auto i = 0; i < 3; i++)
			vOut[i] = vSome.Dot((Vector3&)vMatrix[i]) + vMatrix[i][3];
	}

	float Rad2Deg(float x)
	{
		return (x * (180.0f / M_PI));
	}

	float Deg2Rad(float x)
	{
		return (x * (M_PI / 180.0f));
	}

	void SinCos(float x, float* s, float* c)
	{
		__asm
		{
			fld dword ptr[x]
			fsincos
				mov edx, dword ptr[c]
				mov eax, dword ptr[s]
				fstp dword ptr[edx]
				fstp dword ptr[eax]
		}
	}

	void SinCos(float x, float &s, float &c)
	{
		__asm
		{
			fld dword ptr[x]
			fsincos
				mov edx, dword ptr[c]
				mov eax, dword ptr[s]
				fstp dword ptr[edx]
				fstp dword ptr[eax]
		}
	}

	void AngleVectors(const Vector3& angles, Vector3* forward, Vector3* right, Vector3* up)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(Deg2Rad(angles.x), &sp, &cp);
		SinCos(Deg2Rad(angles.y), &sy, &cy);
		SinCos(Deg2Rad(angles.z), &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
			right->y = (-1 * sr * sp * sy + -1 * cr * cy);
			right->z = -1 * sr * cp;
		}

		if (up)
		{
			up->x = (cr * sp * cy + -sr * -sy);
			up->y = (cr * sp * sy + -sr * cy);
			up->z = cr * cp;
		}
	}

	void AngleVectors2(const Vector3& angles, Vector3* forward)
	{
		float sp, sy, cp, cy;

		SinCos(Deg2Rad(angles.x), &sp, &cp);
		SinCos(Deg2Rad(angles.y), &sy, &cy);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}
	}

	void VectorAngles(const Vector3& forward, Vector3& angles)
	{
		float tmp, yaw, pitch;

		if (forward.y == 0 && forward.x == 0)
		{
			yaw = 0;

			if (forward.z > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else
		{
			yaw = Rad2Deg(atan2f(forward.y, forward.x));

			if (yaw < 0)
				yaw += 360;

			tmp = forward.Length2d();
			pitch = Rad2Deg(atan2f(-forward.z, tmp));

			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	float VectorNormalize(Vector3& v)
	{
		float flLength = v.Length();

		if (!flLength)
			v.Set();
		else
			v /= flLength;

		return flLength;
	}

	void AngleNormalize(Vector3& v)
	{
		for (auto i = 0; i < 3; i++)
		{
			if (v[i] < -180.0f) v[i] += 360.0f;
			if (v[i] >  180.0f) v[i] -= 360.0f;
		}
	}

	void ClampAngles(Vector3& v)
	{
		if (v.x > 89.0f && v.x <= 180.0f)
			v.x = 89.0f;

		if (v.x > 180.0f)
			v.x = v.x - 360.0f;

		if (v.x < -89.0f)
			v.x = -89.0f;

		v.y = fmodf(v.y + 180, 360) - 180;

		v.z = 0;
	}

	float Clamp(float v, float mmin, float mmax)
	{
		if (v > mmax) return mmax;
		if (v < mmin) return mmin;

		return v;
	}

	bool IsWeaponPistol(int weaponid)
	{
		if (weaponid == WEAPON_DEAGLE || weaponid == WEAPON_ELITE || weaponid == WEAPON_FIVESEVEN || weaponid == WEAPON_GLOCK || weaponid == WEAPON_HKP2000 || weaponid == WEAPON_P250 || weaponid == WEAPON_TEC9 || weaponid == WEAPON_USP_SILENCER)
			return true;

		return false;
	}

	bool IsWeaponSniper(int weaponid)
	{
		if (weaponid == WEAPON_AWP || weaponid == WEAPON_G3SG1 || weaponid == WEAPON_SCAR20 || weaponid == WEAPON_SSG08)
			return true;

		return false;
	}

	bool IsWeaponKnife(int weaponid)
	{
		if (weaponid == WEAPON_KNIFE || weaponid == WEAPON_KNIFE_T || weaponid == WEAPON_KNIFEGG || weaponid == WEAPON_KNIFE_BAYONET || weaponid == WEAPON_KNIFE_BUTTERFLY || weaponid == WEAPON_KNIFE_FALCHION || weaponid == WEAPON_KNIFE_FLIP || weaponid == WEAPON_KNIFE_GUT || weaponid == WEAPON_KNIFE_KARAMBIT || weaponid == WEAPON_KNIFE_M9_BAYONET || weaponid == WEAPON_KNIFE_PUSH || weaponid == WEAPON_KNIFE_TACTICAL)
			return true;

		return false;
	}

	bool IsWeaponGrenade(int weaponid)
	{
		if (weaponid == WEAPON_FLASHBANG || weaponid == WEAPON_HEGRENADE || weaponid == WEAPON_SMOKEGRENADE || weaponid == WEAPON_MOLOTOV || weaponid == WEAPON_INCGRENADE || weaponid == WEAPON_DECOY)
			return true;

		return false;
	}

	bool IsWeaponBomb(int weaponid)
	{
		if (weaponid == WEAPON_C4)
			return true;

		return false;
	}

	bool IsWeaponTaser(int weaponid)
	{
		if (weaponid == WEAPON_TASER)
			return true;

		return false;
	}

	bool IsWeaponShotgun(int weaponid)
	{
		if (weaponid == WEAPON_NOVA || weaponid == WEAPON_SAWEDOFF || weaponid == WEAPON_XM1014 || weaponid == WEAPON_MAG7)
			return true;

		return false;
	}

	bool IsRcsWeapon(int weaponid)
	{
		if (IsWeaponPistol(weaponid) || IsWeaponSniper(weaponid) || IsWeaponShotgun(weaponid))
			return false;

		return true;
	}

	bool IsNonAimWeapon(int weaponid)
	{
		if (IsWeaponKnife(weaponid) || IsWeaponGrenade(weaponid) || IsWeaponBomb(weaponid) || IsWeaponTaser(weaponid))
			return true;

		return false;
	}
}*/