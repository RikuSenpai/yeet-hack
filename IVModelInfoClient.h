#pragma once
#include "Includes.h"
#include "IMaterial.h"

class IVModelInfoClient
{
public:
	model_t* GetModel(int index)
	{
		typedef model_t*(__thiscall* GetModelFn)(void*, int);
		return CallVFunc<GetModelFn>(this, 1)(this, index);
	}

	int	GetModelIndex(const char* name)
	{
		typedef int(__thiscall* GetModelIndexFn)(void*, const char*);
		return CallVFunc<GetModelIndexFn>(this, 2)(this, name);
	}

	const char* GetModelName(const model_t* model)
	{
		typedef const char* (__thiscall* GetModelNameFn)(void*, const model_t*);
		return CallVFunc<GetModelNameFn>(this, 3)(this, model);
	}

	int GetModelMaterials(const model_t* model)
	{
		typedef int(__thiscall* GetModelNameFn)(void*, const model_t* model);
		return CallVFunc<GetModelNameFn>(this, 16)(this, model);
	}

	void GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterials)
	{
		typedef void(__thiscall* GetModelNameFn)(void*, const model_t *model, int count, IMaterial** ppMaterials);
		return CallVFunc<GetModelNameFn>(this, 17)(this, model, count, ppMaterials);
	}

	studiohdr_t* GetStudiomodel(const model_t* mod)
	{
		typedef studiohdr_t* (__thiscall* GetStudiomodelFn)(void*, const model_t*);
		return CallVFunc<GetStudiomodelFn>(this, 30)(this, mod);
	}
};