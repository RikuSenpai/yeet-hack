#pragma once
#include "Includes.h"

class CBaseHudChat
{
public:
	///<summary>Print in chat using const char</summary>
	void ChatPrintf(int iPlayerIndex, int iFilter, const char* fmt, ...)
	{
		typedef void(__cdecl* ChatPrintfFn)(void*, int, int, const char*, ...);
		return CallVFunc<ChatPrintfFn>(this, 26)(this, iPlayerIndex, iFilter, fmt);
	}

	///<summary>Print in chat using const wchar_t</summary>
	void ChatPrintfW(int iPlayerIndex, int iFilter, const wchar_t* fmt, ...)
	{
		typedef void(__cdecl* ChatPrintfWFn)(void*, int, int, const wchar_t*, ...);
		return CallVFunc<ChatPrintfWFn>(this, 27)(this, iPlayerIndex, iFilter, fmt);
	}
};