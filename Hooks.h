#include "SDK.h"
#include "Player.h"
#include "BaseWeapon.h"
#include "CBaseAttributableItem.h"
#include "Draw.h"
#include "Vars.h"
#include "VTableHook.h"
#include "THook.h"
#include "vthook.h"

#include "DXDraw.h"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

HWND g_hWnd;
WNDPROC g_pOldWindowProc = nullptr;
HMODULE thismodule;

typedef long(__stdcall* EndSceneFn)(IDirect3DDevice9* device);
typedef long(__stdcall* ResetFn)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);
typedef long(__stdcall* PresentFn)(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);

typedef float(__stdcall *GetViewModelFOVFn)();
typedef bool(__stdcall * CreateMoveFn)(float flInputSampleTime, CUserCmd* cmd);
typedef void(__stdcall *FrameStageNotifyFn)(ClientFrameStage_t stage);
typedef bool(__thiscall *FireEventClientSideFn)(void*, IGameEvent*);
typedef void(__stdcall *OverrideViewFn)(CViewSetup* vsView);
typedef void(__thiscall *DrawModelExecuteFn)(void*, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld);

namespace O
{
	ResetFn Reset;
	ResetFn Reset2;
	PresentFn Present;
	EndSceneFn EndScene;
	CreateMoveFn CreateMove;
	OverrideViewFn OverrideView;
	GetViewModelFOVFn GetViewModelFOV;
	DrawModelExecuteFn DrawModelExecute;
	FrameStageNotifyFn FrameStageNotify;
	FireEventClientSideFn FireEventClientSide;

	RecvVarProxyFn SequenceProxy;
}

namespace H
{
	bool isEjecting = false;
	CVMTHookManager* DirectX;
	CVMTHookManager* ClientDLL;
	CVMTHookManager* ClientMode;
	CVMTHookManager* ModelRender;
	CVMTHookManager* MDL;
	CVMTHookManager* GameEventManager;
	std::unique_ptr<RecvPropHook> Sequence;
	void Eject()
	{
		G::MenuOpened = false;
		isEjecting = true;
		Sleep(1200);

		H::ClientDLL->UnHook();
		H::ClientMode->UnHook();
		H::ModelRender->UnHook();
		H::GameEventManager->UnHook();

		SetWindowLongPtrW(g_hWnd, GWLP_WNDPROC, (LONG_PTR)g_pOldWindowProc);
		FreeLibraryAndExitThread(thismodule, 0);
	}
}




