#pragma once
#include <math.h>

namespace CKnifeBot
{
	bool lastAttacked = false;
	int m_nBestIndex = -1;
	float m_nBestDist = -1;
	Vector3 m_nAngle;
	CPlayer* pBestEntity;
	CPlayer* pLocalEntity;

	bool GetBestTarget()
	{
		float bestDist = 75;
		for (int i = 0; i < Interface.Engine->GetMaxClients(); i++)
		{
			CPlayer* pBaseEntity = Interface.EntityList->GetClientEntity<CPlayer>(i);
			if (!pBaseEntity)
				continue;
			if (!pBaseEntity->IsValid())
				continue;
			if (pBaseEntity == pLocalEntity)
				continue;
			if (pBaseEntity->GetTeam() == pLocalEntity->GetTeam())
				continue;

			Vector3 localPos = pLocalEntity->GetOrigin(); localPos.z += 50;
			Vector3 basePos = pBaseEntity->GetOrigin(); basePos.z += 50;
			if (!U::IsVisible(localPos, basePos, pLocalEntity, pBaseEntity, true))
				continue;

			float curDist = localPos.DistTo(basePos);
			if (curDist < bestDist)
			{
				bestDist = curDist;
				m_nBestIndex = i;
				pBestEntity = pBaseEntity;
			}
		}

		m_nBestDist = bestDist;
		return m_nBestIndex != -1;
	}

	void Run(CUserCmd* cmd, bool* &bSendPacket)
	{
		m_nBestIndex = -1;
		pLocalEntity = Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer());
		if (!pLocalEntity)
			return;

		int cw = U::SafeWeaponID();
		if (cw == 0)
			return;

		if (!U::IsWeaponKnife(cw))
			return;

		if (!GetBestTarget())
			return;

		Vector3 tempLocalOrigin = pLocalEntity->GetOrigin();
		Vector3 tempBestOrigin = pBestEntity->GetOrigin();
		tempBestOrigin.z = tempLocalOrigin.z;
		Vector3 entAng = U::CalculateAngle(tempLocalOrigin, tempBestOrigin);

		if (!lastAttacked)
		{
			bool stab = false;
			if (Options::Misc::KnifeBotAuto)
			{
				int health = pBestEntity->GetHealth();
				if (pBestEntity->isArmored())
				{
					if (health <= 55 &&
						health > 34)
						stab = true;
				}
				else
				{
					if (health <= 65 &&
						health > 40)
						stab = true;
				}

				stab = stab && m_nBestDist < 60;

				if (stab)
					cmd->buttons |= IN_ATTACK2;
				else
					cmd->buttons |= IN_ATTACK;
			}
			else
			{
				stab = cmd->buttons & IN_ATTACK2;
			}

			if (Options::Misc::KnifeBot360)
			{
				CBaseWeapon* weap = pLocalEntity->GetWeap();
				float server_time = pLocalEntity->TickBase() * Interface.Globals->interval_per_tick;
				float next_shot = (stab ? weap->NextSecondaryAttack() : weap->NextPrimaryAttack()) - server_time;
				if (!(next_shot > 0) && (Options::Misc::KnifeBotAuto || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2))
				{
					cmd->viewangles = entAng;
					*bSendPacket = false;
				}
			}
		}
		lastAttacked = !lastAttacked;
	}
};