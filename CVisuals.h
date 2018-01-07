#pragma once

namespace CVisuals
{
	// Rendering
	std::string tWeapName;

	bool isDrop(IClientEntity* pBaseEntity) throw()
	{
		if (strstr(pBaseEntity->GetClientClass()->szName, XorStr("CWeapon")))
		{
			tWeapName = std::string(pBaseEntity->GetClientClass()->szName).substr(7);
			return true;
		}
		if (strcmp(pBaseEntity->GetClientClass()->szName, XorStr("CAK47")) == 0)
		{
			tWeapName = XorStr("AK47");
			return true;
		}
		if (strcmp(pBaseEntity->GetClientClass()->szName, XorStr("CDEagle")) == 0)
		{
			tWeapName = XorStr("Deagle");
			return true;
		}
		if (strcmp(pBaseEntity->GetClientClass()->szName, XorStr("CKnife")) == 0)
		{
			tWeapName = XorStr("Knife");
			return true;
		}
		if (strcmp(pBaseEntity->GetClientClass()->szName, XorStr("CC4")) == 0)
		{
			tWeapName = XorStr("C4");
			return true;
		}

		return false;
	}

	void DrawStringO(float x, float y, Color clr, bool centeredX, bool centeredY, bool outline, float fontSize, const char* format, ...)
	{
		static const auto MAX_BUFFER_SIZE = 1024;
		static char buffer[MAX_BUFFER_SIZE] = "";

		auto font = _fonts.Fonts[0];

		_drawList->PushTextureID(_fonts.TexID);

		va_list va;
		va_start(va, format);
		vsnprintf_s(buffer, MAX_BUFFER_SIZE, format, va);
		va_end(va);

		float fSize = fontSize == 0 ? font->FontSize : fontSize;

		if (centeredX || centeredY) {
			auto text_size = font->CalcTextSizeA(fSize, FLT_MAX, 0.0f, buffer);
			if (centeredX)
				x -= text_size.x / 2;
			if (centeredY)
				y -= text_size.y / 2;
		}

		/*
		if (outline) {
			int w = 1;
			_drawList->AddText(font, fSize, ImVec2{ x - w, y - w }, 0xFF000000, buffer);
			_drawList->AddText(font, fSize, ImVec2{ x + w, y }, 0xFF000000, buffer);
			_drawList->AddText(font, fSize, ImVec2{ x    , y + w }, 0xFF000000, buffer);
			_drawList->AddText(font, fSize, ImVec2{ x - w, y }, 0xFF000000, buffer);
		}
		*/

		_drawList->AddText(font, fSize, ImVec2(x, y), clr.GetU32(), buffer);
		_drawList->PopTextureID();
	}

	void DrawString(float x, float y, Color clr, bool centeredX, bool centeredY, bool outline, const char* format, ...)
	{
		DrawStringO(x, y, clr, centeredX, centeredY, outline, 0, format);
	}

	void DrawString(float x, float y, Color clr, const char* format, ...)
	{
		DrawString(x, y, clr, false, false, false, format);
	}

	void W2SdrawString(Vector3 vec, const char* str)
	{
		Vector3 screenPos;
		if (U::WorldToScreen(vec, screenPos))
			DrawString(screenPos.x, screenPos.y, Color::White(), true, true, true, str);
	}

