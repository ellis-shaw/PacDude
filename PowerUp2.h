#pragma once

#include <TL-Engine.h>
#include "Entity.h"
#include "Coords.h"
#include "PacDude.h"
#include "PowerUpBase.h"
using namespace tle;

class CPowerUp2 : public CPowerUpBase
{
public:
	//needs a timer

	void PowerUpEffect(CPacDude* Player);

	CPowerUp2();
	CPowerUp2(IMesh*, SCoords);
};

CPowerUp2::CPowerUp2()
{
}

CPowerUp2::CPowerUp2(IMesh* cubeMESH, SCoords p)
{
	mCoords = p;
	mModel = cubeMESH->CreateModel(p.x, 0.0f, p.z);
	mModel->Scale(0.5f);
	mModel->SetSkin("red.png");
	mEaten = false;
}

void CPowerUp2::PowerUpEffect(CPacDude* Player)
{
	Player->mSpeedMultiplier = 0.5;
	Player->SetSpeed(Player->mSpeedMultiplier);
}