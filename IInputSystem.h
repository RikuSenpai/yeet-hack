#pragma once
#include "Includes.h"

class IInputSystem
{
public:
	void IInputSystem::GetCursorPosition(int* m_pX, int* m_pY)
	{
		typedef void(__thiscall* OriginalFn)(void*, int*, int*);
		return CallVFunc<OriginalFn>(this, 56)(this, m_pX, m_pY);
	}

	void IInputSystem::SetMouseCursorVisible(bool visible)
	{
		typedef void(__thiscall* OriginalFn)(void*, bool);
		return CallVFunc<OriginalFn>(this, 59)(this, visible);
	}
};