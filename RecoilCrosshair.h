#include "SDK.h"

class CPlayer;

class CRecoilCrosshair
{
public:
	void Main(CUserCmd* cmd);
	void Render(CPlayer* pLocal);

private:
	CUserCmd* m_pCmd;
};

extern CRecoilCrosshair* RecoilCrosshair;