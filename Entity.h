#pragma once

#include "Coords.h"
#include "enumeratedTypes.h"
#include "Tiles.h"
#include "GlobalScopeVars.h"
#include <TL-Engine.h>
using namespace tle;

class CEntity
{
public:
	SCoords PreviousPos;

	EDirection mDirection;
	float mDefaultSpeed;
	float mSpeed;
	float mSpeedMultiplier = 1;
	bool mVulnverable;

	virtual void SnapX() = 0; //snapping isnt the cleanest
	virtual void SnapZ() = 0;
	virtual void SetSpeed(float);
	virtual void MoveDude(CTile tiles[gGridWidth][gGridWidth]) = 0;
};

void CEntity::SetSpeed(float multiplier)
{
	mSpeed = mDefaultSpeed * multiplier;
}
