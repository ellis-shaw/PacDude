#pragma once

#include "Entity.h"
#include "Points.h"
#include "PowerUp.h"
#include "Coords.h"

#include <iostream>

class CCollisionHandler
{
public:	
	// sphere to sphere collision between player and AI
	bool S2SPlayerAI		(CPacDude* player, CGhostDude* AI);
	bool S2SPlayerPoints	(CPacDude* player, CPoints* points);
	bool S2SPlayerPowerUp	(CPacDude* player, CPowerUpBase* powerUp);
};

bool CCollisionHandler::S2SPlayerAI(CPacDude* player, CGhostDude* AI)
{
	// simulate size of player and ai. may not be accurate
	float Radius = 0.2f;

	float x = player->mModel->GetX() - AI->mModel->GetX();
	float z = player->mModel->GetZ() - AI->mModel->GetZ();

	float collisionDistance = sqrt(x*x + z*z);

	return (collisionDistance < Radius);
}

bool CCollisionHandler::S2SPlayerPoints(CPacDude * player, CPoints * points)
{
	//sphere to sphere collision detection
	float playerRadius = 0.5f;
	float dotRadius = 0.0f;

	float x, z;
	x = player->mModel->GetX() - points->mCoords.x;
	z = player->mModel->GetZ() - points->mCoords.z;

	float collisionDist = sqrt(x*x + z*z);

	if (collisionDist < playerRadius + dotRadius)
	{
		points->mModel->SetPosition(0, 200, 0);
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionHandler::S2SPlayerPowerUp(CPacDude* player, CPowerUpBase* powerUp)
{
	//sphere to sphere collision detection
	float playerRadius = 0.5f;
	float dotRadius = 0.0f;

	float x, z;
	x = player->mModel->GetX() - powerUp->mCoords.x;
	//y = Player.mModel->GetY() - mModel->GetY();
	z = player->mModel->GetZ() - powerUp->mCoords.z;

	float collisionDist = sqrt(x*x + z*z);

	if (collisionDist < playerRadius + dotRadius)
	{
		//collision occoured
		powerUp->mModel->SetPosition(0, 200, 0);
		powerUp->mEaten = true;
		return true;
	}
	else
	{
		return false;
	}
}
