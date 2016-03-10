// ProfSkillsRefactor.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <fstream>
#include "Entity.h"
#include "PacDude.h"
#include "GhostDude.h"
#include "Points.h"
#include "Tiles.h"
#include "PowerUpBase.h"
#include "PowerUp.h"
#include "PowerUp2.h"
#include "PowerUp3.h"
#include "GlobalScopeVars.h"
#include "KeyboardListeners.h"
using namespace tle;

const int gNumPoints = 10000;
const int gNumPowerUps = 10;

void LoadMap();
void ReadGrid(ifstream &mapFile, CTile tiles[gGridWidth][gGridWidth]);
void InitialiseTiles_XandZ(CTile tiles[gGridWidth][gGridWidth], IMesh* tileMESH, IMesh* cubeMESH);
void InitialiseTiles_TerrainAndTexture(CTile tiles[gGridWidth][gGridWidth], CPoints* Points[gNumPoints], int& activePointCount, CPowerUpBase* PowerUps[gNumPowerUps], int& activePowerUpCount, IMesh* cubeMESH);

void test(EKeyCode key)
{

}

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( ".\\Media" );
	/**** Set up your scene here ****/
	ICamera* myCamera = myEngine->CreateCamera(kManual);
	//camera1
	myCamera->SetPosition(10.0f, 25.0f, 4.0f);
	myCamera->RotateX(90);

	IFont* myFont = myEngine->LoadFont("font1.bmp");

	//load meshes
	IMesh* tileMESH = myEngine->LoadMesh("Square.x");
	IMesh* cubeMESH = myEngine->LoadMesh("state.x");

	//Set up Player
	CPacDude Player(cubeMESH);
	myCamera->AttachToParent(Player.mModel);

	//Set up AI
	const int numGhosts = 2;
	CGhostDude AI = CGhostDude(cubeMESH, 0);

	//set up points
	CPoints* Points[gNumPoints];
	int activePointCount = 0;

	//set up powerups
	CPowerUpBase* PowerUps[gNumPowerUps];
	int activePowerUpCount = 0;
	bool PowerUp_ACTIVE = false;
	int frameCount = 0;

	//set up the grid of tiles
	CTile tiles[gGridWidth][gGridWidth];
	InitialiseTiles_XandZ(tiles, tileMESH, cubeMESH);

	ifstream CoordinateFile;
	CoordinateFile.open("eMap.txt");
	ReadGrid(CoordinateFile, tiles);
	CoordinateFile.close();
	InitialiseTiles_TerrainAndTexture(tiles, Points, activePointCount, PowerUps, activePowerUpCount, cubeMESH);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		//save the player's last position
		Player.PreviousPos.x = round(Player.mModel->GetX());
		Player.PreviousPos.z = round(Player.mModel->GetZ());

		string output;
		myFont->Draw("Speed: ", 10, 10);
		output = to_string(Player.mSpeed);
		myFont->Draw(output, 80, 10);

		/**** Update your scene each frame here ****/
		//if any key is hit
		if (myEngine->AnyKeyHit())
		{
			//handle the players movement
			ListenforPlayerInput(myEngine, &Player);
		}
		Player.MoveDude(tiles); //move the player in their direction

		//-------------------both of the following loops are inneficient because we are checking everything every frame

		//loop the number of active points, and run player to point collision //------------------------by making a class that contains a vector of points could help 
		for (int i = 0; i < activePointCount; i++)
		{
			Points[i]->PlayerCollisionDetection(Player);
		}

		//loop the number of powerups, and run the player collision //------------------------
		for (int i = 0; i < activePowerUpCount; i++)
		{
			if (!PowerUps[i]->mEaten && PowerUps[i]->PlayerCollisionDetection(Player))
			{
				PowerUps[i]->PowerUpEffect(&Player);
				PowerUp_ACTIVE = true;
			}
		}

		//timer to deactivate powerup
		if (PowerUp_ACTIVE)
		{
			float timer = myEngine->Timer();
			float fps = 1 / timer;
			frameCount++;

			if (frameCount > (fps * 10))
			{
				frameCount = 0;
				PowerUp_ACTIVE = false;
				Player.mVulnverable = true;
				Player.mModel->SetSkin("yellow.png");
				Player.mSpeedMultiplier = 1;
				Player.SetSpeed(Player.mSpeedMultiplier);
			}
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

void LoadMap()
{

}

void ReadGrid(ifstream &mapFile, CTile tiles[gGridWidth][gGridWidth])
{
	char ch; //temp holder for data being read in

	if (mapFile.is_open())
	{
		//read in Z inversely (from 9 -> 0)
		for (int z = gGridWidth - 1; z >= 0; z--)
		{
			for (int x = 0; x < gGridWidth; x++)
			{
				mapFile >> ch;
				switch (ch)
				{
				case '0':
					tiles[z][x].terrain = Wall;
					break;
				case '1':
					tiles[z][x].terrain = Open;
					break;
				case '2':
					tiles[z][x].terrain = Wood;
					break;
				case '3':
					tiles[z][x].terrain = Water;
					break;
				default:
					break;
				}
			}
		}
	}
}

//Constructor style for grid //cannot be in constructor because the constructor gives them all the same value 
void InitialiseTiles_XandZ(CTile tiles[gGridWidth][gGridWidth], IMesh* tileMESH, IMesh* cubeMESH)
{
	//this method initilaises the tiles matrix (models, state models, coordinates and states)
	for (int z = 0; z < gGridWidth; z++)
	{
		for (int x = 0; x < gGridWidth; x++)
		{
			tiles[z][x].coords.x = x;
			tiles[z][x].coords.z = z;
			tiles[z][x].model = tileMESH->CreateModel(tiles[z][x].coords.x, 0.0f, tiles[z][x].coords.z);
		}
	}
}

//Method sets the tile's textures to match the terrain
void InitialiseTiles_TerrainAndTexture(CTile tiles[gGridWidth][gGridWidth], CPoints* Points[gNumPoints], int& activePointCount, CPowerUpBase* PowerUps[gNumPowerUps], int& activePowerUpCount, IMesh* cubeMESH)
{
	//loop the tiles matrix
	for (int z = 0; z < gGridWidth; z++)
	{
		for (int x = 0; x < gGridWidth; x++)
		{
			//set the texture of the tile to correspond with its terrain
			switch (tiles[z][x].terrain)
			{
			case Wall:
				tiles[z][x].model->SetSkin("black.PNG");
				break;
			case Open:
				tiles[z][x].model->SetSkin("white.PNG");
				Points[activePointCount] = new CPoints(cubeMESH, tiles[z][x].coords);
				activePointCount++;
				break;
			case Wood:
				tiles[z][x].model->SetSkin("white.PNG");
				if (activePowerUpCount % 3 == 0)
				{
					PowerUps[activePowerUpCount] = new CPowerUp(cubeMESH, tiles[z][x].coords);
				}
				else if (activePowerUpCount % 2 == 0)
				{
					PowerUps[activePowerUpCount] = new CPowerUp2(cubeMESH, tiles[z][x].coords);
				}
				else
				{
					PowerUps[activePowerUpCount] = new CPowerUp3(cubeMESH, tiles[z][x].coords);
				}
				activePowerUpCount++;
				break;
			case Water:
				tiles[z][x].model->SetSkin("blue.PNG");
				break;

			default:
				break;
			}
		}
	}
}