#pragma once

//class IMatRenderContext;

class IMatRenderContext
{
public:
	void Scale(float x, float y, float z)
	{
		typedef void(__thiscall* ScaleFn)(void*, float x, float y, float z);
		CallVFunc<ScaleFn>(this, 35)(this, x, y, z);
	}
};