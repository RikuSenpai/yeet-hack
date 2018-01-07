#pragma once

namespace CLegitBot
{
	CBaseWeapon* Weapon;
	int WeaponID;
	CUserCmd* cmd;
	int m_nBestIndex = -1;
	int m_nBestBone;
	Vector3 m_nAngle;
	CPlayer* m_nLastBestEntity;
	CPlayer* m_nBestEntity;
	CPlayer* pLocalEntity;
	bool lastShooting;

	void MakeVector(const Vector3& vIn, Vector3& vOut)
	{
		float pitch = U::Deg2Rad(vIn.x);
		float yaw = U::Deg2Rad(vIn.y);
		float temp = cos(pitch);

		vOut.x = -temp * -cos(yaw);
		vOut.y = sin(yaw) * temp;
		vOut.z = -sin(pitch);
	}

	float GetFOV(Vector3& viewangles, const Vector3& vSrc, const Vector3& vEnd) // TODO: Remove additional  U::CalculateAngle
	{
		Vector3 delta = U::CalculateAngle(vSrc, vEnd) - viewangles;
		U::AngleNormalize(delta);

		return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));

		/*Vector3 vAng, vAim;

		vAng = U::CalculateAngle(vSrc, vEnd);
		MakeVector(viewangles, vAim);
		MakeVector(vAng, vAng);

		return U::Rad2Deg(acos(vAim.Dot(vAng)) / vAim.LengthSqr());*/
	}

	Vector3 CurveSmooth(Vector3& viewangles, Vector3 target, float factor)
	{
		factor *= 10;

		if (factor <= 0.0f)
			return target;

		Vector3 delta = target - viewangles;
		U::ClampAngles(delta);

		float factorx = factor, factory = factor;

		if (delta.x < 0.0f)
		{
			if (factorx > fabs(delta.x))
				factorx = fabs(delta.x);

			target.x = viewangles.x - factorx;
		}
		else
		{
			if (factorx > delta.x)
				factorx = delta.x;

			target.x = viewangles.x + factorx;
		}

		if (delta.y < 0.0f)
		{
			if (factory > fabs(delta.y))
				factory = fabs(delta.y);

			target.y = viewangles.y - factory;
		}
		else
		{
			if (factory > delta.y)
				factory = delta.y;

			target.y = viewangles.y + factory;
		}

		return target;
	}

	Vector3 Smooth(Vector3& viewangles, Vector3 target, float factor)
	{
		factor /= 10.f;

		Vector3 delta = target - viewangles;
		U::ClampAngles(delta);

		float smooth = powf(factor, 0.4f);

		smooth = min(0.99f, smooth);

		Vector3 toChange = Vector3(0.f, 0.f, 0.f);

		if (Options::Legitbot::AimType == 0)
		{
			toChange = delta - delta * smooth;
		}
		else
		{
			float coeff = fabsf(smooth - 1.f) / delta.Length() * 4.f;
			coeff = min(1.f, coeff);
			toChange = (delta * coeff);
		}

		return viewangles + toChange;
	}

	bool GetBestTarget(Vector3 myAng, bool allowSilent)
	{
		float bestFov = FLT_MAX;
		for (int i = 0; i < Interface.Engine->GetMaxClients(); i++)
		{
			CPlayer* pBaseEntity = Interface.EntityList->GetClientEntity<CPlayer>(i);
			if (!pBaseEntity)
				continue;
			if (!pBaseEntity->IsValid())
				continue;
			if (pBaseEntity == pLocalEntity)
				continue;
			if (!U::IsVisible(pLocalEntity->GetEyePosition(), pBaseEntity->GetEyePosition(), pLocalEntity, pBaseEntity, Options::Legitbot::SmokeCheck))
				continue;
			if (!Options::Legitbot::Deathmatch && pBaseEntity->GetTeam() == pLocalEntity->GetTeam())
				continue;

			Vector3 vSrc = pLocalEntity->GetEyePosition();
			Vector3 vEnd = pBaseEntity->GetEyePosition();

			float fov = GetFOV(myAng, vSrc, vEnd);
			if (fov < bestFov)
			{
				bestFov = fov;
				m_nBestIndex = i;
				m_nBestEntity = pBaseEntity;
			}
		}

		return m_nBestIndex != -1;
	}

	bool GetBestBone(Vector3 myAng, bool allowSilent)
	{
		float bestFov = allowSilent ? weapons[WeaponID].pSilentFov : weapons[WeaponID].Fov;

		if (!m_nLastBestEntity ||
			m_nLastBestEntity->GetHealth() <= 0/* ||
											   m_nBestIndex == m_nLastBestEntity->GetIndex()*/)
			m_nBestBone = -1;

		CPlayer* pBaseEntity = m_nBestEntity;
		Vector3 vSrc = pLocalEntity->GetEyePosition();
		Vector3 vEnd;
		if (weapons[WeaponID].Nearest)
		{
			//m_nBestBone = -1;
			if (m_nBestBone == -1)
			{
				int nt = weapons[WeaponID].NearestType;
				for (int j = 0; j < (nt == 0 ? 8 : nt == 1 ? 14 : 20); j++)
				{
					Vector3 vec = pBaseEntity->GetHitboxPosition(j);
					float fov = GetFOV(myAng, vSrc, vec);

					if (fov < bestFov)
					{
						if (!U::IsVisible(vSrc, vec, pLocalEntity, pBaseEntity, Options::Legitbot::SmokeCheck))
							continue;

						bestFov = fov;
						vEnd = vec;
						m_nBestBone = j;
					}
				}
			}
			else
			{
				vEnd = pBaseEntity->GetHitboxPosition(m_nBestBone);
			}
		}
		else
		{
			int bone = weapons[WeaponID].Bone;
			Vector3 vec = pBaseEntity->GetBonePosition(bone);
			if (bone >= 6 && bone <= 8) vec.z += 4;

			float fov = GetFOV(myAng, vSrc, vec);
			if (fov < bestFov)
				vEnd = vec;

		}

		m_nAngle = U::CalculateAngle(vSrc, vEnd);
		return vEnd != Vector3(0, 0, 0);
	}
	void AnitUntrusted(Vector3 &angle)
	{
		//if (!Vars.RagebotNew.AntiAim.AnitUT.enabled)
		//	return; // добавь сюда настройку , если хочешь , чтобы он отключался , когда вклачюна опция анти антрастеда , иначе он будет всегда работать
		// сейчас он всегда работает

		if (!std::isfinite(angle.x)) { angle.x = 0; }
		if (!std::isfinite(angle.y)) { angle.y = 0; }

		while (angle.y <= -1800000) angle.y += 3600000;
		while (angle.y > 1800000) angle.y -= 3600000;
		while (angle.x <= -1800000) angle.x += 3600000;
		while (angle.x > 1800000) angle.x -= 3600000;

		while (angle.y <= -18000) angle.y += 36000;
		while (angle.y > 18000) angle.y -= 36000;
		while (angle.x <= -18000) angle.x += 36000;
		while (angle.x > 18000) angle.x -= 36000;

		while (angle.y <= -180) angle.y += 360;
		while (angle.y > 180) angle.y -= 360;
		while (angle.x <= -180) angle.x += 360;
		while (angle.x > 180) angle.x -= 360;

		if (angle.x > 89.0) angle.x = 89;
		if (angle.x < -89.0) angle.x = -89;
		if (angle.y < -180) angle.y = -179.999;
		if (angle.y > 180) angle.y = 179.999;

		angle.z = 0;
	}

	void Run(CUserCmd* cmd, bool* &bSendPacket)
	{
		m_nBestIndex = -1;
		//m_nLastBestEntity = NULL;
		pLocalEntity = Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer());
		if (!pLocalEntity)
			return;
		Weapon = pLocalEntity->GetWeap();
		if (!Weapon)
			return;
		WeaponID = Weapon->GetItemDefinitionIndex();
		if (!weapons[WeaponID].Enabled)
			return;
		if (U::IsNonAimWeapon(WeaponID))
			return;

		int m_iShotsFired = pLocalEntity->GetShotsFired();

		if (m_iShotsFired <= weapons[WeaponID].StartBullet - 1)
			return;

		if (weapons[WeaponID].EndBullet != 0 && m_iShotsFired >= weapons[WeaponID].EndBullet)
			return;

		bool allowSilent = weapons[WeaponID].pSilent &&
			(weapons[WeaponID].pSilentBullet == 0 || weapons[WeaponID].pSilentBullet != 0 && m_iShotsFired <= weapons[WeaponID].pSilentBullet - 1);

		G::AllowSilent = allowSilent;
		bool canSilent = allowSilent && U::CanShoot(pLocalEntity, Weapon);

		if (canSilent)
			canSilent = (1 + (rand() % 101)) <= weapons[WeaponID].pSilentPercentage;

		Vector3 src = cmd->viewangles;
		//Vector3 srcr = cmd->viewangles + (pLocalEntity->GetPunchAngles() * Vector3(weapons[WeaponID].RCSAmountX, weapons[WeaponID].RCSAmountY, 0));
		Vector3 srcr = cmd->viewangles + (pLocalEntity->GetPunchAngles() * Vector3(weapons[WeaponID].RcsX / 50.f, weapons[WeaponID].RcsY / 50.f, 0));

		auto pBaseEntity = m_nBestEntity;
		if (cmd->buttons & IN_ATTACK || Options::Legitbot::AutoFire)
		{
			bool canFireDelay = Interface.Globals->curtime <= G::FireDelayTime;
			if (!lastShooting || lastShooting && weapons[WeaponID].FireDelayRepeat && !canFireDelay)
			{
				lastShooting = true;
				G::FireDelayTime = Interface.Globals->curtime + weapons[WeaponID].FireDelay;
			}

			if (Options::Legitbot::KillDelay && !Options::Legitbot::AutoFire && (G::KillDelayEnd || Interface.Globals->curtime <= G::KillDelayTime))
				return;

			bool delay = false;
			if (weapons[WeaponID].FireDelayEnabled && canFireDelay)
			{
				delay = true;
				canSilent = false;
				allowSilent = false;
			}

			if (!GetBestTarget(srcr, allowSilent))
				return;

			if (!GetBestBone(srcr, allowSilent))
				return;

			m_nLastBestEntity = m_nBestEntity;
			if (Options::Legitbot::AutoFire) cmd->buttons |= IN_ATTACK;
			if (delay) cmd->buttons &= ~IN_ATTACK;

			//Vector3 dst = m_nAngle - (pLocalEntity->GetPunchAngles() * Vector3(weapons[WeaponID].RCSAmountX, weapons[WeaponID].RCSAmountY, 0));
			Vector3 dst = m_nAngle - (pLocalEntity->GetPunchAngles() * Vector3(weapons[WeaponID].RcsX / 50.f, weapons[WeaponID].RcsY / 50.f, 0));

			float smooth = allowSilent ? weapons[WeaponID].pSilentSmooth : weapons[WeaponID].Smooth;
			if (Options::Legitbot::AimType == 0 ||
				Options::Legitbot::AimType == 1)
				dst = Smooth(src, dst, smooth);
			else if (Options::Legitbot::AimType == 2)
				dst = CurveSmooth(src, dst, smooth / 100.f);

			if (canSilent)
			{
				AnitUntrusted(dst);
				cmd->viewangles = dst;
				*bSendPacket = false;
			}
			else if (!allowSilent)
			{
				AnitUntrusted(dst);
				cmd->viewangles = dst;
				Interface.Engine->SetViewAngles(dst);
			}
		}
		else
		{
			lastShooting = false;
			m_nBestBone = -1;
			G::KillDelayEnd = false;
		}

		/*if (Options::Misc::AU)
		{
		if (Interface.Engine->GetLocalPlayer() == MOVETYPE_LADDER || Interface.Engine->GetLocalPlayer() == MOVETYPE_NOCLIP)
		return;

		if (Interface.Engine->GetLocalPlayer() & FL_ONGROUND)
		return;

		if (cmd->mousedx > 1 || cmd->mousedx < -1)
		{
		cmd->sidemove = cmd->mousedx < 0.f ? -400.f : 400.f;
		}
		}*/


		CBaseWeapon* weap = pLocalEntity->GetWeap();
		if (Options::Misc::AU)
			if ((cmd->buttons & IN_ATTACK) && (weap->NextPrimaryAttack()
				- ((float)pLocalEntity->TickBase()
					* Interface.Globals->interval_per_tick) > 0)) cmd->buttons &= ~IN_ATTACK;
	}
}