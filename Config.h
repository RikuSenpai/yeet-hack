#pragma once
#include "IniReader.h"
#include "IniWriter.h"

namespace Config
{
	
	const char* config_path = "";
	void SetupPath()
	{
		/*std::string str = "";
		str += getenv("APPDATA");
		str += "\\Renaissance\\Config.ini";
		config_path = str.c_str();*/

		CreateDirectory("C:\\ShaytanHook", NULL);
		config_path = "C:\\ShaytanHook\\config.ini";
	}

	void ConfigSystem()
	{
		switch (Options::Misc::ConfigSystem)
		{
		case 0:
		{
			config_path = "C:\\ShaytanHook\\legit.ini";
			break;
		}
		case 1:
		{
			config_path = "C:\\ShaytanHook\\semilegit.ini";
			break;
		}
		case 2:
		{
			config_path = "C:\\ShaytanHook\\semirage.ini";
			break;
		}
		default:
		{
			config_path = "C:\\ShaytanHook\\semilegit.ini";
			break;
		}
		}
	}

	void Read()
	{
		CIniReader reader(config_path);
		ConfigSystem();
		Options::Legitbot::Enabled = reader.ReadBoolean(XorStr("Legitbot"), XorStr("|Enabled"), false);
		Options::Legitbot::DrawFov = reader.ReadBoolean(XorStr("Legitbot"), XorStr("|DrawFov"), false);
		Options::Legitbot::Deathmatch = reader.ReadBoolean(XorStr("Legitbot"), XorStr("|Deathmatch"), false);
		Options::Legitbot::SmokeCheck = reader.ReadBoolean(XorStr("Legitbot"), XorStr("|SmokeCheck"), false);
		Options::Legitbot::AimType = reader.ReadInteger(XorStr("Legitbot"), XorStr("|AimType"), 0);
		Options::Legitbot::KillDelay = reader.ReadBoolean(XorStr("Legitbot"), XorStr("|KillDelay"), false);
		Options::Legitbot::KillDelayTime = reader.ReadFloat(XorStr("Legitbot"), XorStr("|KillDelayTime"), 0.40f);

		Options::Visuals::ESP::Enabled = reader.ReadBoolean(XorStr("ESP"), XorStr("|Enabled"), false);
		Options::Visuals::ESP::EnemyOnly = reader.ReadBoolean(XorStr("ESP"), XorStr("|EnemyOnly"), false);
		Options::Visuals::ESP::VisibleOnly = reader.ReadBoolean(XorStr("ESP"), XorStr("|VisibleOnly"), false);
		Options::Visuals::ESP::SmokeCheck = reader.ReadBoolean(XorStr("ESP"), XorStr("|SmokeCheck"), false);
		Options::Visuals::ESP::Box = reader.ReadBoolean(XorStr("ESP"), XorStr("|Box"), false);	
		Options::Visuals::ESP::Style = reader.ReadInteger(XorStr("ESP"), XorStr("|Style"), 0);
		Options::Visuals::Misc::Grenades = reader.ReadBoolean(XorStr("ESP"), XorStr("|Grenades"), false);
		Options::Visuals::ESP::Lights = reader.ReadBoolean(XorStr("ESP"), XorStr("|Lights"), false);
		Options::Visuals::ESP::Name = reader.ReadBoolean(XorStr("ESP"), XorStr("|Name"), false);
		Options::Visuals::Health::Health1 = reader.ReadBoolean(XorStr("ESP"), XorStr("|Health"), false);
		Options::Visuals::ESP::Weapon = reader.ReadBoolean(XorStr("ESP"), XorStr("|Weapon"), false);
		Options::Visuals::ESP::WeaponAmmo = reader.ReadBoolean(XorStr("ESP"), XorStr("|WeaponAmmo"), false);
		Options::Visuals::ESP::skilet = reader.ReadBoolean(XorStr("ESP"), XorStr("|BoneESP"), false);

		//Options::Visuals::Hands::color[0] = reader.ReadInteger(XorStr("Hands"), XorStr("|ColorR"), 0) / 255.f;
		Options::Visuals::Health::color[0] = reader.ReadInteger(XorStr("ESP"), XorStr("|HPBarr"),  0) / 255.f;
		Options::Visuals::Health::color[1] = reader.ReadInteger(XorStr("ESP"), XorStr("|HPBarg"), 255) / 255.f;
		Options::Visuals::Health::color[2] = reader.ReadInteger(XorStr("ESP"), XorStr("|HPBarb"), 0) / 255.f;

		Options::Visuals::ESP::colorbomb[0] = reader.ReadInteger(XorStr("BOMB"), XorStr("|ColorBR"), 255) / 255.f;
		Options::Visuals::ESP::colorbomb[1] = reader.ReadInteger(XorStr("BOMB"), XorStr("|ColorBG"), 0) / 255.f;
		Options::Visuals::ESP::colorbomb[2] = reader.ReadInteger(XorStr("BOMB"), XorStr("|ColorBB"), 0) / 255.f;

		Options::Visuals::ESP::color_dlight[0] = reader.ReadInteger(XorStr("ESP"), XorStr("|lightr"), 0) / 255.f;
		Options::Visuals::ESP::color_dlight[1] = reader.ReadInteger(XorStr("ESP"), XorStr("|lightg"), 255) / 255.f;
		Options::Visuals::ESP::color_dlight[2] = reader.ReadInteger(XorStr("ESP"), XorStr("|lightb"), 0) / 255.f;

		Options::Visuals::Chams::Enabled = reader.ReadBoolean(XorStr("Chams"), XorStr("|Enabled"), false);
		Options::Visuals::Chams::EnemyOnly = reader.ReadBoolean(XorStr("Chams"), XorStr("|EnemyOnly"), true);
		Options::Visuals::Chams::VisibleOnly = reader.ReadBoolean(XorStr("Chams"), XorStr("|VisibleOnly"), false);
		Options::Visuals::Chams::Stylez = reader.ReadInteger(XorStr("Chams"), XorStr("|Style"), 1);

		Options::Visuals::Chams::color[0] = reader.ReadInteger(XorStr("Chams"), XorStr("|VisibleColorR"), 0) / 255.f;
		Options::Visuals::Chams::color[1] = reader.ReadInteger(XorStr("Chams"), XorStr("|VisibleColorG"), 255) / 255.f;
		Options::Visuals::Chams::color[2] = reader.ReadInteger(XorStr("Chams"), XorStr("|VisibleColorB"), 0) / 255.f;

		Options::Visuals::Chams::coloriz[0] = reader.ReadInteger(XorStr("Chams"), XorStr("|InvisibleColorR"), 0) / 255.f;
		Options::Visuals::Chams::coloriz[1] = reader.ReadInteger(XorStr("Chams"), XorStr("|InvisibleColorG"), 0) / 255.f;
		Options::Visuals::Chams::coloriz[2] = reader.ReadInteger(XorStr("Chams"), XorStr("|InvisibleColorB"), 0) / 255.f;

		Options::Visuals::Hands::Enabled = reader.ReadBoolean(XorStr("Hands"), XorStr("|Enabled"), false);
		Options::Visuals::Hands::Style = reader.ReadInteger(XorStr("Hands"), XorStr("|Style"), false);

		Options::Visuals::Hands::color[0] = reader.ReadInteger(XorStr("Hands"), XorStr("|ColorR"), 0) / 255.f;
		Options::Visuals::Hands::color[1] = reader.ReadInteger(XorStr("Hands"), XorStr("|ColorG"), 104) / 255.f;
		Options::Visuals::Hands::color[2] = reader.ReadInteger(XorStr("Hands"), XorStr("|ColorB"), 0) / 255.f;

		Options::Radar::Enabled = reader.ReadBoolean(XorStr("Radar"), XorStr("|Enabled"), false);
		Options::Radar::Style = reader.ReadInteger(XorStr("Radar"), XorStr("|Style"), 0);
		Options::Radar::Type = reader.ReadInteger(XorStr("Radar"), XorStr("|Type"), 0);
		Options::Radar::Alpha = reader.ReadInteger(XorStr("Radar"), XorStr("|Alpha"), 255);
		Options::Radar::ViewCheck = reader.ReadBoolean(XorStr("Radar"), XorStr("|Radar"), false);
		Options::Radar::EnemyOnly = reader.ReadBoolean(XorStr("Radar"), XorStr("|EnemyOnly"), false);
		Options::Radar::VisibleOnly = reader.ReadBoolean(XorStr("Radar"), XorStr("|VisibleOnly"), false);
		Options::Radar::SmokeCheck = reader.ReadBoolean(XorStr("Radar"), XorStr("|SmokeCheck"), false);
		Options::Radar::Zoom = reader.ReadFloat(XorStr("Radar"), XorStr("|Zoom"), 1.f);

		Options::SkinChanger::EnabledSkin = reader.ReadBoolean(XorStr("SkinChanger"), XorStr("|EnabledSkin"), false);
		Options::SkinChanger::EnabledKnife = reader.ReadBoolean(XorStr("SkinChanger"), XorStr("|EnabledKnife"), false);
		Options::SkinChanger::EnabledGlove = reader.ReadBoolean(XorStr("SkinChanger"), XorStr("|EnabledGlove"), false);
		Options::SkinChanger::Knife = reader.ReadInteger(XorStr("SkinChanger"), XorStr("|Knife"), 4);
		Options::SkinChanger::Glove = reader.ReadInteger(XorStr("SkinChanger"), XorStr("|Glove"), 0);
		Options::SkinChanger::GloveSkin = reader.ReadInteger(XorStr("SkinChanger"), XorStr("|GloveSkin"), 0);
		Options::SkinChanger::buf3 = reader.ReadString(XorStr("SkinChanger"), XorStr("|AK47Model"), "");
		Options::SkinChanger::buf1 = reader.ReadString(XorStr("SkinChanger"), XorStr("|CTModel"), "");
		Options::SkinChanger::buf2 = reader.ReadString(XorStr("SkinChanger"), XorStr("|TModel"), "");
		Options::SkinChanger::buf4 = reader.ReadString(XorStr("SkinChanger"), XorStr("|M4Model"), "");
		Options::SkinChanger::buf5 = reader.ReadString(XorStr("SkinChanger"), XorStr("|TKnife"), "");
		Options::SkinChanger::buf6 = reader.ReadString(XorStr("SkinChanger"), XorStr("|CTKnife"), "");

		Options::Misc::RevealRanks = reader.ReadBoolean(XorStr("Misc"), XorStr("|RevealRanks"), false);
		Options::Misc::Bunnyhop = reader.ReadBoolean(XorStr("Misc"), XorStr("|Bunnyhop"), false);
		Options::Misc::SpectatorList = reader.ReadBoolean(XorStr("Misc"), XorStr("|SpectatorList"), false);
		Options::Misc::KnifeBot = reader.ReadBoolean(XorStr("Misc"), XorStr("|KnifeBot"), false);
		Options::Misc::KnifeBotAuto = reader.ReadBoolean(XorStr("Misc"), XorStr("|KnifeBotAuto"), false);
		Options::Misc::KnifeBot360 = reader.ReadBoolean(XorStr("Misc"), XorStr("|KnifeBot360"), false);
		Options::Misc::RecoilCrosshair = reader.ReadBoolean(XorStr("Misc"), XorStr("|RecoilCrosshair"), false);
		Options::Misc::SniperCrosshair = reader.ReadBoolean(XorStr("Misc"), XorStr("|SniperCrosshair"), false);
		Options::Misc::HitInfo = reader.ReadBoolean(XorStr("Misc"), XorStr("|HitInfo"), false);
		Options::Misc::Watermark = reader.ReadBoolean(XorStr("Misc"), XorStr("|Watermark"), false);
		Options::Misc::SpeedControl = reader.ReadFloat(XorStr("Misc"), XorStr("|SpeedControl"), 1);
		Options::Misc::NoFlash = reader.ReadBoolean(XorStr("Misc"), XorStr("|NoFlash"), false);
		Options::Misc::NoFlashAlpha = reader.ReadFloat(XorStr("Misc"), XorStr("|NoFlashAlpha"), 100);
		Options::Misc::AirStuck = reader.ReadBoolean(XorStr("Misc"), XorStr("|AirStuck"), false);
		Options::Visuals::Misc::DropESP = reader.ReadBoolean(XorStr("Misc"), XorStr("|DropESP"), false);
		Options::Visuals::Misc::BombTimer = reader.ReadBoolean(XorStr("Misc"), XorStr("|BombESP"), false);
		Options::Visuals::Misc::BombTimerType = reader.ReadInteger(XorStr("Misc"), XorStr("|BombESPtype"), 2);
		Options::Visuals::Misc::CustomSky = reader.ReadInteger(XorStr("Misc"), XorStr("|SkyChanger"), 0);
		Options::Visuals::Misc::FovChanger = reader.ReadBoolean(XorStr("Misc"), XorStr("|FovChanger"), false);
		Options::Visuals::Misc::FovChangerValue = reader.ReadFloat(XorStr("Misc"), XorStr("|FovChangerValue"), 90);
		Options::Visuals::Misc::ViewmodelChanger = reader.ReadBoolean(XorStr("Misc"), XorStr("|ViewmodelChanger"), false);
		Options::Visuals::Misc::ViewmodelChangerValue = reader.ReadFloat(XorStr("Misc"), XorStr("|ViewmodelChangerValue"), 90);

		for (int i = 1; i < 520; i++)
		{
			char* section = U::GetConfigName(i);
			if (strcmp(section, "") == 0)
				continue;

			weapons[i].Enabled = reader.ReadBoolean(section, XorStr("|Enabled"), weapons[i].Enabled);
			weapons[i].Fov = reader.ReadFloat(section, XorStr("|Fov"), weapons[i].Fov);
			weapons[i].Bone = reader.ReadInteger(section, XorStr("|Bone"), weapons[i].Bone);
			weapons[i].Nearest = reader.ReadBoolean(section, XorStr("|Nearest"), weapons[i].Nearest);
			weapons[i].NearestType = reader.ReadInteger(section, XorStr("|NearestType"), weapons[i].NearestType);
			weapons[i].Smooth = reader.ReadFloat(section, XorStr("|Smooth"), weapons[i].Smooth);
			weapons[i].FireDelayEnabled = reader.ReadBoolean(section, XorStr("|FireDelayEnabled"), weapons[i].FireDelayEnabled);
			weapons[i].FireDelayRepeat = reader.ReadBoolean(section, XorStr("|FireDelayRepeat"), weapons[i].FireDelayRepeat);
			weapons[i].FireDelay = reader.ReadFloat(section, XorStr("|FireDelay"), weapons[i].FireDelay);
			weapons[i].StartBullet = reader.ReadInteger(section, XorStr("|StartBullet"), weapons[i].StartBullet);
			weapons[i].EndBullet = reader.ReadInteger(section, XorStr("|EndBullet"), weapons[i].EndBullet);
			weapons[i].RcsX = reader.ReadInteger(section, XorStr("|RcsX"), weapons[i].RcsX);
			weapons[i].RcsY = reader.ReadInteger(section, XorStr("|RcsY"), weapons[i].RcsY);

			weapons[i].pSilent = reader.ReadBoolean(section, XorStr("|pSilent"), weapons[i].pSilent);
			weapons[i].pSilentBullet = reader.ReadInteger(section, XorStr("|pSilentBullet"), weapons[i].pSilentBullet);
			weapons[i].pSilentPercentage = reader.ReadInteger(section, XorStr("|pSilentPercentage"), weapons[i].pSilentPercentage);
			weapons[i].pSilentFov = reader.ReadFloat(section, XorStr("|pSilentFov"), weapons[i].pSilentFov);
			weapons[i].pSilentSmooth = reader.ReadFloat(section, XorStr("|pSilentSmooth"), weapons[i].pSilentSmooth);

			weapons[i].ChangerEnabled = reader.ReadBoolean(section, XorStr("|ChangerEnabled"), weapons[i].ChangerEnabled);
			//reader.ReadString(section, XorStr("|ChangerName"), weapons[i].ChangerName, weapons[i].ChangerName);
			weapons[i].ChangerSeed = reader.ReadInteger(section, XorStr("|ChangerSeed"), weapons[i].ChangerSeed);
			weapons[i].ChangerSkin = reader.ReadInteger(section, XorStr("|ChangerSkin"), weapons[i].ChangerSkin);
			weapons[i].ChangerStatTrak = reader.ReadInteger(section, XorStr("|ChangerStatTrak"), weapons[i].ChangerStatTrak);
			weapons[i].ChangerWear = reader.ReadFloat(section, XorStr("|ChangerWear"), weapons[i].ChangerWear);
		}
	}

