#pragma once

#include "Entity.h"

#include <iostream>

class CCollisionHandler
{
public:	
	// sphere to sphere collision between player and AI
	bool S2SPlayerAI(CPacDude* player, CGhostDude* AI);
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