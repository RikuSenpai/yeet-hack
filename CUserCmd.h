#include "Includes.h"

///<summary>CUserCmd most valuable class, it's controls player interactions in MP</summary> 
class CUserCmd
{
public:
	virtual ~CUserCmd() { };

	int		command_number;		
	int		tick_count;			
	Vector3	viewangles;			
	Vector3	aimdirection;		
	float	forwardmove;		
	float	sidemove;			
	float	upmove;				
	int		buttons;			
	byte    impulse;			
	int		weaponselect;		
	int		weaponsubtype;		
	int		random_seed;		
	short	mousedx;			
	short	mousedy;			
	bool	hasbeenpredicted;	
	char	pad_0x4C[0x18];		// 0x4C Current sizeof( usercmd ) =  100  = 0x64
};