	void Save()
	{
		CIniWriter writer(config_path);
		ConfigSystem();
		writer.WriteBoolean(XorStr("Legitbot"), XorStr("|Enabled"), Options::Legitbot::Enabled);
		writer.WriteBoolean(XorStr("Legitbot"), XorStr("|DrawFov"), Options::Legitbot::DrawFov);
		writer.WriteBoolean(XorStr("Legitbot"), XorStr("|Deathmatch"), Options::Legitbot::Deathmatch);
		writer.WriteBoolean(XorStr("Legitbot"), XorStr("|SmokeCheck"), Options::Legitbot::SmokeCheck);
		writer.WriteInteger(XorStr("Legitbot"), XorStr("|AimType"), Options::Legitbot::AimType);
		writer.WriteBoolean(XorStr("Legitbot"), XorStr("|KillDelay"), Options::Legitbot::KillDelay);
		writer.WriteFloat(XorStr("Legitbot"), XorStr("|KillDelayTime"), Options::Legitbot::KillDelayTime);

		writer.WriteBoolean(XorStr("ESP"), XorStr("|Enabled"), Options::Visuals::ESP::Enabled);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|EnemyOnly"), Options::Visuals::ESP::EnemyOnly);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|VisibleOnly"), Options::Visuals::ESP::VisibleOnly);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|SmokeCheck"), Options::Visuals::ESP::SmokeCheck);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|Box"), Options::Visuals::ESP::Box);
		writer.WriteInteger(XorStr("ESP"), XorStr("|Style"), Options::Visuals::ESP::Style);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|Name"), Options::Visuals::ESP::Name);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|Health"), Options::Visuals::Health::Health1);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|Weapon"), Options::Visuals::ESP::Weapon);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|WeaponAmmo"), Options::Visuals::ESP::WeaponAmmo);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|Grenades"), Options::Visuals::Misc::Grenades);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|Lights"), Options::Visuals::ESP::Lights);
		writer.WriteBoolean(XorStr("ESP"), XorStr("|BoneESP"), Options::Visuals::ESP::skilet); 

		writer.WriteBoolean(XorStr("Chams"), XorStr("|Enabled"), Options::Visuals::Chams::Enabled);
		writer.WriteBoolean(XorStr("Chams"), XorStr("|EnemyOnly"), Options::Visuals::Chams::EnemyOnly);
		writer.WriteBoolean(XorStr("Chams"), XorStr("|VisibleOnly"), Options::Visuals::Chams::VisibleOnly);
		writer.WriteInteger(XorStr("Chams"), XorStr("|Style"), Options::Visuals::Chams::Stylez);
		writer.WriteInteger(XorStr("Chams"), XorStr("|VisibleColorR"), Options::Visuals::Chams::color[0] * 255);
		writer.WriteInteger(XorStr("Chams"), XorStr("|VisibleColorG"), Options::Visuals::Chams::color[1] * 255);
		writer.WriteInteger(XorStr("Chams"), XorStr("|VisibleColorB"), Options::Visuals::Chams::color[2] * 255);

		writer.WriteInteger(XorStr("Chams"), XorStr("|InvisibleColorR"), Options::Visuals::Chams::coloriz[0] * 255);
		writer.WriteInteger(XorStr("Chams"), XorStr("|InvisibleColorG"), Options::Visuals::Chams::coloriz[1] * 255);
		writer.WriteInteger(XorStr("Chams"), XorStr("|InvisibleColorB"), Options::Visuals::Chams::coloriz[2] * 255);

		writer.WriteBoolean(XorStr("Hands"), XorStr("|Enabled"), Options::Visuals::Hands::Enabled);
		writer.WriteInteger(XorStr("Hands"), XorStr("|Style"), Options::Visuals::Hands::Style);
		writer.WriteInteger(XorStr("Hands"), XorStr("|ColorR"), Options::Visuals::Hands::color[0] * 255);
		writer.WriteInteger(XorStr("Hands"), XorStr("|ColorG"), Options::Visuals::Hands::color[1] * 255);
		writer.WriteInteger(XorStr("Hands"), XorStr("|ColorB"), Options::Visuals::Hands::color[2] * 255);

		writer.WriteInteger(XorStr("ESP"), XorStr("|ColorR"), Options::Visuals::ESP::color_invis[0] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|ColorG"), Options::Visuals::ESP::color_invis[1] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|ColorB"), Options::Visuals::ESP::color_invis[2] * 255);

		writer.WriteInteger(XorStr("BOMB"), XorStr("|ColorBR"), Options::Visuals::ESP::colorbomb[0] * 255);
		writer.WriteInteger(XorStr("BOMB"), XorStr("|ColorBG"), Options::Visuals::ESP::colorbomb[1] * 255);
		writer.WriteInteger(XorStr("BOMB"), XorStr("|ColorBB"), Options::Visuals::ESP::colorbomb[2] * 255);

		writer.WriteInteger(XorStr("ESP"), XorStr("|ColorRz"), Options::Visuals::ESP::color_vis[0] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|ColorGz"), Options::Visuals::ESP::color_vis[1] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|ColorBz"), Options::Visuals::ESP::color_vis[2] * 255);

		writer.WriteInteger(XorStr("ESP"), XorStr("|HPBarr"), Options::Visuals::Health::color[0] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|HPBarg"), Options::Visuals::Health::color[1] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|HPBarb"), Options::Visuals::Health::color[2] * 255);

		writer.WriteInteger(XorStr("ESP"), XorStr("|lightr"), Options::Visuals::ESP::color_dlight[0] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|lightg"), Options::Visuals::ESP::color_dlight[1] * 255);
		writer.WriteInteger(XorStr("ESP"), XorStr("|lightb"), Options::Visuals::ESP::color_dlight[2] * 255);

		writer.WriteBoolean(XorStr("Radar"), XorStr("|Enabled"), Options::Radar::Enabled);
		writer.WriteInteger(XorStr("Radar"), XorStr("|Style"), Options::Radar::Style);
		writer.WriteInteger(XorStr("Radar"), XorStr("|Type"), Options::Radar::Type);
		writer.WriteInteger(XorStr("Radar"), XorStr("|Alpha"), Options::Radar::Alpha);
		writer.WriteBoolean(XorStr("Radar"), XorStr("|ViewCheck"), Options::Radar::ViewCheck);
		writer.WriteBoolean(XorStr("Radar"), XorStr("|EnemyOnly"), Options::Radar::EnemyOnly);
		writer.WriteBoolean(XorStr("Radar"), XorStr("|VisibleOnly"), Options::Radar::VisibleOnly);
		writer.WriteBoolean(XorStr("Radar"), XorStr("|SmokeCheck"), Options::Radar::SmokeCheck);
		writer.WriteFloat(XorStr("Radar"), XorStr("|Zoom"), Options::Radar::Zoom);

		writer.WriteInteger(XorStr("Radar"), XorStr("|ENVISr"), Options::Visuals::ESP::radar_enVis[0] * 255);
		writer.WriteInteger(XorStr("Radar"), XorStr("|ENVISg"), Options::Visuals::ESP::radar_enVis[1] * 255);
		writer.WriteInteger(XorStr("Radar"), XorStr("|ENVISb"), Options::Visuals::ESP::radar_enVis[2] * 255);

		writer.WriteInteger(XorStr("Radar"), XorStr("|enInvisr"), Options::Visuals::ESP::radar_enInvis[0] * 255);
		writer.WriteInteger(XorStr("Radar"), XorStr("|enInvisg"), Options::Visuals::ESP::radar_enInvis[1] * 255);
		writer.WriteInteger(XorStr("Radar"), XorStr("|enInvisb"), Options::Visuals::ESP::radar_enInvis[2] * 255);

		writer.WriteInteger(XorStr("Radar"), XorStr("|teamr"), Options::Visuals::ESP::radar_team[0] * 255);
		writer.WriteInteger(XorStr("Radar"), XorStr("|teamg"), Options::Visuals::ESP::radar_team[1] * 255);
		writer.WriteInteger(XorStr("Radar"), XorStr("|teamb"), Options::Visuals::ESP::radar_team[2] * 255);
			

		writer.WriteBoolean(XorStr("SkinChanger"), XorStr("|EnabledSkin"), Options::SkinChanger::EnabledSkin);
		writer.WriteBoolean(XorStr("SkinChanger"), XorStr("|EnabledKnife"), Options::SkinChanger::EnabledKnife);
		writer.WriteBoolean(XorStr("SkinChanger"), XorStr("|EnabledGlove"), Options::SkinChanger::EnabledGlove);
		writer.WriteInteger(XorStr("SkinChanger"), XorStr("|Knife"), Options::SkinChanger::Knife);
		writer.WriteInteger(XorStr("SkinChanger"), XorStr("|Glove"), Options::SkinChanger::Glove);
		writer.WriteInteger(XorStr("SkinChanger"), XorStr("|GloveSkin"), Options::SkinChanger::GloveSkin);
		writer.WriteInteger(XorStr("SkinChanger"), XorStr("|SkyChanger"), Options::Visuals::Misc::CustomSky);
		writer.WriteString(XorStr("SkinChanger"), XorStr("|AK47Model"), Options::SkinChanger::buf3);
		writer.WriteString(XorStr("SkinChanger"), XorStr("|CTModel"), Options::SkinChanger::buf1);
		writer.WriteString(XorStr("SkinChanger"), XorStr("|TModel"), Options::SkinChanger::buf2);
		writer.WriteString(XorStr("SkinChanger"), XorStr("|M4Model"), Options::SkinChanger::buf4);
		writer.WriteString(XorStr("SkinChanger"), XorStr("|TKnife"), Options::SkinChanger::buf5);
		writer.WriteString(XorStr("SkinChanger"), XorStr("|CTKnife"), Options::SkinChanger::buf6);

		writer.WriteBoolean(XorStr("Misc"), XorStr("|RevealRanks"), Options::Misc::RevealRanks);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|Bunnyhop"), Options::Misc::Bunnyhop);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|SpectatorList"), Options::Misc::SpectatorList);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|HitInfo"), Options::Misc::HitInfo);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|KnifeBot"), Options::Misc::KnifeBot);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|KnifeBotAuto"), Options::Misc::KnifeBotAuto);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|KnifeBot360"), Options::Misc::KnifeBot360);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|Watermark"), Options::Misc::Watermark);
		writer.WriteFloat(XorStr("Misc"), XorStr("|SpeedControl"), Options::Misc::SpeedControl);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|RecoilCrosshair"), Options::Misc::RecoilCrosshair);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|SniperCrosshair"), Options::Misc::SniperCrosshair);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|AirStuck"), Options::Misc::AirStuck);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|DropESP"), Options::Visuals::Misc::DropESP);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|BombESP"), Options::Visuals::Misc::BombTimer);
		writer.WriteInteger(XorStr("Misc"), XorStr("|BombESPtype"), Options::Visuals::Misc::BombTimerType);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|FovChanger"), Options::Visuals::Misc::FovChanger);
		writer.WriteFloat(XorStr("Misc"), XorStr("|FovChangerValue"), Options::Visuals::Misc::FovChangerValue);
		writer.WriteBoolean(XorStr("Misc"), XorStr("|ViewmodelChanger"), Options::Visuals::Misc::ViewmodelChanger);
		writer.WriteFloat(XorStr("Misc"), XorStr("|ViewmodelChangerValue"), Options::Visuals::Misc::ViewmodelChangerValue);

		for (int i = 1; i < 520; i++)
		{
			char* section = U::GetConfigName(i);
			if (strcmp(section, "") == 0)
				continue;

			Weapon_t w = weapons[i];
			if (std::string(section).find(XorStr("knife")) == std::string::npos)
			{
				writer.WriteBoolean(section, XorStr("|Enabled"), w.Enabled);
				writer.WriteFloat(section, XorStr("|Fov"), w.Fov);
				writer.WriteInteger(section, XorStr("|Bone"), w.Bone);
				writer.WriteBoolean(section, XorStr("|Nearest"), w.Nearest);
				writer.WriteInteger(section, XorStr("|NearestType"), w.NearestType);
				writer.WriteFloat(section, XorStr("|Smooth"), w.Smooth);
				writer.WriteBoolean(section, XorStr("|FireDelayEnabled"), weapons[i].FireDelayEnabled);
				writer.WriteBoolean(section, XorStr("|FireDelayRepeat"), weapons[i].FireDelayRepeat);
				writer.WriteFloat(section, XorStr("|FireDelay"), weapons[i].FireDelay);
				writer.WriteInteger(section, XorStr("|StartBullet"), w.StartBullet);
				writer.WriteInteger(section, XorStr("|EndBullet"), w.EndBullet);
				writer.WriteInteger(section, XorStr("|RcsX"), w.RcsX);
				writer.WriteInteger(section, XorStr("|RcsY"), w.RcsY);

				writer.WriteBoolean(section, XorStr("|pSilent"), w.pSilent);
				writer.WriteInteger(section, XorStr("|pSilentBullet"), w.pSilentBullet);
				writer.WriteInteger(section, XorStr("|pSilentPercentage"), w.pSilentPercentage);
				writer.WriteFloat(section, XorStr("|pSilentFov"), w.pSilentFov);
				writer.WriteFloat(section, XorStr("|pSilentSmooth"), w.pSilentSmooth);
			}

			writer.WriteBoolean(section, XorStr("|ChangerEnabled"), w.ChangerEnabled);
			writer.WriteInteger(section, XorStr("|ChangerSkin"), w.ChangerSkin);
			writer.WriteString(section, XorStr("|ChangerName"), w.ChangerName);
			writer.WriteInteger(section, XorStr("|ChangerStatTrak"), w.ChangerStatTrak);
			writer.WriteInteger(section, XorStr("|ChangerSeed"), w.ChangerSeed);
			writer.WriteFloat(section, XorStr("|ChangerWear"), w.ChangerWear);
		}
	}
}