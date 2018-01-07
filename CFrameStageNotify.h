#pragma once

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF



enum class EStickerAttributeType
{
	Index,
	Wear,
	Scale,
	Rotation
};
DWORD dwEconItemInterfaceWrapper = 0;

typedef float(__thiscall* GetStickerAttributeBySlotIndexFloatFn)(void*, int, EStickerAttributeType, float);
GetStickerAttributeBySlotIndexFloatFn oGetStickerAttributeBySlotIndexFloat;
float __fastcall Hooked_GetStickerAttributeBySlotIndexFloat(void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, float flUnknown)
{
	auto pItem = reinterpret_cast<C_BaseAttributableItem*>(uintptr_t(thisptr) - dwEconItemInterfaceWrapper);
	if (!pItem)
		return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);

	int iID = *pItem->GetItemDefinitionIndex();
	if (!weapons[iID].StickersEnabled)
		return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);

	switch (iAttribute)
	{
	case EStickerAttributeType::Wear:
		return min(1.f, weapons[iID].Stickers[iSlot].flWear + 0.0000000001f);
	case EStickerAttributeType::Scale:
		return weapons[iID].Stickers[iSlot].flScale;
	case EStickerAttributeType::Rotation:
		return weapons[iID].Stickers[iSlot].iRotation;
	default:
		break;
	}

	return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);
}

typedef UINT(__thiscall* GetStickerAttributeBySlotIndexIntFn)(void*, int, EStickerAttributeType, float);
GetStickerAttributeBySlotIndexIntFn oGetStickerAttributeBySlotIndexInt;
UINT __fastcall Hooked_GetStickerAttributeBySlotIndexInt(void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, UINT iUnknown)
{
	auto pItem = reinterpret_cast<C_BaseAttributableItem*>(uintptr_t(thisptr) - dwEconItemInterfaceWrapper);
	if (!pItem)
		return oGetStickerAttributeBySlotIndexInt(thisptr, iSlot, iAttribute, iUnknown);

	int iID = *pItem->GetItemDefinitionIndex();
	if (!weapons[iID].StickersEnabled)
		return oGetStickerAttributeBySlotIndexInt(thisptr, iSlot, iAttribute, iUnknown);

	return weapons[iID].Stickers[iSlot].iID;
	// return Parser::Stickers.List[g_Weapons[iID].Stickers[iSlot].iID].iID; //
}
bool IsCodePtr(void* ptr)
{
	constexpr const DWORD protect_flags = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;

	MEMORY_BASIC_INFORMATION out;
	VirtualQuery(ptr, &out, sizeof out);

	return out.Type
		&& !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS))
		&& out.Protect & protect_flags;
}
void ApplyStickerHooks(C_BaseAttributableItem* pItem)
{
	if (!dwEconItemInterfaceWrapper)
		dwEconItemInterfaceWrapper = 0x2DB0 + 0xC;

	void**& vmt = *reinterpret_cast<void***>(uintptr_t(pItem) + dwEconItemInterfaceWrapper);

	static void** hooked_vmt = nullptr;
	if (!hooked_vmt)
	{
		size_t size = 0;

		while (IsCodePtr(vmt[size]))
			++size;

		hooked_vmt = new void*[size];
		memcpy(hooked_vmt, vmt, size * sizeof(void*));

		oGetStickerAttributeBySlotIndexFloat = (GetStickerAttributeBySlotIndexFloatFn)hooked_vmt[4];
		hooked_vmt[4] = reinterpret_cast<void*>(&Hooked_GetStickerAttributeBySlotIndexFloat);

		oGetStickerAttributeBySlotIndexInt = (GetStickerAttributeBySlotIndexIntFn)hooked_vmt[5];
		hooked_vmt[5] = reinterpret_cast<void*>(&Hooked_GetStickerAttributeBySlotIndexInt);
	}
	vmt = hooked_vmt;

}

namespace CFrameStageNotify
{
	void DLights()
	{
		CPlayer* pLocalEntity = G::GlobalLocalPlayer_r;
		for (int i = 0; i < Interface.EntityList->GetHighestEntityIndex(); i++)
		{
			CPlayer *pEntity = Interface.EntityList->GetClientEntity<CPlayer>(i);
			player_info_t pinfo;

			if (pLocalEntity)
			{
				if (Interface.Engine->GetPlayerInfo(i, &pinfo) && pEntity->GetHealth() > 1 && !pEntity->GetDormant())
				{
					float rad = 800;
					dlight_t* pElight = Interface.Dilight->CL_AllocElight(i);
					pElight->origin = pEntity->GetOrigin() + Vector3(0.0f, 0.0f, 35.0f);
					pElight->radius = rad;
					pElight->color.r = Options::Visuals::ESP::color_dlight[0] * 255;
					pElight->color.g = Options::Visuals::ESP::color_dlight[1] * 255;
					pElight->color.b = Options::Visuals::ESP::color_dlight[2] * 255;
					pElight->die = Interface.Globals->curtime + 0.05f;
					pElight->decay = pElight->radius / 5.0f;
					pElight->key = i;

					dlight_t* pDlight = Interface.Dilight->CL_AllocDlight(i);
					pDlight->origin = pEntity->GetOrigin();
					pDlight->radius = rad;
					pDlight->color.r = Options::Visuals::ESP::color_dlight[0] * 255;
					pDlight->color.g = Options::Visuals::ESP::color_dlight[1] * 255;
					pDlight->color.b = Options::Visuals::ESP::color_dlight[2] * 255;
					pDlight->die = Interface.Globals->curtime + 0.05f;
					pDlight->decay = pDlight->radius; // / 5.0f;
					pDlight->key = i;
				}
			}
		}
	}

