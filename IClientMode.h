#pragma once
#include "CBaseHudChat.h"

class CBaseEntity
{

};
class IPanel;

class IClientMode
{
public:
	virtual             ~IClientMode() {}
	virtual int         ClientModeCSNormal(void *) = 0;
	virtual void        Init() = 0;
	virtual void        InitViewport() = 0;
	virtual void        Shutdown() = 0;
	virtual void        Enable() = 0;
	virtual void        Disable() = 0;
	virtual void        Layout() = 0;
	virtual IPanel*     GetViewport() = 0;
	virtual void*       GetViewportAnimationController() = 0;
	virtual void        ProcessInput(bool bActive) = 0;
	virtual bool        ShouldDrawDetailObjects() = 0;
	virtual bool        ShouldDrawEntity(CBaseEntity *pEnt) = 0;
	virtual bool        ShouldDrawLocalPlayer(CBaseEntity *pPlayer) = 0;
	virtual bool        ShouldDrawParticles() = 0;
	virtual bool        ShouldDrawFog(void) = 0;
	virtual void        OverrideView(CViewSetup *pSetup) = 0; // 16
	virtual int         KeyInput(int down, int keynum, const char *pszCurrentBinding) = 0; // 17
	virtual void        StartMessageMode(int iMessageModeType) = 0; //18
	virtual IPanel*     GetMessagePanel() = 0; //19
	virtual void        OverrideMouseInput(float *x, float *y) = 0; //20
	virtual bool        CreateMove(float flInputSampleTime, void* usercmd) = 0; // 21
	virtual void        LevelInit(const char *newmap) = 0;
	virtual void        LevelShutdown(void) = 0;
	virtual bool		ShouldDrawViewModel(void) = 0;
	virtual bool		ShouldDrawCrosshair(void) = 0;
};