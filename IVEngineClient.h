#pragma once
#include "Includes.h"

class IVEngineClient
{
public:

	///<summary>Mods version number (steam.inf)</summary>
	const char* GetProductVersionString()
	{
		typedef const char*(__thiscall* GetProductVersionStringFn)(void*);
		return CallVFunc<GetProductVersionStringFn>(this, 105)(this);
	}

	///<summary>Gets screen width and height</summary>
	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* GetScreenSizeFn)(void*, int&, int&);
		return CallVFunc<GetScreenSizeFn>(this, 5)(this, width, height);
	}

	///<summary>Executeing console command, works only with client commands</summary>
	void ExecuteConsoleCommand(const char* szCommandString)
	{
		/*typedef void(__thiscall* ClientCmdFn)(void*, const char*);
		return CallVFunc<ClientCmdFn>(this, 7)(this, szCommandString);*/

		typedef void(__thiscall* ClientCmdFn)(void*, const char*, bool bDelayed);
		return CallVFunc<ClientCmdFn>(this, 114)(this, szCommandString, 0);
	}

	///<summary>Getting player info: setamid, name e.t.c</summary>
	bool GetPlayerInfo(int index, player_info_t* pInfo)
	{
		typedef bool(__thiscall* GetPlayerInfoFn)(void*, int, player_info_t*);
		return CallVFunc<GetPlayerInfoFn>(this, 8)(this, index, pInfo);
	}

	int GetPlayerForUserID(int userID)
	{
		typedef int(__thiscall* GetPlayerForUserIDFn)(void*, int);
		return CallVFunc<GetPlayerForUserIDFn>(this, 9)(this, userID);
	}

	///<summary>Returns local player index</summary>
	int GetLocalPlayer()
	{
		typedef int(__thiscall* GetLocalPlayerFn)(void*);
		return CallVFunc<GetLocalPlayerFn>(this, 12)(this);
	}

	///<summary>Returns time (float)</summary>
	float Time()
	{
		typedef float(__thiscall* TimeFn)(void*);
		return CallVFunc<TimeFn>(this, 14)(this);
	}

	///<summary>Returns player viewangles</summary>
	void GetViewAngles(Vector3 &ang)
	{
		typedef void(__thiscall* GetViewAnglesFn)(void*, Vector3&);
		return CallVFunc<GetViewAnglesFn>(this, 18)(this, ang);
	}

	///<summary>Set's player viewangles</summary>
	void SetViewAngles(Vector3 &ang)
	{
		typedef void(__thiscall* SetViewAnglesFn)(void*, Vector3&);
		return CallVFunc<SetViewAnglesFn>(this, 19)(this, ang);
	}

	///<summary>Returns number of client on current server</summary>
	int GetMaxClients()
	{
		typedef int(__thiscall* GetMaxClientsFn)(void*);
		return CallVFunc<GetMaxClientsFn>(this, 20)(this);
	}

	///<summary>If local player is in a game</summary>
	bool IsInGame()
	{
		typedef bool(__thiscall* IsInGameFn)(void*);
		return CallVFunc<IsInGameFn>(this, 26)(this);
	}

	///<summary>Return true if local player connected to an a server</summary>
	bool IsConnected()
	{
		typedef bool(__thiscall* IsConnectedFn)(void*);
		return CallVFunc<IsConnectedFn>(this, 27)(this);
	}

	///<summary>Retruns true if player taking screenshot by F12</summary>
	bool IsTakingScreenshot()
	{
		typedef bool(__thiscall* IsTakingScreenshotFn)(void*);
		return CallVFunc<IsTakingScreenshotFn>(this, 92)(this);
	}

	///<summary>3'd coordinates to 2'd coordinates</summary>
	const matrix3x4& WorldToScreenMatrix()
	{
		typedef const matrix3x4& (__thiscall* GetMatrixFn)(void*);
		return CallVFunc<GetMatrixFn>(this, 37)(this);
	}
};