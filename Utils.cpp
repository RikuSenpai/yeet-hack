#include "Utils.h"
#include "Player.h"
#include "BaseWeapon.h"
#include "KeyValues.h"
#include "XorStr.h"

#define M_PI 3.14159265358979323846
#define POINTERCHK( pointer ) ( pointer  && pointer !=0  && HIWORD( pointer ) )

namespace U
{
	int SafeWeaponID()
	{
		CPlayer* me = Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer());
		if (!me)
			return 0;

		CBaseWeapon* weap = me->GetWeap();
		if (!weap)
			return 0;

		return weap->GetItemDefinitionIndex();
	}

	KeyValues* CreateKeyValue(const char* matname, bool flat, bool ignorez)
	{
		std::string type = (flat) ? XorStr("UnlitGeneric") : XorStr("VertexLitGeneric");

		std::string matdata = XorStr("\"") + type + XorStr("\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"") + XorStr("\"\"\n\t\"$model\" \"0\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"") + XorStr("\"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"") + XorStr("\"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"0\"\n\t\"$ignorez\" \"") + std::to_string(ignorez) + XorStr("\"\n}\n");
		//std::string matdata = "\"" + type + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"" + "\"\"\n\t\"$model\" \"0\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"" + "\"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"" + "\"0\"\n\t\"$znearer\" \"0\"" +/**/ "\n\t\"$outline\" \"1\"\n\t\"$translucent\" \"1\"\n\t\"$distancealpha\" \"1\"\n\t\"$softedges\" \"1\"\n\t\"$edgesoftnessstart\" \".5\"\n\t\"$edgesoftnessend\" \".46\"\n\t\"$scaleedgesoftnessbasedonscreenres	\" \"1\"" /**/+  "\n\t\"$glow\" \"1\"\n\t\"$glowcolor\" \"[0 0 0]\"\n\t\"$glowalpha\" \".4\"\n\t\"$glowstart\" \".1\"\n\t\"$glowend\" \".5\"" + "\n\t\"$wireframe\" \"0\"\n\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n}\n";
		
		KeyValues* pKeyValues = new KeyValues(matname);
		U::InitKeyValues(pKeyValues, type.c_str());
		U::LoadFromBuffer(pKeyValues, matname, matdata.c_str());

		return pKeyValues;
	}

	IMaterial* CreateMat(const char* matname, bool flat, bool ignorez)
	{
		IMaterial* createdMaterial = Interface.MatSystem->CreateMaterial(matname, CreateKeyValue(matname, flat, ignorez));

		createdMaterial->IncrementReferenceCount();

		return createdMaterial;
	}

	void InitKeyValues(KeyValues* pKeyValues, const char* name)
	{
		using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);

		InitKeyValuesFn InitKeyValuesEx;
		InitKeyValuesEx = (InitKeyValuesFn)(Offsets.InitKeyValuesEx);
		InitKeyValuesEx(pKeyValues, name);
	}

	void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc)
	{
		using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);

		LoadFromBufferFn LoadFromBufferEx;
		LoadFromBufferEx = (LoadFromBufferFn)(Offsets.LoadFromBufferEx);
		LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
	}

	std::string GetWorkingPath()
	{
		char szPath[MAX_PATH];

		GetModuleFileNameA(0, szPath, MAX_PATH);

		std::string path(szPath);

		return path.substr(0, path.find_last_of("\\") + 1);
	}

	bool IsFileExists(const std::string& name)
	{
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	void ForceMaterial(IMaterial* material, float color[3])
	{
		if (material)
		{
			//material->AlphaModulate(color[3]);
			material->ColorModulate(color[0], color[1], color[2]);

			Interface.ModelRender->ForcedMaterialOverride(material);
		}
	}

	bool IsHeadshoted(IClientEntity* pLocal, Vector3& vecStart, Vector3& vecEnd)
	{
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		filter.pSkip = pLocal;

		ray.Init(vecStart, vecEnd);

		Interface.EngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

		return tr.hitbox == 6;
	}

	bool IsVisible(Vector3& vecAbsStart, Vector3& vecAbsEnd, IClientEntity* pLocal, IClientEntity* pBaseEnt, bool smokeCheck) throw()
	{
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		filter.pSkip = pLocal;

		ray.Init(vecAbsStart, vecAbsEnd);

		Interface.EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		bool visible = (tr.m_pEnt == pBaseEnt || tr.fraction >= 0.96f);

		if (visible && smokeCheck)
			visible = !LineGoesThroughSmoke(vecAbsStart, vecAbsEnd);

		return visible;
	}

	bool LineGoesThroughSmoke(Vector3 pos1, Vector3 pos2) throw()
	{
		typedef bool(*LineGoesThroughSmokeFn)(float, float, float, float, float, float, short);

		LineGoesThroughSmokeFn LineGoesThroughSmokeEx;
		LineGoesThroughSmokeEx = (LineGoesThroughSmokeFn)(Offsets.LineGoesThroughSmoke);
		return LineGoesThroughSmokeEx(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, 1);
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
		//const matrix3x4& worldToScreen = Interface.Engine->WorldToScreenMatrix();

		const matrix3x4& worldToScreen = *(matrix3x4*)(*(PDWORD)(Offsets.worldToScreen) + 988);
		if (!POINTERCHK(worldToScreen)) 
			return false;


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
			if (v[i] > 180.0f) v[i] -= 360.0f;
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

	Vector3 CalculateAngle(const Vector3& in, Vector3 out)
	{
		double delta[3] = { (in[0] - out[0]), (in[1] - out[1]), (in[2] - out[2]) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		Vector3 ret = Vector3();
		ret.x = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
		ret.y = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
		ret.z = 0.0f;

		if (delta[0] >= 0.0)
			ret.y += 180.0f;
		return ret;
		/*float pitch = U::Deg2Rad(in.x);
		float yaw = U::Deg2Rad(in.y);
		float temp = cos(pitch);
		Vector3 ret = Vector3();

		ret.x = -temp * -cos(yaw);
		ret.y = sin(yaw) * temp;
		ret.z = -sin(pitch);
		return ret;*/
	}

	Vector2 RotatePoint(Vector3 EntityPos, Vector3 LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck, bool angleInRadians)
	{
		float r_1, r_2;
		float x_1, y_1;

		r_1 = -(EntityPos.y - LocalPlayerPos.y);
		r_2 = EntityPos.x - LocalPlayerPos.x;
		float Yaw = angle - 90.0f;

		float yawToRadian = Yaw * (float)(M_PI/ 180.0F);
		x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
		y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

		*viewCheck = y_1 < 0;

		x_1 *= zoom;
		y_1 *= zoom;

		int sizX = sizeX / 2;
		int sizY = sizeY / 2;

		x_1 += sizX;
		y_1 += sizY;

		if (x_1 < 5)
			x_1 = 5;

		if (x_1 > sizeX - 5)
			x_1 = sizeX - 5;

		if (y_1 < 5)
			y_1 = 5;

		if (y_1 > sizeY - 5)
			y_1 = sizeY - 5;


		x_1 += posX;
		y_1 += posY;


		return Vector2(x_1, y_1);


		/*if (!angleInRadians)
			angle = (float)(angle * (M_PI / 180));
		float cosTheta = (float)cos(angle);
		float sinTheta = (float)sin(angle);
		Vector2 returnVec = Vector2(
			cosTheta * (pointToRotate.x - centerPoint.x) - sinTheta * (pointToRotate.y - centerPoint.y),
			sinTheta * (pointToRotate.x - centerPoint.x) + cosTheta * (pointToRotate.y - centerPoint.y)
		);
		returnVec += centerPoint;
		return returnVec / zoom;*/
	}

	bool CanShoot(CPlayer* pLocalPlayer, CBaseWeapon* weapon)
	{
		if (!weapon)
			return false;

		if (IsNonAimWeapon(weapon->GetItemDefinitionIndex()))
			return false;

		if (weapon->ClipAmmo() < 1)
			return false;

		/*if (weapon->InReload())
			return false;*/

		float server_time = pLocalPlayer->TickBase() * Interface.Globals->interval_per_tick;

		float next_shot = weapon->NextPrimaryAttack() - server_time;
		if (next_shot > 0)
			return false;

		return true;
	}

	void LoadKnifeModels()
	{
		KnifeModels.DefaultTT = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_default_t.mdl"));
		KnifeModels.DefaultCT = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_default_ct.mdl"));

		KnifeModels.Bayonet = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_bayonet.mdl"));
		KnifeModels.M9Bayonet = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_m9_bay.mdl"));
		KnifeModels.Butterfly = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_butterfly.mdl"));
		KnifeModels.Flip = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_flip.mdl"));
		KnifeModels.GunGame = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_gg.mdl"));
		KnifeModels.Gut = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_gut.mdl"));
		KnifeModels.Karambit = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_karam.mdl"));
		KnifeModels.Huntsman = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_tactical.mdl"));
		KnifeModels.Bowie = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_survival_bowie.mdl"));
		KnifeModels.Falchion = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_falchion_advanced.mdl"));
		KnifeModels.Dagger = Interface.ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_push.mdl"));
	}

	void FullUpdate()
	{
		/*ConVar* Meme = Interface.CVar->FindVar("cl_fullupdate");
		Meme->nFlags &= ~(1 << 14);

		Interface.Engine->ExecuteConsoleCommand("cl_fullupdate");*/

		typedef void(*CL_FullUpdate_t) (void);

		CL_FullUpdate_t cl_fullupdate = (CL_FullUpdate_t)(Offsets.FullUpdate);
		cl_fullupdate();

		//(Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer()))->GetWearables()[0] = 0;

		/*ConVar *cl_fullupdate = Interface.CVar->FindVar(XorStr("cl_fullupdate"));
		cl_fullupdate->nFlags &= ~(1 << 14);

		Interface.Engine->ExecuteConsoleCommand(XorStr("cl_fullupdate"));*/
	}

	const char* GetKillIconWeapon(int si)
	{
		// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
		switch (si)
		{
		case 0:
			return "bayonet";
		case 1:
			return "knife_flip";
		case 2:
			return "knife_gut";
		case 3:
			return "knife_karambit";
		case 4:
			return "knife_m9_bayonet";
		case 5:
			return "knife_tactical";
		case 6:
			return "knife_falchion";
		case 7:
			return "knife_survival_bowie";
		case 8:
			return "knife_butterfly";
		case 9:
			return "knife_push";
		default:
			NULL;
		}
	}

	int GetKnifeDefinitionIndex(int si)
	{
		// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
		switch (si)
		{
		case 0:
			return 500;
		case 1:
			return 505;
		case 2:
			return 506;
		case 3:
			return 507;
		case 4:
			return 508;
		case 5:
			return 509;
		case 6:
			return 512;
		case 7:
			return 514;
		case 8:
			return 515;
		case 9:
			return 516;
		default:
			return -1;
		}
	}

	int GetGloveSkinByMenu(int gloveIndex, int skinIndex)
	{
		if (gloveIndex == 0) // bloudhound
		{
			switch (skinIndex)
			{
			case 0:
				return 10006;
			case 1:
				return 10007;
			case 2:
				return 10008;
			case 3:
				return 10039;
			default:
				return 0;
			}
		}
		else if (gloveIndex == 1) // Sport
		{
			switch (skinIndex)
			{
			case 0:
				return 10038;
			case 1:
				return 10037;
			case 2:
				return 10018;
			case 3:
				return 10019;
			default:
				return 0;
			}
		}
		else if (gloveIndex == 2) // Driver
		{
			switch (skinIndex)
			{
			case 0:
				return 10013;
			case 1:
				return 10015;
			case 2:
				return 10016;
			case 3:
				return 10040;
			default:
				return 0;
			}
		}
		else if (gloveIndex == 3) // Wraps
		{
			switch (skinIndex)
			{
			case 0:
				return 10009;
			case 1:
				return 10010;
			case 2:
				return 10021;
			case 3:
				return 10036;
			default:
				return 0;
			}
		}
		else if (gloveIndex == 4) // Moto
		{
			switch (skinIndex)
			{
			case 0:
				return 10024;
			case 1:
				return 10026;
			case 2:
				return 10027;
			case 3:
				return 10028;
			default:
				return 0;
			}
		}
		else if (gloveIndex == 5) // Specialist
		{
			switch (skinIndex)
			{
			case 0:
				return 10030;
			case 1:
				return 10033;
			case 2:
				return 10034;
			case 3:
				return 10035;
			default:
				return 0;
			}
		}
		else
			return 0;
	}

	char* GetConfigName(int weaponid)
	{
		switch (weaponid)
		{
		case WEAPON_DEAGLE:
			return "deagle";
		case WEAPON_ELITE:
			return "elite";
		case WEAPON_FIVESEVEN:
			return "fiveseven";
		case WEAPON_GLOCK:
			return "glock18";
		case WEAPON_AK47:
			return "ak47";
		case WEAPON_AUG:
			return "aug";
		case WEAPON_AWP:
			return "awp";
		case WEAPON_FAMAS:
			return "famas";
		case WEAPON_G3SG1:
			return "g3sg1";
		case WEAPON_GALILAR:
			return "galil";
		case WEAPON_M249:
			return "m249";
		case WEAPON_M4A1:
			return "m4a4";
		case WEAPON_MAC10:
			return "mac10";
		case WEAPON_P90:
			return "p90";
		case WEAPON_UMP45:
			return "ump45";
		case WEAPON_XM1014:
			return "xm1014";
		case WEAPON_BIZON:
			return "bizon";
		case WEAPON_MAG7:
			return "mag7";
		case WEAPON_NEGEV:
			return "negev";
		case WEAPON_SAWEDOFF:
			return "sawedoff";
		case WEAPON_TEC9:
			return "tec9";
		case WEAPON_HKP2000:
			return "p2000";
		case WEAPON_MP7:
			return "mp7";
		case WEAPON_MP9:
			return "mp9";
		case WEAPON_NOVA:
			return "nova";
		case WEAPON_P250:
			return "p250";
		case WEAPON_SCAR20:
			return "scar20";
		case WEAPON_SG556:
			return "sg556";
		case WEAPON_SSG08:
			return "ssg08";
		case WEAPON_M4A1_SILENCER:
			return "m4a1s";
		case WEAPON_USP_SILENCER:
			return "usps";
		case WEAPON_CZ75A:
			return "cz75a";
		case WEAPON_R8REVOLVER:
			return "revolver";
		case WEAPON_KNIFE_BAYONET:
			return "knife_bayonet";
		case WEAPON_KNIFE_FLIP:
			return "knife_flip";
		case WEAPON_KNIFE_GUT:
			return "knife_gut";
		case WEAPON_KNIFE_KARAMBIT:
			return "knife_karambit";
		case WEAPON_KNIFE_M9_BAYONET:
			return "knife_m9";
		case WEAPON_KNIFE_TACTICAL:
			return "knife_huntsman";
		case WEAPON_KNIFE_FALCHION:
			return "knife_falchion";
		case WEAPON_KNIFE_BUTTERFLY:
			return "knife_butterfly";
		case WEAPON_KNIFE_PUSH:
			return "knife_bowie";
		default:
			return "";
		}
		return "";
	}

	const char* GetWeaponNameById(int id)
	{
		switch (id)
		{
		case 1:
			return "deagle";
		case 2:
			return "elite";
		case 3:
			return "fiveseven";
		case 4:
			return "glock";
		case 7:
			return "ak47";
		case 8:
			return "aug";
		case 9:
			return "awp";
		case 10:
			return "famas";
		case 11:
			return "g3sg1";
		case 13:
			return "galilar";
		case 14:
			return "m249";
		case 60:
			return "m4a1_silencer";
		case 16:
			return "m4a1";
		case 17:
			return "mac10";
		case 19:
			return "p90";
		case 24:
			return "ump45";
		case 25:
			return "xm1014";
		case 26:
			return "bizon";
		case 27:
			return "mag7";
		case 28:
			return "negev";
		case 29:
			return "sawedoff";
		case 30:
			return "tec9";
		case 32:
			return "hkp2000";
		case 33:
			return "mp7";
		case 34:
			return "mp9";
		case 35:
			return "nova";
		case 36:
			return "p250";
		case 38:
			return "scar20";
		case 39:
			return "sg556";
		case 40:
			return "ssg08";
		case 61:
			return "usp_silencer";
		case 63:
			return "cz75a";
		case 64:
			return "revolver";
		case 508:
			return "knife_m9_bayonet";
		case 500:
			return "bayonet";
		case 505:
			return "knife_flip";
		case 506:
			return "knife_gut";
		case 507:
			return "knife_karambit";
		case 509:
			return "knife_tactical";
		case 512:
			return "knife_falchion";
		case 514:
			return "knife_survival_bowie";
		case 515:
			return "knife_butterfly";
		case 516:
			return "knife_push";

		default:
			return "";
		}
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
		if (weaponid == WEAPON_KNIFE || weaponid == WEAPON_KNIFE_T || weaponid == WEAPON_KNIFEGG || weaponid == WEAPON_KNIFE_BAYONET || weaponid == WEAPON_KNIFE_BUTTERFLY || weaponid == WEAPON_KNIFE_FALCHION || weaponid == WEAPON_KNIFE_FLIP || weaponid == WEAPON_KNIFE_GUT || weaponid == WEAPON_KNIFE_KARAMBIT || weaponid == WEAPON_KNIFE_M9_BAYONET || weaponid == WEAPON_KNIFE_PUSH || weaponid == WEAPON_KNIFE_BOWIE || weaponid == WEAPON_KNIFE_TACTICAL)
			return true;

		return false;
	}

	bool IsWeaponDefaultKnife(int weaponid)
	{
		if (weaponid == WEAPON_KNIFE || weaponid == WEAPON_KNIFE_T)
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

	bool IsModelKnife(int modelIndex)
	{
		return (modelIndex == KnifeModels.DefaultCT ||
			modelIndex == KnifeModels.DefaultTT ||
			modelIndex == KnifeModels.Bayonet ||
			modelIndex == KnifeModels.Bowie ||
			modelIndex == KnifeModels.Butterfly ||
			modelIndex == KnifeModels.Dagger ||
			modelIndex == KnifeModels.Falchion ||
			modelIndex == KnifeModels.Flip ||
			modelIndex == KnifeModels.GunGame ||
			modelIndex == KnifeModels.Gut ||
			modelIndex == KnifeModels.Huntsman ||
			modelIndex == KnifeModels.Karambit ||
			modelIndex == KnifeModels.M9Bayonet);
	}

	bool IsModelDefaultKnife(int modelIndex, int currentKnifeIndex)
	{
		return modelIndex == KnifeModels.DefaultCT ||
			modelIndex == KnifeModels.DefaultTT ||
			(modelIndex != currentKnifeIndex && IsModelKnife(modelIndex));
	}

	const char* GetModelByIndex(int id)
	{
		switch (id)
		{
		case 506:
			return "models/weapons/v_knife_gut.mdl";
		case 505:
			return "models/weapons/v_knife_flip.mdl";
		case 500:
			return "models/weapons/v_knife_bayonet.mdl";
		case 508:
			return "models/weapons/v_knife_m9_bay.mdl";
		case 507:
			return "models/weapons/v_knife_karam.mdl";
		case 509:
			return "models/weapons/v_knife_tactical.mdl";
		case 515:
			return "models/weapons/v_knife_butterfly.mdl";
		case 514:
			return "models/weapons/v_knife_survival_bowie.mdl";
		case 512:
			return "models/weapons/v_knife_falchion_advanced.mdl";
		case 516:
			return "models/weapons/v_knife_push.mdl";
		case 5027:
			return "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl";
		case 5030:
			return "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl";
		case 5031:
			return "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl";
		case 5032:
			return "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl";
		case 5033:
			return "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl";
		case 5034:
			return "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl";
		default:
			return NULL;
		}
	}

	int GetCurrentKnifeModel(int currentKnife)
	{
		// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
		switch (currentKnife)
		{
		case 0:
			return KnifeModels.Bayonet;
		case 1:
			return KnifeModels.Flip;
		case 2:
			return KnifeModels.Gut;
		case 3:
			return KnifeModels.Karambit;
		case 4:
			return KnifeModels.M9Bayonet;
		case 5:
			return KnifeModels.Huntsman;
		case 6:
			return KnifeModels.Falchion;
		case 7:
			return KnifeModels.Bowie;
		case 8:
			return KnifeModels.Butterfly;
		case 9:
			return KnifeModels.Dagger;
		case 10:
			return KnifeModels.GunGame;
		default:
			return 0;
		}
	}
}