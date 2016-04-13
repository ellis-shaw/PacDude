#pragma once
#include <TL-Engine.h>
#include "Entity.h"
#include "Coords.h"
#include "PacDude.h"
using namespace tle;

class CPowerUpBase
{
public:
	IModel* mModel;
	SCoords mCoords;
	bool mEaten;
	//needs a timer

	virtual void PowerUpEffect(CPacDude* Player) = 0;

	bool PlayerCollisionDetection(CPacDude* Player);

	CPowerUpBase();
	CPowerUpBase(IMesh*, SCoords);
};

CPowerUpBase::CPowerUpBase()
{
}

CPowerUpBase::CPowerUpBase(IMesh* cubeMESH, SCoords p)
{
	mCoords = p;
	mModel = cubeMESH->CreateModel(p.x, 0.0f, p.z);
	mModel->Scale(0.5f);
	mModel->SetSkin("purple.png");
	mEaten = false;
}

bool CPowerUpBase::PlayerCollisionDetection(CPacDude* Player)
{
	//sphere to sphere collision detection
	float playerRadius = 0.5f;
	float dotRadius = 0.0f;

	float x, z;
	x = Player->mModel->GetX() - mCoords.x;
	//y = Player.mModel->GetY() - mModel->GetY();
	z = Player->mModel->GetZ() - mCoords.z;

	float collisionDist = sqrt(x*x + z*z);

	// obsolete
	if (collisionDist < playerRadius + dotRadius)
	{
		//collision occoured
		mModel->SetPosition(0, 200, 0);
		mEaten = true;
		return true;
	}
	else
	{
		return false;
	}
}