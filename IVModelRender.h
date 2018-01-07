#pragma once
#include "Includes.h"
#include "IMaterial.h"
#include "IMatRenderContext.h"

class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL, int unk = 0)
	{
		typedef void(__thiscall* ForcedMaterialOverrideFn)(void*, IMaterial*, OverrideType_t, int);
		CallVFunc<ForcedMaterialOverrideFn>(this, 1)(this, newMaterial, nOverrideType, unk);
	}

	void DrawModelExecute(IMatRenderContext* matctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4* pCustomBoneToWorld)
	{
		typedef void(__thiscall* DrawModelExecuteFn)(void*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);
		CallVFunc<DrawModelExecuteFn>(this, 21)(this, matctx, state, pInfo, pCustomBoneToWorld);
	}
};