	void __stdcall Run(ClientFrameStage_t stage)
	{
		int LocalPlayerID = Interface.Engine->GetLocalPlayer();
		CPlayer* pLocalPlayer = Interface.EntityList->GetClientEntity<CPlayer>(LocalPlayerID);

		if (!pLocalPlayer || pLocalPlayer->GetHealth() <= 0)
			return O::FrameStageNotify(stage);

		// 3D Boxes
		while (stage == FRAME_RENDER_START)
		{
			if (!Options::Visuals::ESP::Enabled)
				break;

			if (Options::Visuals::ESP::Lights)
				DLights();

			for (int i = 0; i < G::PlayersDrawList.size(); i++)
			{
				CPlayer* pBasePlayer = G::PlayersDrawList[i];
				if (!pBasePlayer)
					continue;

				if (!pBasePlayer->IsValid())
					continue;

				Vector3 max = Vector3();
				if ((pBasePlayer->GetFlags() & FL_DUCKING))
					max = Vector3(20.f, 20.f, 52.f);
				else max = Vector3(20.f, 20.f, 72.f);

				bool isVisibled = G::VisibledPlayers[i];//U::IsVisible(pLocalPlayer->GetEyePosition(), pBasePlayer->GetEyePosition(), pLocalPlayer, pBasePlayer, Options::Visuals::ESP::SmokeCheck);
				Color col = isVisibled ? Color(0, 255, 0, 60) : Color::Blue(120);

				// "Default\0Default outlined\0Corner\0Corner outlined\0\r3D\0\r3D filled\0\r3D filled outline\0\0"

				switch (Options::Visuals::ESP::Style)
				{
				case 4:
				{
					Interface.DebugOverlay->AddBoxOverlay2(pBasePlayer->GetOrigin(), Vector3(-20.f, -20.f, 0), max, Vector3(0, 0, 0), Color(0, 0, 0, 0), col, 0);
					break;
				}
				case 5:
				{
					Interface.DebugOverlay->AddBoxOverlay2(pBasePlayer->GetOrigin(), Vector3(-20.f, -20.f, 0), max, Vector3(0, 0, 0), col, Color(0, 0, 0, 0), 0);
					break;
				}
				case 6:
				{
					Interface.DebugOverlay->AddBoxOverlay2(pBasePlayer->GetOrigin(), Vector3(-20.f, -20.f, 0), max, Vector3(0, 0, 0), col, Color::White(), 0);
					break;
				}
				default:
					break;
				case 7:
				{
					Interface.DebugOverlay->AddBoxOverlay2(pBasePlayer->GetOrigin(), Vector3(-5.f, -5.f, 0), max, Vector3(0, 0, 0), col, Color::White(), 0);
					break;
				}
				}
				//Interface.DebugOverlay->AddBoxOverlay2(pBasePlayer->GetOrigin(), Vector3(-20.f, -20.f, 0), max, Vector3(0, 0, 0), col, Color::White(), 0);
			}

			break;
		}

		// Glove Changer
		while (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			if (!Options::SkinChanger::EnabledGlove)
				break;

			auto hWearables = pLocalPlayer->GetWearables();
			if (!Interface.EntityList->GetClientEntityFromHandle(hWearables[0]))
			{
				static ClientClass* pClass;

				if (!pClass)
					pClass = Interface.Client->GetAllClasses();
				while (pClass)
				{
					if (pClass->iClassID == CEconWearable)
						break;
					pClass = pClass->pNextClass;
				}

				int iEntry, iSerial;

				pClass->m_pCreateFn(iEntry = (Interface.EntityList->GetHighestEntityIndex() + 1), iSerial = (RandomInt(0x0, 0xFFF)));
				hWearables[0] = iEntry | (iSerial << 16);

				C_BaseAttributableItem* glove = Interface.EntityList->GetClientEntity<C_BaseAttributableItem>(hWearables[0] & 0xFFF);
				if (glove)
				{
					player_info_t localplayer_info;
					Interface.Engine->GetPlayerInfo(Interface.Engine->GetLocalPlayer(), &localplayer_info);

					int gi = Options::SkinChanger::Glove;
					*glove->GetItemDefinitionIndex() = (gi == 0 ? 5027 : 5030 + (gi - 1)); 
					*glove->GetItemIDHigh() = -1;
					*glove->GetEntityQuality() = 4;
					*glove->GetAccountID() = localplayer_info.xuidlow;
					*glove->GetFallbackWear() = 0.00000001f;
					*glove->GetFallbackSeed() = 0;
					*glove->GetFallbackStatTrak() = -1;
					*glove->GetFallbackPaintKit() = U::GetGloveSkinByMenu(Options::SkinChanger::Glove, Options::SkinChanger::GloveSkin);
					((IClientEntity*)glove)->SetModelIndexVirtual(Interface.ModelInfo->GetModelIndex(U::GetModelByIndex(*glove->GetItemDefinitionIndex())));
					((IClientNetworkable*)glove)->PreDataUpdate(0);
				}
			}
			break;
		}

		// No Flash
		while (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			float* maxAlpha = pLocalPlayer->GetFlashMaxAlpha();

			if (Options::Misc::NoFlash)
				*maxAlpha = Options::Misc::NoFlashAlpha;
			else
				*maxAlpha = 255.f;

			break;
		}

		// Skin/Knife Changer
		while (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			player_info_t localPlayerInfo;
			if (!Interface.Engine->GetPlayerInfo(Interface.Engine->GetLocalPlayer(), &localPlayerInfo))
				break;

			int* hweapons = pLocalPlayer->GetWeapons();
			if (!hweapons)
				break;
			
			for (int i = 0; hweapons[i] != INVALID_EHANDLE_INDEX; i++)
			{
				C_BaseAttributableItem* weapon = Interface.EntityList->GetClientEntity<C_BaseAttributableItem>(hweapons[i] & 0xFFF);
				if (!weapon)
					continue;

				int* cw = weapon->GetItemDefinitionIndex();

				*weapon->GetItemIDHigh() = -1;
				while (Options::SkinChanger::EnabledKnife)
				{
					if (!U::IsWeaponKnife(*cw))
						break;

					if (!U::IsWeaponDefaultKnife(*cw))
						break;

					int si = U::GetKnifeDefinitionIndex(Options::SkinChanger::Knife);
					if (si != -1)
					{
						*weapon->GetEntityQuality() = 3;
						*cw = si;
					}

					break;
				}

				if (localPlayerInfo.xuidlow != *weapon->GetOriginalOwnerXuidLow())
					continue;

				if (localPlayerInfo.xuidhigh != *weapon->GetOriginalOwnerXuidHigh())
					continue;

				if (!weapons[*cw].ChangerEnabled)
					continue;

				if (U::IsWeaponKnife(*cw)) ((IClientEntity*)weapon)->SetModelIndex(U::GetCurrentKnifeModel(Options::SkinChanger::Knife));
				//((IClientEntity*)weapon)->SetModelIndex(Interface.ModelInfo->GetModelIndex(ItemDefinitionIndex.at(*cw).model));
				*weapon->GetAccountID() = localPlayerInfo.xuidlow;
				*weapon->GetFallbackPaintKit() = weapons[*cw].ChangerSkin;
				*weapon->GetFallbackWear() = min(1.f, weapons[*cw].ChangerWear + 0.0000000001f);
				*weapon->GetFallbackSeed() = weapons[*cw].ChangerSeed;

				if (weapons[*cw].ChangerStatTrak > 0)
				{
					*weapon->GetFallbackStatTrak() = weapons[*cw].ChangerStatTrak;
				}

				if (weapons[*cw].ChangerName)
					snprintf(weapon->GetCustomName(), 32, "%s", weapons[*cw].ChangerName);

				ApplyStickerHooks(weapon);

			}

			int cw = pLocalPlayer->GetWeap()->GetItemDefinitionIndex();

			if (!U::IsWeaponKnife(cw))
				break;

			if (!Options::SkinChanger::EnabledKnife)
				break;

			CBaseHandle hViewModel = *reinterpret_cast<CBaseHandle*>(uintptr_t(pLocalPlayer) + 0x32DC); // TODO: Delete offset
			if (hViewModel == INVALID_EHANDLE_INDEX)
				break;

			C_BaseAttributableItem* pViewModel = (C_BaseAttributableItem*)Interface.EntityList->GetClientEntityFromHandle((DWORD)hViewModel);
			((IClientEntity*)pViewModel)->SetModelIndex(U::GetCurrentKnifeModel(Options::SkinChanger::Knife));

			break;
		}
		return O::FrameStageNotify(stage);
	}
}