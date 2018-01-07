#include "RecoilCrosshair.h"
#include "Player.h"
#include "Draw.h"
#include "Utils.h"
#include "Vars.h"

void CRecoilCrosshair::Main(CUserCmd* cmd)
{
	/*Vector3 Punch = pLocal->GetPunchAngles() * 4.f;

	int  iWidth, iHeight;

	Interface.Engine->GetScreenSize(iWidth, iHeight);

	Draw::DrawRect((iWidth / 2) - 5 - Punch.y, (iHeight / 2) - 1 + Punch.x, 11, 3, Color(0,0,0,255));
	Draw::DrawRect((iWidth / 2) - 1 - Punch.y, (iHeight / 2) - 5 + Punch.x, 3, 11, Color(0, 0, 0, 255));
	Draw::DrawRect((iWidth / 2) - 4 - Punch.y, (iHeight / 2) + Punch.x, 9, 1, Color(255, 255, 255, 255));
	Draw::DrawRect((iWidth / 2) - Punch.y, (iHeight / 2) - 4 + Punch.x, 1, 9, Color(255, 255, 255, 255));*/
	m_pCmd = cmd;
}

void CRecoilCrosshair::Render(CPlayer* pLocal)
{
	Vector3 LookingAngles = m_pCmd->viewangles + pLocal->GetPunchAngles() * 2.f;

	Vector3 Start = pLocal->GetEyePosition();

	Vector3 End;

	Ray_t ray;
	trace_t trace;
	CTraceFilter TraceFilter;

	TraceFilter.pSkip = pLocal;

	End += Start;

	U::AngleVectors2(LookingAngles, &End);

	ray.Init(Start, End);

	Interface.EngineTrace->TraceRay(ray, 0x46004003, &TraceFilter, &trace);

	Vector3 screen;
		
	if (U::WorldToScreen(trace.endpos,screen))
	{
		Draw::DrawString(400, 400, Color::White(), false, "%s", screen.x);
		Draw::DrawString(400, 450, Color::White(), false, "%s", screen.y);
		Draw::DrawString(screen.x, screen.y, Color::White(), L"+");
	}
}

CRecoilCrosshair* RecoilCrosshair = new CRecoilCrosshair;