#ifndef _POINTS
#define _POINTS

#include <iostream>
#include <TL-Engine.h>
#include "Entity.h"
#include "Coords.h"
using namespace tle;

class CPoints
{
public:
	IModel* mModel;
	SCoords mCoords;
	bool mEaten;

	bool PlayerCollisionDetection(CPacDude* Player);

	CPoints();
	CPoints(IMesh*, SCoords);
};

CPoints::CPoints()
{
}

CPoints::CPoints(IMesh* cubeMESH, SCoords p)
{
	mCoords = p;
	mModel = cubeMESH->CreateModel(p.x, 0.0f, p.z);
	mModel->Scale(0.5f);
	mEaten = false;
}

bool CPoints::PlayerCollisionDetection(CPacDude* Player)
{
	//sphere to sphere collision detection
	float playerRadius = 0.5f;
	float dotRadius = 0.0f;

	float x, z;
	x = Player->mModel->GetX() - mCoords.x;
	//y = Player.mModel->GetY() - mModel->GetY();
	z = Player->mModel->GetZ() - mCoords.z;

	float collisionDist = sqrt(x*x + z*z);

	if (collisionDist < playerRadius + dotRadius)
	{		
		//collision occoured
		mModel->SetSkin("black.png");
		return true;
	}
	else
	{
		return false;
	}
}

#endif