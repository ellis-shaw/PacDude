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
	void MoveDude(CTile tiles[gGridHeight][gGridWidth]);
	bool AIcollisionWithPlayer(CPacDude* Player);
	virtual void PathFind(CGhostDude, CPacDude);
};

CGhostDude::CGhostDude(IMesh* cubeMESH, int pos)
{
	mModel = cubeMESH->CreateModel(pos + 20.0f, 0.35f, pos + 19.0f);
	mModel->SetSkin("red.png");
	mVulnverable = false;
	mDefaultSpeed = 0.02f;
}

void CGhostDude::MoveDude(CTile tiles[gGridHeight][gGridWidth])
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

bool CGhostDude::AIcollisionWithPlayer(CPacDude* Player)
{
	//sphere to sphere collision detection
	float playerRadius = 0.5f;
	float dotRadius = 0.0f;

	float x, z;
	x = Player->mModel->GetX() - mModel->GetX();
	z = Player->mModel->GetZ() - mModel->GetZ();

	float collisionDist = sqrt(x*x + z*z);

	if (collisionDist < playerRadius + dotRadius)
	{
		//collision occoured
		mModel->SetSkin("green.png");
		return true;
	}
	else
	{
		return false;
	}
}

void CGhostDude::PathFind(CGhostDude, CPacDude) {}