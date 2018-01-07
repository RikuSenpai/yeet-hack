#pragma once

#define IsInRange(x, a, b) (x >= a && x <= b)
#define GetBits(x) (IsInRange(x, '0', '9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xA))
#define GetByte(x) (GetBits(x[0]) << 4 | GetBits(x[1]))

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin)

#include "Enums.h"
#include "Structs.h"

#include "CUserCmd.h"
#include "CBaseHudChat.h"
#include "ClientClass.h"

#include "IBaseClientDLL.h"
#include "IClientMode.h"
#include "IInputSystem.h"
#include "IVEngineClient.h"
#include "ICollideable.h"
#include "IClientEntity.h"
#include "IClientEntityList.h"
#include "IPanel.h"
#include "ICVar.h"
#include "ISurface.h"
#include "IVModelInfoClient.h"
#include "IVRenderView.h"
#include "IMaterial.h"
#include "IMaterialSystem.h"
#include "IVModelRender.h"
#include "IMatRenderContext.h"
#include "IGameMovement.h"
#include "CGlobalVars.h"
#include "IPlayerInfoManager.h"
#include "IViewRender.h"
#include "ITraceFilter.h"
#include "CTraceFilter.h"
#include "CTraceFilterSkipTwoEntities.h"
#include "CBaseTrace.h"
#include "CGameTrace.h"
#include "IEngineTrace.h"
#include "IGameEvents.h"
#include "IVDebugOverlay.h"
#include "RecvPropHook.h"

#include "ImGUI\imgui.h"
#include "ImGUI\DX9\imgui_impl_dx9.h"


//#include "Includes.h"

class CNetVars;

///<summary>Use this to Read pointer: ReadPtrTemp:int*:Temp(PlayerBase, offset)</summary>
template<typename T>
inline T ReadPtr(void* base, unsigned long offset)
{
	return *(T*)((char*)base + offset);
}

struct ColorRGBExp32
{
	byte r, g, b;
	signed char exponent;

};

struct dlight_t
{
	int		flags;
	Vector3	origin;
	float	radius;
	ColorRGBExp32	color;
	float	die;
	float	decay;
	float	minlight;
	int		key;
	int		style;
	Vector3	m_Direction;
	float	m_InnerAngle;
	float	m_OuterAngle;
	float GetRadius() const
	{
		return radius;
	}
	float GetRadiusSquared() const
	{
		return radius * radius;
	}
	float IsRadiusGreaterThanZero() const
	{
		return radius > 0.0f;
	}
};

class IVEffects
{
public:
	dlight_t* CL_AllocDlight(int key)
	{
		typedef dlight_t*(__thiscall* OriginalFn)(PVOID, int);
		return CallVFunc<OriginalFn>(this, 4)(this, key);
	}

	dlight_t* CL_AllocElight(int key)
	{
		typedef dlight_t*(__thiscall* OriginalFn)(PVOID, int);
		return CallVFunc<OriginalFn>(this, 5)(this, key);
	}

	dlight_t* GetElightByKey(int key)
	{
		typedef dlight_t*(__thiscall* OriginalFn)(PVOID, int);
		return CallVFunc<OriginalFn>(this, 8)(this, key);
	}

};

class Interface_
{
public:
	IBaseClientDLL* Client = nullptr;
	IClientMode* ClientMode = nullptr;
	IClientEntityList* EntityList = nullptr;
	IVEngineClient* Engine = nullptr;
	CGlobalVars* Globals = nullptr;
	IVEffects* Dilight = nullptr;
	IMDLCache* MDLCache = nullptr;
	IGameMovement* GameMovement = nullptr;
	IPlayerInfoManager* PlayerInfoManager = nullptr;
	IEngineTrace* EngineTrace = nullptr;
	IVModelInfoClient* ModelInfo = nullptr;
	IVModelRender* ModelRender = nullptr;
	IVRenderView* RenderView = nullptr;
	IMaterialSystem* MatSystem = nullptr;
	IVDebugOverlay* DebugOverlay = nullptr;
	IGameEventManager2* GameEventsManager = nullptr;
	IViewRender* ViewRender = nullptr;
	IInputSystem* Input = nullptr;
	ICVar* CVar = nullptr;
};

class NetVars_
{
public:
	DWORD m_rgflCoordinateFrame = 0;
	DWORD m_Collision = 0;
	DWORD m_vecOrigin = 0;
	DWORD m_vecViewOffset = 0;
	DWORD m_vecPunchAngles = 0;
	DWORD m_vecViewPunchAngles = 0;
	DWORD m_vecVelocity = 0;
	DWORD m_bIsScoped = 0;
	DWORD m_lifeState = 0;
	DWORD m_fFlags = 0;
	DWORD m_iHealth = 0;
	DWORD m_iTeamNum = 0;
	DWORD m_iGlowIndex = 0;
	DWORD m_iShotsFired = 0;
	DWORD m_flFlashMaxAlpha = 0;
	DWORD m_hActiveWeapon = 0;
	DWORD m_hMyWeapons = 0;
	DWORD m_nHitboxSet = 0;
	DWORD m_nModelIndex = 0;
	DWORD m_hOwner = 0;
	DWORD m_hWeapon = 0;
	DWORD m_hViewModel = 0;
	DWORD m_nTickBase = 0;
	DWORD m_hObserverTarget = 0;
	DWORD m_flC4Blow = 0;
	DWORD m_flTimerLength = 0;
	DWORD m_hMyWearables = 0;

	DWORD m_iAccountID = 0;
	DWORD m_iItemDefinitionIndex = 0;
	DWORD m_iItemIDHigh = 0;
	DWORD m_iEntityQuality = 0;
	DWORD m_szCustomName = 0;
	DWORD m_nFallbackPaintKit = 0;
	DWORD m_flFallbackWear = 0;
	DWORD m_nFallbackSeed = 0;
	DWORD m_nFallbackStatTrak = 0;
	DWORD m_OriginalOwnerXuidLow = 0;
	DWORD m_OriginalOwnerXuidHigh = 0;

	//Weapons
	DWORD m_flNextPrimaryAttack = 0;
	DWORD m_flNextSecondaryAttack = 0;
	DWORD m_iClip1 = 0;
	DWORD m_iClip2 = 0;
};
class Resolver_
{
public:
	std::shared_ptr<CNetVars> NetVars = nullptr;
};

class Offsets_
{
public:
	DWORD FullUpdate = NULL;
	DWORD RevealRanks = NULL;
	DWORD worldToScreen = NULL;
	DWORD TraceRay = NULL;
	DWORD InitKeyValuesEx = NULL;
	DWORD LoadFromBufferEx = NULL;
	DWORD LineGoesThroughSmoke = NULL;
};

class KnifeModels_
{
public:
	int DefaultTT = 0;
	int DefaultCT = 0;

	int Bayonet = 0;
	int M9Bayonet = 0;
	int Butterfly = 0;
	int Flip = 0;
	int GunGame = 0;
	int Gut = 0;
	int Karambit = 0;
	int Huntsman = 0;
	int Bowie = 0;
	int Falchion = 0;
	int Dagger = 0;
};

extern Interface_ Interface;
extern NetVars_ NetVars;
extern Resolver_ Resolver;
extern Offsets_ Offsets;
extern KnifeModels_ KnifeModels;


enum EClassIds : int
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBreakableProp,
	CBreakableSurface,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPlantedC4,
	CPlasma,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail
};

/*enum Hitboxes
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};*/