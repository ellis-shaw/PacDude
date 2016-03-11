#pragma once

#include "enumeratedTypes.h"
#include "PacDude.h"

const EKeyCode MoveNorth = Key_W;
const EKeyCode MoveEast = Key_D;
const EKeyCode MoveSouth = Key_S;
const EKeyCode MoveWest = Key_A;

void ListenforPlayerInput(I3DEngine* myEngine, CPacDude* Player)
{
	//keyboard listeners for the player's movement
	if (myEngine->KeyHit(Key_W))
	{
		Player->mDirection = N;
		Player->SetSpeed(Player->mSpeedMultiplier);
		Player->SnapX();
	}
	if (myEngine->KeyHit(Key_D))
	{
		Player->mDirection = E;
		Player->SetSpeed(Player->mSpeedMultiplier);
		Player->SnapZ();
	}
	if (myEngine->KeyHit(Key_S))
	{
		Player->mDirection = S;
		Player->SetSpeed(Player->mSpeedMultiplier);
		Player->SnapX();
	}
	if (myEngine->KeyHit(Key_A))
	{
		Player->mDirection = W;
		Player->SetSpeed(Player->mSpeedMultiplier);
		Player->SnapZ();
	}
}
