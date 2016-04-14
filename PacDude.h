#ifndef _PACDUDE
#define _PACDUDE

#include "Coords.h"
#include "Entity.h"
#include "Tiles.h"
#include <TL-Engine.h>
using namespace tle;

class CPacDude : public CEntity
{
public:
	IModel* mModel;
	int mPoints;

	void SnapX();//snapping isnt the cleanest
	void SnapZ();
	void MoveDude(CTile tiles[gGridHeight][gGridWidth]);

	CPacDude();
	CPacDude(IMesh*);
};

CPacDude::CPacDude(IMesh* cubeMESH)
{
	mModel = cubeMESH->CreateModel(5.0f, 0.0f, 5.0f);
	mModel->SetSkin("yellow.png");
	mPoints = 0;
	mVulnverable = true;
	mDefaultSpeed = 0.04f;
	mSpeed = 0.0f;
}

void CPacDude::MoveDude(CTile tiles[gGridHeight][gGridWidth])
{
	//move the player in their direction
	switch (mDirection)
	{
	case N:
		//if the next square in the direction the player is traveling isnt a wall
		//THEN move the player
		if (tiles[PreviousPos.z + 1][PreviousPos.x].terrain != Wall)
		{
			mModel->Move(0.0f, 0.0f, mSpeed);
		}
		else //Set the player to the center of the previous square
		{
			mModel->SetPosition(PreviousPos.x, 0.0f, PreviousPos.z);
		}
		break;
	case E:
		if (tiles[PreviousPos.z][PreviousPos.x + 1].terrain != Wall)
		{
			mModel->Move(mSpeed, 0.0f, 0.0f);
		}
		else
		{
			mModel->SetPosition(PreviousPos.x, 0.0f, PreviousPos.z);
		}
		break;
	case S:
		if (tiles[PreviousPos.z - 1][PreviousPos.x].terrain != Wall)
		{
			mModel->Move(0.0f, 0.0f, -mSpeed);
		}
		else
		{
			mModel->SetPosition(PreviousPos.x, 0.0f, PreviousPos.z);
		}
		break;
	case W:
		if (tiles[PreviousPos.z][PreviousPos.x - 1].terrain != Wall)
		{
			mModel->Move(-mSpeed, 0.0f, 0.0f);
		}
		else
		{
			mModel->SetPosition(PreviousPos.x, 0.0f, PreviousPos.z);
		}
		break;
	default:
		break;
	}
}

void CPacDude::SnapX()
{
	mModel->SetX(round(mModel->GetX()));
}

void CPacDude::SnapZ()
{
	mModel->SetZ(round(mModel->GetZ()));
}

#endif