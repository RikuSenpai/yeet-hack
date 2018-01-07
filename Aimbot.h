#include "SDK.h"

class CPlayer;

class CAimbot
{
public:
	void Init();

	void Main(CPlayer* pLocal, CUserCmd* cmd);
	void Render(CPlayer* pLocal);
	void CalculateAngle(const Vector3& in, Vector3 out);
	int GetBestTargetByDistance();
	int GetBestTargetByCrosshairDistance();
	Vector3 NormalizeAngles(Vector3 AngleToNormalize);

	bool IsPlayerValid(int pIndex);

private:
	CPlayer* m_pLocal;
	int m_iTarget;
	Vector2 ScreenCenter;
};

extern CAimbot* Aimbot;