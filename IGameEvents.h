#pragma once

class IGameEvent {
public:
	const char* GetName() {
		return CallVFunc<const char*(__thiscall *)(void*)>(this, 1)(this);
	}

	int GetInt(const char* szKeyName, int nDefault = 0) {
		return CallVFunc<int(__thiscall *)(void*, const char*, int)>(this, 6)(this, szKeyName, nDefault);
	}

	const char* GetString(const char* szKeyName) {
		return CallVFunc<const char*(__thiscall *)(void*, const char*, int)>(this, 9)(this, szKeyName, 0);
	}

	void SetString(const char* szKeyName, const char* szValue) {
		return CallVFunc<void(__thiscall *)(void*, const char*, const char*)>(this, 16)(this, szKeyName, szValue);
	}
};

class IGameEventListener2
{
public:
	virtual	~IGameEventListener2(void) {};

	virtual void FireGameEvent(IGameEvent *event) = 0;

	virtual int	 GetEventDebugID(void) = 0;
};

class IGameEventManager2
{
public:
	bool AddListener(IGameEventListener2* listener, const char *name, bool bServerSide) {
		return CallVFunc<bool(__thiscall *)(void*, IGameEventListener2* listener, const char *name, bool bServerSide)>(this, 3)(this, listener, name, bServerSide);
	}
};