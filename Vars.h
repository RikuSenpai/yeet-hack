#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#define STICKERS_COUNT 5
class Sticker_t
{
public:
	int iID = 0;
	float flWear = 0.f;
	float flScale = 1.f;
	int iRotation = 0;
};

class Weapon_t
{
public:
	bool Enabled = true;
	float Fov = 4;
	int Bone = 8;
	bool Nearest = false;
	int NearestType = 1;
	float Smooth = 4.5f;
	bool FireDelayEnabled = false;
	bool FireDelayRepeat = false;
	float FireDelay = 2;
	int StartBullet = 0;
	int EndBullet = 0;
	int RcsX = 100;
	int RcsY = 100;
	bool pSilent = true;
	int pSilentPercentage = 70;
	int pSilentBullet = 1;
	float pSilentFov = 1.4;
	float pSilentSmooth = 0;

	bool ChangerEnabled = false;
	int ChangerSkin = 0;
	char ChangerName[32] = "";
	int ChangerStatTrak = 0;
	int ChangerSeed = 0;
	float ChangerWear = 0;

	bool StickersEnabled = false;
	Sticker_t Stickers[STICKERS_COUNT];
};
Weapon_t* weapons = new Weapon_t[520];

struct ColorP
{
public:
	const char* Name;
	float* Ccolor;

	ColorP(const char* name, float* color)
	{
		this->Name = name;
		this->Ccolor = color;
	}
};

struct skinInfo
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};

namespace G
{
	CUserCmd* GlobalCmd_r;
	CPlayer* GlobalLocalPlayer_r;
	float rcol = 0;
	float gcol = 0;
	float bcol = 0;
	float acol = 0;
	bool MenuOpened = false;
	bool PressedKeys[256] = {};
	bool Inited = false;
	bool AllowSilent = false;
	bool ForceFullUpdate = false;
	float KillDelayTime = 0;
	bool KillDelayEnd = false;
	float FireDelayTime = 0;
	bool NextResetRadar = false;
	std::unordered_map<std::string, std::set<std::string>> weaponSkins;
	std::unordered_map<std::string, skinInfo> skinMap;
	std::unordered_map<std::string, std::string> skinNames;
	std::vector<std::string> weaponNames;
	std::vector<ColorP> ColorsForPicker;
	std::vector<CPlayer*> PlayersDrawList;
	std::vector<std::string> EventList;
	std::vector<bool> VisibledPlayers(128);
	IMaterial* chamsNormalMaterial;
	IMaterial* ignoreNormalMaterial;
	IMaterial* chamsFlatMaterial;
	IMaterial* ignoreFlatMaterial;
	IMaterial* fMaterial;

}

namespace Options
{
	namespace Legitbot
	{
		bool l = false;
		bool v = false;
		bool m = false;
		bool s = false;
		bool r = false;
		bool c = false;
		bool Enabled = true;
		bool DrawFov = false;
		bool Deathmatch = false;
		bool SmokeCheck = true;
		bool AutoFire = false;
		int AimType = 0;
		bool KillDelay = true;
		float KillDelayTime = 0.40f;
	}
	namespace Ragebot
	{
		bool Enabled = true;
		bool Silent = true;
		bool Auto = true;
	}
	namespace Visuals
	{
		namespace ESP
		{
			bool Lights;
			float color_dlight[3] = { 0, 1, 0 };
			float color_invis[3] = { 0, 0, 0 };
			float color_vis[3] = { 0, 0, 0 };
			float radar_enVis[3] = { 255,255,255 };
			float radar_enInvis[3] = {0,0,0};
			float radar_team[3] = { 173, 216, 230 };

			float colorbomb[3] = { 0, 0, 0 };
			bool Enabled = true;
			bool EnemyOnly = true;
			bool VisibleOnly = true;
			bool SmokeCheck = true;
			bool Box = true;
			int Style = 1;
			bool Name = true;
			
			
			bool Weapon = true;
			bool skilet = true;
			bool WeaponAmmo = true;
		}
		namespace Health
		{
			bool Health1 = true;
			int Style = 0;
			float color[3] = { 0 ,1 ,0 };
		}

		namespace Chams
		{
			bool Enable = false;
			bool RainBow = false;
			bool VisibleRainBow = false;
			bool InVisibleRainBow = false;
			bool Enabled = true;
			bool EnemyOnly = true;
			bool VisibleOnly = false;
			bool DrawHead = true;
			float color[3] = { 0, 1.f, 0 };
			float coloriz[3] = { 0, 0, 0 };
			float colori[3] = { 0, 0, 0 };
			float colorin[3] = { 0, 0, 0 };
			int Stylez = 0;
		}
		
		namespace Hands
		{
			bool Enabled = false;
			int Style = 1; // 0 - Disabled; 1 - Wireframe; 2 - Chams; 3 - Chams & Wireframe
			float color[3] = { 0, 0.41f, 1 };
		}
		namespace Misc
		{
			int CustomSky;
			bool DropESP = false;
			bool BombTimer = true;
			int ConfigSystem = 1;
			bool Grenades;
			int BombTimerType = 2;
			bool FovChanger = false;
			float FovChangerValue = 90;
			bool ViewmodelChanger = false;
			float ViewmodelChangerValue = 90;
		}
	}
	namespace Radar
	{
		bool Enabled = false;
		int Style = 0; // 0 - External; 1 - In-Game
		int Type = 0; // 0 - Box; 1 - Filled box; 2 - Circle; 3 - Filled circle;
		bool EnemyOnly = true;
		bool VisibleOnly = false;
		bool SmokeCheck = true;
		bool ViewCheck = true;
		int Alpha = 255;
		float Zoom = 1;
	}
	namespace SkinChanger
	{
		bool EnabledSkin = true;
		bool EnabledKnife = true;
		bool EnabledGlove = true;
		int Knife = 4; // 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
		int Glove = 0; // 0 - Bloodhound; 1 - Sport; 2 - Driver; 3 - Wraps; 4 - Moto; 5 - Specialist
		int GloveSkin = 0;

		static char* buf1;
		static char* buf2;
		static char* buf3;
		static char* buf4;
		static char* buf5;
		static char* buf6;
	}
	namespace Misc
	{
		bool AutoAccept = false;
		bool LS = false;
		float r1 = false;
		float g1 = false;
		float b1 = false;
		bool lx = false;
		bool RevealRanks = true;
		bool Bunnyhop = true;
		bool SpectatorList = false;
		bool RecoilCrosshair = false;
		bool SniperCrosshair = true;
		bool HitInfo = true;
		int ConfigSystem = 1;
		bool NoFlash = true;
		bool KnifeBot = false;
		bool AU = true;
		bool KnifeBotAuto = true;
		bool KnifeBot360 = true;
		bool Watermark = true;
		bool AntiAFK = false;
		bool AirStuck = false;
		float SpeedControl = 0.1f;
		float SControl = 0.1f;
		float HControl = 0.1f;
		float NoFlashAlpha = 100;
		bool ClanTagAnim = false;
		int ClanTagAnimStyle = 1;
		char ClanTabAnimText[15] = "";
		bool name = false;
	};
};