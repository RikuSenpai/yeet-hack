#pragma once
#include "Includes.h"

class ICollideable
{
public:

	///<summary>Bounding box min position</summary>
	const Vector3& OBBMins()
	{
		typedef const Vector3& (__thiscall* OBBMinsFn)(void*);
		return CallVFunc<OBBMinsFn>(this, 1)(this);
	}

	///<summary>Bounding box max position</summary>
	const Vector3& OBBMaxs()
	{
		typedef const Vector3& (__thiscall* OBBMaxsFn)(void*);
		return CallVFunc<OBBMaxsFn>(this, 2)(this);
	}

	///<summary>Origin of bb</summary>
	const Vector3& GetCollisionOrigin()
	{
		typedef const Vector3& (__thiscall* GetCollisionOriginFn)(void*);
		return CallVFunc<GetCollisionOriginFn>(this, 8)(this);
	}

	///<summary>Angles of bb</summary>
	const Vector3& GetCollisionAngles()
	{
		typedef const Vector3& (__thiscall* GetCollisionAnglesFn)(void*);
		return CallVFunc<GetCollisionAnglesFn>(this, 9)(this);
	}

	///<summary>Allow to transform(kek) collision to world transform</summary>
	const matrix3x4& CollisionToWorldTransform()
	{
		typedef const matrix3x4& (__thiscall* CollisionToWorldTransformFn)(void*);
		return CallVFunc<CollisionToWorldTransformFn>(this, 10)(this);
	}

	///<summary>Returns collision group</summary>
	int GetCollisionGroup()
	{
		typedef int(__thiscall* GetCollisionGroupFn)(void*);
		return CallVFunc<GetCollisionGroupFn>(this, 14)(this);
	}
};