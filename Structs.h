#pragma once
#include "Includes.h"
#include "VectorAligned.h"

class model_t;

struct mstudiobone_t
{
	int					sznameindex;
	inline char * const pszName(void) const { return ((char *)this) + sznameindex; }
	int		 			parent;		// parent bone
	int					bonecontroller[6];	// bone controller index, -1 == none

											// default values
	Vector3				pos;
	Vector4			quat;
	Vector3			rot;
	// compression scale
	Vector3				posscale;
	Vector3				rotscale;

	matrix3x4			poseToBone;
	Vector4			qAlignment;
	int					flags;
	int					proctype;
	int					procindex;		// procedural rule
	mutable int			physicsbone;	// index into physically simulated bone
	inline void *pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
	int					surfacepropidx;	// index into string tablefor property name
	inline char * const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
	inline int			GetSurfaceProp(void) const { return surfacepropLookup; }

	int					contents;		// See BSPFlags.h for the contents flags
	int					surfacepropLookup;	// this index must be cached by the loader, not saved in the file
	int					unused[7];		// remove as appropriate

	mstudiobone_t() {}
private:
	// No copy constructors allowed
	mstudiobone_t(const mstudiobone_t& vOther);
};

///<summary>Bounding boxes</summary>
struct mstudiobbox_t
{
	int		bone;
	int		group;
	Vector3	bbmin;
	Vector3	bbmax;
	int		hitboxnameindex;
	int		pad[3];
	float	m_flRadius;
	int		pad2[4];

	char* getHitboxName()
	{
		if (hitboxnameindex == 0)
			return "";

		return ((char*)this) + hitboxnameindex;
	}
};

///<summary>Hitboxes stuff</summary>
struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char * const	pszName(void) const { return ((char *)this) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t*)(((unsigned char*)this) + hitboxindex) + i; };
};

#define  Assert( _exp )										((void)0)
///<summary>Hitboxes stuff</summary>
struct studiohdr_t
{
	int					id;
	int					version;
	long				checksum;
	char				name[64];
	int					length;
	Vector3				eyeposition;
	Vector3				illumposition;
	Vector3				hull_min;
	Vector3				hull_max;
	Vector3				view_bbmin;	
	Vector3				view_bbmax;
	int					flags;
	int					numbones;
	int					boneindex;
	int					numbonecontrollers;
	int					bonecontrollerindex;
	int					numhitboxsets;
	int					hitboxsetindex;
	int					numlocalanim;
	int					localanimindex;
	int					numlocalseq;
	int					localseqindex;
	mutable int			activitylistversion;
	mutable int			eventsindexed;
	int					numtextures;
	int					textureindex;
	int					numcdtextures;
	int					cdtextureindex;
	int					numskinref;
	int					numskinfamilies;
	int					skinindex;
	int					numbodyparts;
	int					bodypartindex;


	/*unsigned char		pad00[12];
	char				name[64];
	unsigned char		pad01[80];
	int					numbones;
	int					boneindex;
	unsigned char		pad02[12];
	int					hitboxsetindex;
	unsigned char		pad03[228];*/

	inline mstudiobone_t *pBone(int i) const { Assert(i >= 0 && i < numbones); return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };
	//inline mstudiobone_t *pBone(int i) const { return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };

	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((unsigned char *)this) + hitboxsetindex) + i;
	};

	mstudiobbox_t* pHitbox(int i, int set) const
	{
		const mstudiohitboxset_t* s = pHitboxSet(set);
		if (!s)
			return NULL;

		return s->pHitbox(i);
	};

	int			iHitboxCount(int set) const
	{
		const mstudiohitboxset_t* s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};
};

///<summary>Source engine model information
struct ModelRenderInfo_t
{
	Vector3 origin;
	Vector3 angles;
	void* pRenderable;
	model_t* pModel;
	matrix3x4* pModelToWorld;
	matrix3x4* pLightingOffset;
	Vector3* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = nullptr;
		pLightingOffset = nullptr;
		pLightingOrigin = nullptr;
	}
};

///<summary>MP player info</summary>
typedef struct player_info_s
{
	DWORD __pad0[2];
	int xuidlow;
	int xuidhigh;
	char name[128];//32
	int userid;
	char steamid[33];//32
	UINT steam3id;
	char friendsname[128];
	bool isfakeplayer;
	bool ishltv;
	DWORD customfiles[4];
	BYTE filesdownloaded;
	int __pad1;
} player_info_t;

///<summary>ViewSetup of client 'vision'</summary>
struct CViewSetup
{
	char _0x0000[16];
	__int32 x;
	__int32 x_old;
	__int32 y;
	__int32 y_old;
	__int32 width;
	__int32    width_old;
	__int32 height;
	__int32    height_old;
	char _0x0030[128];
	float fov;
	float fovViewmodel;
	Vector3 origin;
	Vector3 angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	float m_nDoFQuality;
	__int32 m_nMotionBlurMode;
	char _0x0104[68];
	__int32 m_EdgeBlur;
};


struct csurface_t
{
	const char		*name;
	short			surfaceProps;
	unsigned short	flags;
};

///<summary>Used in tracing</summary>
struct cplane_t
{
	Vector3	normal;
	float	dist;
	BYTE	type;
	BYTE	signbits;
	BYTE	pad[2];
};

struct Ray_t
{
	VectorAligned   m_Start;
	VectorAligned   m_Delta;
	VectorAligned   m_StartOffset;
	VectorAligned   m_Extents;

	const   matrix3x4* m_pWorldAxisTransform;

	bool    m_IsRay;
	bool    m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(0) { }

	void Init(Vector3& start, Vector3& end)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.Set();
		m_pWorldAxisTransform = 0;
		m_IsRay = true;

		m_StartOffset.Set();
		m_Start = start;
	}

	void Init(Vector3& start, Vector3& end, Vector3& mins, Vector3& maxs)
	{
		m_Delta = end - start;

		m_pWorldAxisTransform = 0;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		m_StartOffset = mins + maxs;
		m_StartOffset *= 0.5f;
		m_Start = start - m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

struct DrawModelState_t
{

};