#pragma once

#include "Entity.h"
#include "Points.h"
#include "Coords.h"

#include <iostream>

class CCollisionHandler
{
public:	
	// sphere to sphere collision between player and AI
	bool S2SPlayerAI(CPacDude* player, CGhostDude* AI);
	bool S2SPlayerPoints(CPacDude* player, CPoints points[]);
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

bool S2SPlayerPoints(CPacDude* player, CPoints points[])
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
		points->mModel->SetSkin("black.png");
		return true;
	}
	else
	{
		return false;
	}
}