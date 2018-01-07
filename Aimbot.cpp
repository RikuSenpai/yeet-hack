#include "Aimbot.h"
#include "Utils.h"
#include "Player.h"
#include "Draw.h"

#define TargetChar "+"

void CAimbot::Init()
{
	m_iTarget = -1;

	m_pLocal = 0;

}

void CAimbot::Main(CPlayer* pLocal ,CUserCmd* cmd)
{
	m_pLocal = pLocal; 

	GetBestTargetByCrosshairDistance();

	if (m_iTarget != -1)
	{
		CPlayer* target = Interface.EntityList->GetClientEntity<CPlayer>(m_iTarget);

		if (!target->IsValid())
		{
			m_iTarget = -1;
			return;
		}

		Vector3 dir = target->GetBonePosition(6) - pLocal->GetEyePosition();

		U::VectorNormalize(dir);

		Vector3 aim;

		U::VectorAngles(dir, aim);

		aim.z = 0.f;

		U::ClampAngles(aim);

		cmd->viewangles = aim;
	}
}

void CAimbot::Render(CPlayer* pLocal)
{
	CPlayer* target = Interface.EntityList->GetClientEntity<CPlayer>(m_iTarget);

	Vector3 screen;

	if (target->IsValid(pLocal))
	{
		if (U::WorldToScreen(target->GetBonePosition(6), screen))
		{
			Draw::DrawString(screen.x, screen.y, Color(83, 255, 64),true, "%s",TargetChar);
		}
	}
}

void CAimbot::CalculateAngle(const Vector3& in, Vector3 out)
{
	float pitch = U::Deg2Rad(in.x);
	float yaw = U::Deg2Rad(in.y);
	float temp = cos(pitch);

	out.x = -temp * -cos(yaw);
	out.y = sin(yaw) * temp;
	out.z = -sin(pitch);
}

int CAimbot::GetBestTargetByDistance()
{
	return 0;
}

int CAimbot::GetBestTargetByCrosshairDistance()
{

	for (int i = 1; i <= Interface.EntityList->GetHighestEntityIndex(); i++)
	{
		CPlayer* target = Interface.EntityList->GetClientEntity<CPlayer>(i);

		Vector3 screen;

	if (target->IsValid(m_pLocal))
	{

		if (U::WorldToScreen(target->GetAbsOrigin(), screen))
		{
				if (m_iTarget == -1)
				{
					if (screen.DistTo(ScreenCenter) < 360)
					{
						m_iTarget = i;
					}
				}
			}
	}
}

	return 0;
}

Vector3 CAimbot::NormalizeAngles(Vector3 AngleToNormalize)
{
	Vector3 vec = AngleToNormalize;
	if (vec.x > 89.0f && vec.x <= 180.0f)
	{
		vec.x = 89.0f;
	}
	while (vec.x > 180.f)
	{
		vec.x -= 360.f;
	}
	while (vec.x < -89.0f)
	{
		vec.x = -89.0f;
	}
	while (vec.y > 180.f)
	{
		vec.y -= 360.f;
	}
	while (vec.y < -180.f)
	{
		vec.y += 360.f;
	}

	vec.z = 0;
	return vec;
}

bool CAimbot::IsPlayerValid(int pIndex)
{
	if (!m_pLocal)
		return false;

	CPlayer* pEntity = Interface.EntityList->GetClientEntity<CPlayer>(pIndex);
	if (!pEntity)
		return false;


	if (pEntity->IsDormant())
		return false;

	if (pEntity->GetLifeState() != 0)
		return false;

	if (pEntity->GetHealth() > 500)
		return false;

	if (pEntity->GetTeam() == m_pLocal->GetTeam())
		return false;


	return true;
}

CAimbot* Aimbot = new CAimbot();