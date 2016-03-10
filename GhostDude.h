#pragma once

#include "Coords.h"
#include "Entity.h"
#include "PacDude.h"
#include <TL-Engine.h>
using namespace tle;

class CGhostDude : public CEntity
{
public:
	IModel* mModel;
	CGhostDude();
	CGhostDude(IMesh*, int);
	void SnapX();//snapping isnt the cleanest
	void SnapZ();
	void MoveDude(CTile tiles[gGridWidth][gGridWidth]);
	virtual void PathFind(CGhostDude, CPacDude);
};

CGhostDude::CGhostDude(IMesh* cubeMESH, int pos)
{
	mModel = cubeMESH->CreateModel(pos + 20.0f, 0.0f, pos + 20.0f);
	mModel->SetSkin("red.png");
	mVulnverable = false;
	mDefaultSpeed = 0.02f;
}

void CGhostDude::MoveDude(CTile tiles[gGridWidth][gGridWidth])
{
	//move the player in their direction
	switch (mDirection)
	{
	case N:
		mModel->Move(0.0f, 0.0f, mSpeed);
		break;
	case E:
		mModel->Move(mSpeed, 0.0f, 0.0f);
		break;
	case S:
		mModel->Move(0.0f, 0.0f, -mSpeed);
		break;
	case W:
		mModel->Move(-mSpeed, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void CGhostDude::SnapX()
{
	mModel->SetX(round(mModel->GetX()));
}

void CGhostDude::SnapZ()
{
	mModel->SetZ(round(mModel->GetZ()));
}

void CGhostDude::PathFind(CGhostDude, CPacDude) {}