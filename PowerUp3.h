#pragma once

#include <TL-Engine.h>
#include "Entity.h"
#include "Coords.h"
#include "PacDude.h"
#include "PowerUpBase.h"
using namespace tle;

class CPowerUp3 : public CPowerUpBase
{
public:
	//needs a timer

	void PowerUpEffect(CPacDude* Player);

	CPowerUp3();
	CPowerUp3(IMesh*, SCoords);
};

CPowerUp3::CPowerUp3()
{
}

CPowerUp3::CPowerUp3(IMesh* cubeMESH, SCoords p)
{
	mCoords = p;
	mModel = cubeMESH->CreateModel(p.x, 0.0f, p.z);
	mModel->Scale(0.5f);
	mModel->SetSkin("orange.png");
	mEaten = false;
}

void CPowerUp3::PowerUpEffect(CPacDude* Player)
{
	Player->mVulnverable = false;
	Player->mModel->SetSkin("orange.png");

}