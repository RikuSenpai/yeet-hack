#pragma once

namespace CEvents
{
	float hurtTime = -10;
	int hurtDamage = 0;

	bool __fastcall Run(void* ecx, void* edx, IGameEvent* pEvent)
	{
		if (!pEvent)
			return O::FireEventClientSide(ecx, pEvent);
		
		const char* szEventName = pEvent->GetName();

		if (!strcmp(szEventName, XorStr("player_death")))
		{
			if (Interface.Engine->GetPlayerForUserID(pEvent->GetInt(XorStr("attacker"))) == Interface.Engine->GetLocalPlayer())
			{
				if (Options::Legitbot::KillDelayTime == 0)
					G::KillDelayEnd = true;
				else
					G::KillDelayTime = Interface.Globals->curtime + Options::Legitbot::KillDelayTime;

			}
		}
		if(!strcmp(szEventName, XorStr("game_newmap")))
		{
			hurtTime = -10;
			G::KillDelayEnd = false;
			G::KillDelayTime = 0;
			U::LoadKnifeModels();
		}
		if (!strcmp(szEventName, XorStr("player_death")))
		{
			if (Interface.Engine->GetPlayerForUserID(pEvent->GetInt(XorStr("attacker"))) == Interface.Engine->GetLocalPlayer())
			{
				std::string weapon = pEvent->GetString(XorStr("weapon"));
				
				if (weapon == XorStr("knife_default_ct") ||
					weapon == XorStr("knife_default_t"))
				{
					const char* newWeapon = U::GetKillIconWeapon(Options::SkinChanger::Knife);
					if (newWeapon != NULL)
						pEvent->SetString(XorStr("weapon"), newWeapon);
				}
			}
		}

		return O::FireEventClientSide(ecx, pEvent);
	}
};

class player_hurt_listener
	: public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *pEvent) override
	{
		if (!strcmp(pEvent->GetName(), XorStr("player_hurt")))
		{
			if (Interface.Engine->GetPlayerForUserID(pEvent->GetInt("attacker")) == Interface.Engine->GetLocalPlayer()) {
				CEvents::hurtDamage = pEvent->GetInt("dmg_health");
				CEvents::hurtTime = Interface.Globals->curtime;
			}
		}
	}
	int GetEventDebugID(void) override
	{
		return 0x2A;
	}
};
