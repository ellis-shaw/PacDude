#pragma once

#include <TL-Engine.h>
#include "Entity.h"
#include "Coords.h"
#include "PacDude.h"
#include "PowerUpBase.h"
using namespace tle;

class CPowerUp : public CPowerUpBase
{
public:
	//needs a timer

	void PowerUpEffect(CPacDude* Player);

	CPowerUp();
	CPowerUp(IMesh*, SCoords);
};

CPowerUp::CPowerUp()
{
}

CPowerUp::CPowerUp(IMesh* cubeMESH, SCoords p)
{
	mCoords = p;
	mModel = cubeMESH->CreateModel(p.x, 0.3f, p.z);
	mModel->Scale(0.6f);
	mModel->SetSkin("purple.png");
	mEaten = false;
}

void CPowerUp::PowerUpEffect(CPacDude* Player)
{
	Player->mSpeedMultiplier = 2;
	Player->SetSpeed(Player->mSpeedMultiplier);
}