	void DrawLine(int x1, int y1, int x2, int y2, Color clr, float thickness = 1.0f)
	{
		_drawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr.GetU32(), thickness);
	}

	void DrawEspBox(Vector3 leftUpCorn, Vector3 rightDownCorn, Color clr, float width)
	{
		ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
		ImVec2 max = ImVec2(rightDownCorn.x, rightDownCorn.y);
		_drawList->AddRect(min, max, clr.GetU32(), 0.0F, -1, width);
	}

	void DrawCorner(Vector3 leftUpCorn, Vector3 rightUpCorn, Vector3 leftDownCorn, Vector3 rightDownCorn, Color clr, float width)
	{
		int edge = (rightUpCorn.x - leftUpCorn.x) / 3;

		_drawList->AddLine(ImVec2(rightUpCorn.x, rightUpCorn.y), ImVec2(rightUpCorn.x, rightUpCorn.y + edge), clr.GetU32(), width);
		_drawList->AddLine(ImVec2(rightUpCorn.x, rightUpCorn.y), ImVec2(rightUpCorn.x - edge, rightUpCorn.y), clr.GetU32(), width);
		_drawList->AddLine(ImVec2(leftUpCorn.x, leftUpCorn.y), ImVec2(leftUpCorn.x, leftUpCorn.y + edge), clr.GetU32(), width);
		_drawList->AddLine(ImVec2(leftUpCorn.x, leftUpCorn.y), ImVec2(leftUpCorn.x + edge, leftUpCorn.y), clr.GetU32(), width);
		_drawList->AddLine(ImVec2(rightDownCorn.x, rightDownCorn.y), ImVec2(rightDownCorn.x, rightDownCorn.y - edge), clr.GetU32(), width);
		_drawList->AddLine(ImVec2(rightDownCorn.x, rightDownCorn.y), ImVec2(rightDownCorn.x - edge, rightDownCorn.y), clr.GetU32(), width);
		_drawList->AddLine(ImVec2(leftDownCorn.x, leftDownCorn.y), ImVec2(leftDownCorn.x, leftDownCorn.y - edge), clr.GetU32(), width);
		_drawList->AddLine(ImVec2(leftDownCorn.x, leftDownCorn.y), ImVec2(leftDownCorn.x + edge, leftDownCorn.y), clr.GetU32(), width);
	}

	void DrawBonesList(CPlayer* pBaseEntity)
	{
		for (int i = 0; i < 128; i++)
		{
			Vector3 bonePos = pBaseEntity->GetBonePosition(i);
			if (bonePos.x == 0)
				continue;

			Vector3 screenPos;
			if (U::WorldToScreen(bonePos, screenPos))
				DrawStringO(screenPos.x, screenPos.y, Color::White(), true, true, true, 0, XorStr("%d"), i);
		}
	}
	struct ESPBox
	{
		int x, y, w, h;
	};
	void Helth1(CPlayer* pBaseEntity, ESPBox size)
	{
		ESPBox HealthBar = size;
		HealthBar.y += (HealthBar.h + 6);
		HealthBar.h = 4;

		float iClampedHealth = pBaseEntity->GetHealth();
		float HealthPerc = iClampedHealth / 100.f;
		float Width = (size.w * HealthPerc);
		HealthBar.w = Width;

		if (iClampedHealth >= 100)
			iClampedHealth = 100;

		int iHealthG = iClampedHealth * 2.55;
		int iHealthR = 255 - iHealthG;

		Color colHealth = Color(iHealthR, iHealthG, 0, 255);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 80, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 70, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 55, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 45, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 40, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 50, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 60, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 100, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 120, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 3, size.y + 1, size.w / 140, size.h * 0.01 * iClampedHealth + 0.5, colHealth);
		DrawLine(size.x + size.w + 2, size.y, (size.w / 40) + 2, size.h + 1, Color(0, 0, 0, 150));
	}
	//моя хуйня
	void DrawBoneESP(CPlayer* pBaseEntity, bool isEnemy, bool isVisibled, bool isVisibledSmoke) throw()
	{
		if (Options::Visuals::ESP::skilet);
		{
			model_t* pModel = pBaseEntity->GetClientRenderable()->GetModel();
			if (!pModel)
				return;

			studiohdr_t* pStudioMdl = Interface.ModelInfo->GetStudiomodel(pModel);
			if (!pStudioMdl)
				return;

			matrix3x4 matBones[128];
			if (!pBaseEntity->SetupBones(&matBones[0], 128, 256, Interface.Globals->curtime))
				return;

			for (int i = 0; i < pStudioMdl->numbones; i++) {
				mstudiobone_t* pBone = pStudioMdl->pBone(i);
				if (pBone && (pBone->flags & 0x100) && pBone->parent != -1) {
					Vector3 vecParentPos, vecChildPos;
					Vector3 vecParent, vecChild;
					MatrixPosition(matBones[i], vecChildPos);
					MatrixPosition(matBones[pBone->parent], vecParentPos);
					if (U::WorldToScreen(vecChildPos, vecChild) && U::WorldToScreen(vecParentPos, vecParent))
						DrawLine(vecChild.x, vecChild.y, vecParent.x, vecParent.y, Color::White(), 1);
				}
			}
		}
	}
	//cпасченая хуйня
	
	
	void DrawEsp(CPlayer* pBaseEntity, bool isEnemy, bool isVisibled, bool isVisibledSmoke) throw()
	{
		if (!pBaseEntity)
			return;

		if (Options::Visuals::ESP::EnemyOnly && !isEnemy)
			return;

		if (Options::Visuals::ESP::VisibleOnly && !isVisibled)
			return;
	

		if (Options::Visuals::ESP::SmokeCheck && !isVisibledSmoke)
			return;

		Vector3 m_vecFoot = pBaseEntity->GetOrigin();
		Vector3 m_vecHead;
		Vector3 m_screenFoot;
		Vector3 m_screenHead;

		if ((pBaseEntity->GetFlags() & FL_DUCKING))
			m_vecHead = m_vecFoot + Vector3(0.f, 0.f, 52.f);
		else m_vecHead = m_vecFoot + Vector3(0.f, 0.f, 72.f);

		m_vecFoot.z -= 6;
		m_vecHead.z += 6;

		if (U::WorldToScreen(m_vecFoot, m_screenFoot) &&
			U::WorldToScreen(m_vecHead, m_screenHead))
		{
			float lineHeight = (m_screenFoot.y - m_screenHead.y);
			int edgeWidth = lineHeight / 4;
			int lineWidth = edgeWidth;
			edgeWidth /= 1.5f;

			const float OUTLINE_WIDTH = 2.15;
			const float LINE_WIDTH = 0.5;

			Vector3 leftUpCorn = Vector3(m_screenFoot.x - lineWidth - LINE_WIDTH, m_screenHead.y, 0.f);
			Vector3 rightUpCorn = Vector3(m_screenFoot.x + lineWidth, m_screenHead.y, 0.f);
			Vector3 leftDownCorn = Vector3(m_screenFoot.x - lineWidth, m_screenFoot.y, 0.f);
			Vector3 rightDownCorn = Vector3(m_screenFoot.x + lineWidth, m_screenFoot.y, 0.f);

			if (Options::Visuals::ESP::Box)
			{
				//Color col = isVisibled ? Color(0, 255, 0) : Color::Blue();
				Color col = isVisibled ? Color(Options::Visuals::ESP::color_vis[0] * 255, Options::Visuals::ESP::color_vis[1] * 255, Options::Visuals::ESP::color_vis[2] * 255) : Color(Options::Visuals::ESP::color_invis[0] * 255, Options::Visuals::ESP::color_invis[1] * 255, Options::Visuals::ESP::color_invis[2] * 255);

				switch (Options::Visuals::ESP::Style)
				{
				case 1: // default w\ outline
				{
					DrawEspBox(leftUpCorn, rightDownCorn, Color::Black(), OUTLINE_WIDTH);
					DrawEspBox(leftUpCorn, rightDownCorn, col, LINE_WIDTH);
					break;
				}
				case 2: // corner
				{
					DrawCorner(leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, col, OUTLINE_WIDTH - 1);
					break;
				}
				case 3: // corner w\ outline
				{
					DrawCorner(leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, Color::Black(), OUTLINE_WIDTH);
					DrawCorner(leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, col, LINE_WIDTH);
					break;
				}
				case 4:
				case 5:
				case 6:
				{
					G::PlayersDrawList.push_back(pBaseEntity);
					break;
				}

				default:
				{
					DrawEspBox(leftUpCorn, rightDownCorn, col, OUTLINE_WIDTH - 1);
					break;
				}
				}
			}
			if (Options::Visuals::ESP::skilet)
				DrawBoneESP(pBaseEntity, isEnemy, isVisibled, isVisibledSmoke);
			if (Options::Visuals::Health::Health1)
			{
				switch (Options::Visuals::Health::Style)
				{
				case 0:
				{
					float pixelPerHp = lineHeight / 100.f;
			
					DrawLine(rightUpCorn.x + 6, rightUpCorn.y - 1, rightUpCorn.x + 6, rightDownCorn.y + 1, Color::Black(), 5);
					DrawLine(rightUpCorn.x + 6, rightUpCorn.y, rightUpCorn.x + 6, rightDownCorn.y, Color(0, 0, 0), 3);
					DrawLine(rightUpCorn.x + 6, rightUpCorn.y + ((pixelPerHp * (100 - pBaseEntity->GetHealth()))), rightUpCorn.x + 6, rightDownCorn.y, Color(Options::Visuals::Health::color[0] * 255, Options::Visuals::Health::color[1] * 255, Options::Visuals::Health::color[2] * 255), 3);
				}
				case 1:
				{
					//float pixelPerHp = lineHeight / 100.f;
				
				//	DrawString(rightUpCorn.x, rightUpCorn.y, Color(Options::Visuals::ESP::color_hpbar[0] * 255, Options::Visuals::ESP::color_hpbar[1] * 255, Options::Visuals::ESP::color_hpbar[2] * 255), true, true, true,    XorStr(" %d"), pBaseEntity->GetHealth());
				
				}
				
			  }

			}

			if (Options::Visuals::ESP::Name)
			{
				player_info_t pInfo;
				Interface.Engine->GetPlayerInfo(pBaseEntity->GetIndex(), &pInfo);

				DrawString(m_screenFoot.x, m_screenHead.y - 22, Color::White(), true, false, true, pInfo.name);
			}
			

			if (Options::Visuals::ESP::Weapon)
			{
				CBaseWeapon* weapon = pBaseEntity->GetWeap();
				if (weapon)
				{
					CCSWeaponInfo_t* data = weapon->GetWpnData();
					if (data)
					{
						std::string str = "";
						str += data->m_pszName;
						if (Options::Visuals::ESP::WeaponAmmo)
						{
							str += "(";
							str += std::to_string(weapon->ClipAmmo());
							str += ")";
						}
						DrawString(m_screenFoot.x, m_screenFoot.y + 1, Color::White(), true, false, true, str.c_str());
					}
				}
			}
		}
	}
	
	

	void DrawPlayers() throw()
	{
		CPlayer* pLocalEntity = Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer());
		if (!pLocalEntity)
			return;

		G::PlayersDrawList.clear();
		Vector3 LocalPosition = pLocalEntity->GetEyePosition();
		for (int i = 0; i < Interface.Engine->GetMaxClients(); i++) {
			CPlayer* pBaseEntity = Interface.EntityList->GetClientEntity<CPlayer>(i);

			if (!pBaseEntity)
				continue;
			if (!pBaseEntity->IsValid())
				continue; //GetWeapon;
			if (pBaseEntity == pLocalEntity)
				continue;

			bool isEnemy = pLocalEntity->GetTeam() != pBaseEntity->GetTeam();
			bool isVisibled = G::VisibledPlayers[i];/*U::IsVisible(LocalPosition, pBaseEntity->GetEyePosition(), pLocalEntity, pBaseEntity, false);*/ // CRASHING
			bool isVisibledSmoke = true; /*!U::LineGoesThroughSmoke(LocalPosition, pBaseEntity->GetEyePosition());*/

			//DrawBonesList(pBaseEntity);
			if (Options::Visuals::ESP::Enabled) DrawEsp(pBaseEntity, isEnemy, isVisibled, isVisibledSmoke);
			if (Options::Visuals::ESP::skilet)
				DrawBoneESP(pBaseEntity, isEnemy, isVisibled, isVisibledSmoke);
		//	DrawBoneESP(pBaseEntity, isEnemy, isVisibled, isVisibledSmoke);
		}
	}
	void DrawRecoil(CPlayer* pLocalEntity, CBaseWeapon* Weapon, int cw) throw()
	{
		int x = screenWidth / 2;
		int y = screenHeight / 2;
		int dy = screenHeight / 90;
		int dx = screenWidth / 90;
		Vector3 angle = pLocalEntity->GetPunchAngles();
		if (Options::Legitbot::DrawFov)
		{
			//Vector3 punchAngle = (angle / 2) * Vector3(weapons[cw].RCSAmountX, weapons[cw].RCSAmountY, 0);
			Vector3 punchAngle = (angle / 2) * Vector3(weapons[cw].RcsX / 50.f, weapons[cw].RcsY / 50.f, 0);
			ImVec2 pos = ImVec2(
				x - (dx*(punchAngle.y)),
				y + (dy*(punchAngle.x)));

			int fov = dy * (G::AllowSilent ? weapons[cw].pSilentFov : weapons[cw].Fov);
			_drawList->AddCircle(ImVec2(pos.x, pos.y), fov, Color::White().GetU32(), 25, 0.2f);
		}

		if (Options::Misc::RecoilCrosshair)
		{			
			ImVec2 pos = ImVec2(
				x - (dx*(angle.y / 2)),
				y + (dy*(angle.x)));

			int h = 2;
			_drawList->AddRectFilled(ImVec2(pos.x - h, pos.y - h), ImVec2(pos.x + h, pos.y + h), Color::Red().GetU32());
		}
	}

	void DrawSniperCrosshair(CPlayer* pLocalEntity, CBaseWeapon* Weapon, int cw) throw()
	{
		if (!Options::Misc::SniperCrosshair)
			return;

		int size = 8;
		int x = screenWidth / 2;
		int y = screenHeight / 2;
		_drawList->AddLine(ImVec2(x - size, y), ImVec2(x + size, y), Color::White().GetU32(), 2);
		_drawList->AddLine(ImVec2(x, y - size), ImVec2(x, y + size), Color::White().GetU32(), 2);
	}

	void DrawCrosshairs() throw()
	{
		CPlayer* pLocal = Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer());
		if (pLocal == nullptr || !pLocal->IsValid())
			return;

		CBaseWeapon* weap = pLocal->GetWeap();
		if (!weap)
			return;

		int cw = weap->GetItemDefinitionIndex();
		if (U::IsNonAimWeapon(cw))
			return;

		bool sniper = U::IsWeaponSniper(weap->GetItemDefinitionIndex());
		if (sniper) DrawSniperCrosshair(pLocal, weap, cw);
		else DrawRecoil(pLocal, weap, cw);
	}

	void DrawOther() throw()
	{
		CPlayer* pLocalEntity = Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer());
		if (!pLocalEntity)
			return;

		static bool lastBombDraw = false;
		bool foundedBomb = false;
		for (int i = 0; i < Interface.EntityList->GetHighestEntityIndex(); i++) {
			IClientEntity* pBaseEntity = Interface.EntityList->GetClientEntity<IClientEntity>(i);
			if (!pBaseEntity)
				continue;
			Vector3 pPos = pBaseEntity->GetOrigin();
			if (pPos.IsZero())
				continue;

			while (Options::Visuals::Misc::Grenades)
			{
				if (!pBaseEntity)
					break;

				Vector3 screenPos;
				if (U::WorldToScreen(pPos, screenPos))
				{
					if (strstr(pBaseEntity->GetClientClass()->szName, "CSmokeGrenadeProjectile"))
						DrawStringO(screenPos.x, screenPos.y, Color::White(), true, true, false, 10, "Smoke Grenade");

					if (strstr(pBaseEntity->GetClientClass()->szName, "CBaseCSGrenadeProjectile"))
						DrawStringO(screenPos.x, screenPos.y, Color::White(), true, true, false, 10, "Grenade");

					if (strstr(pBaseEntity->GetClientClass()->szName, "CMolotovProjectile"))
						DrawStringO(screenPos.x, screenPos.y, Color::White(), true, true, false, 10, "Molotov");

					if (strstr(pBaseEntity->GetClientClass()->szName, "CDecoyProjectile"))
						DrawStringO(screenPos.x, screenPos.y, Color::White(), true, true, false, 10, "Decoy");
				}
				break;
			}

			while (Options::Visuals::Misc::DropESP)
			{
				if (!isDrop(pBaseEntity))
					break;
				if (*(int*)((DWORD)pBaseEntity + 0x148) != -1)
					break;

				Vector3 screenPos;
				if (U::WorldToScreen(pPos, screenPos))
					DrawStringO(screenPos.x, screenPos.y, Color::White(),  true, true, true, 10, "%s (%d/%d)",
						tWeapName.c_str(), ((CBaseWeapon*)pBaseEntity)->ClipAmmo(),
						((CBaseWeapon*)pBaseEntity)->ClipAmmo2());

				break;
			}

			while (Options::Visuals::Misc::BombTimer)
			{
				if (pBaseEntity->GetClientClass()->iClassID != 108)
					break;

				float timeLeft = *(float*)((DWORD)pBaseEntity + NetVars.m_flC4Blow) - Interface.Globals->curtime;
				if (timeLeft < 0)
					timeLeft = 0;

				int btt = Options::Visuals::Misc::BombTimerType; // 0 - world; 1 - screen; 2 - both
				if (btt == 0 || btt == 2)
				{
					Vector3 screenPos;
					if (U::WorldToScreen(pPos, screenPos))
					{
						DrawStringO(screenPos.x, screenPos.y - 7, Color(Options::Visuals::ESP::colorbomb[0] * 255, Options::Visuals::ESP::colorbomb[1] * 255, Options::Visuals::ESP::colorbomb[2] * 255), true, false, true, 10, XorStr("Bomb"));
						DrawStringO(screenPos.x, screenPos.y + 2, Color(Options::Visuals::ESP::colorbomb[0] * 255, Options::Visuals::ESP::colorbomb[1] * 255, Options::Visuals::ESP::colorbomb[2] * 255), true, false, true, 10, XorStr("Time left: %.1f"),
							timeLeft);
					}
				}
				if (btt == 1 || btt == 2)
				{
					DrawStringO(20, screenHeight / 2, Color(Options::Visuals::ESP::colorbomb[0] * 255, Options::Visuals::ESP::colorbomb[1] * 255, Options::Visuals::ESP::colorbomb[2] * 255),  false, true, true, 0, XorStr("Bomb\nTime left: %.1f"),
						timeLeft);
				}

				if (!lastBombDraw)
				{
				//	Interface.DebugOverlay->AddBoxOverlay2(pPos, Vector3(-8, -8, -6), Vector3(8, 8, 6), Vector3(0, 0, 0), Color(255, 0, 0, 30), Color(255, 0, 0, 150), *(float*)((DWORD)pBaseEntity + NetVars.m_flTimerLength));
				}
				lastBombDraw = true;
				foundedBomb = true;

				break;
			}
		}
		if (!foundedBomb) lastBombDraw = false;
	}

	void Render() throw()
	{
		static RainbowColor copyrightColor = RainbowColor();

		if (Options::Misc::Watermark) DrawString(5, 5, copyrightColor.GetColor(), XorStr(""));

		if (Interface.Engine->IsInGame() && Interface.Engine->IsConnected() && !Interface.Engine->IsTakingScreenshot())
		{
			DrawPlayers();
			DrawCrosshairs();
			DrawOther();

			// hit info
			if (Options::Misc::HitInfo && CEvents::hurtTime + 0.5f >= Interface.Globals->curtime)
				DrawStringO(screenWidth / 2, screenHeight / 3, Color(10, 139, 245, 255), true, true, true, 12, XorStr("%d"), CEvents::hurtDamage);
		}
	}

	void RevealRanks()
	{
		using RevealRanksFn = bool(__cdecl*)(float*);

		RevealRanksFn RevealRanksEx;
		RevealRanksEx = (RevealRanksFn)(Offsets.RevealRanks);
		RevealRanksEx(new float[3]{ 0, 0, 0 });
	}
};