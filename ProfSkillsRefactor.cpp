// ProfSkillsRefactor.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <fstream>
#include <windows.h>
#include <math.h>

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

#include "MenuSelection.h"
#include "AudioEffects.h"
#include "CollisionHandler.h"

#include <iostream>

using namespace std;
using namespace tle;

// Variables
I3DEngine* myEngine;
HWND hWnd;

// collision handler
CCollisionHandler* cHandler;

IFont* loadingFont;
IFont* frontEndFont;
IFont* gameFont;
IFont* myFont;

IModel* backgroundModel;
IMesh* backgroundMesh;

IModel* floorModel;
IMesh* floorMesh;

IMesh* tileMESH;
IMesh* cubeMESH;

ICamera* cameraMenu;
ICamera* myCamera;

//Set up Player
CPacDude* Player;

//Set up AI
const int numGhosts = 2;
CGhostDude* AI;

const int gNumPoints = 10000;
const int gNumPowerUps = 20;

//set up points
CPoints* Points[gNumPoints];
int activePointCount = 0;

//set up powerups
CPowerUpBase* PowerUps[gNumPowerUps];
int activePowerUpCount = 0;
bool PowerUp_ACTIVE = false;
int frameCount = 0;
float counter = 0.0f;

//set up the grid of tiles
CTile tiles[gGridHeight][gGridWidth];
ifstream CoordinateFile;

int random();

void LoadMap();
void ReadGrid(ifstream &mapFile, CTile tiles[gGridHeight][gGridWidth]);
void InitialiseTiles_XandZ(CTile tiles[gGridHeight][gGridWidth], IMesh* tileMESH, IMesh* cubeMESH);
void InitialiseTiles_TerrainAndTexture(CTile tiles[gGridHeight][gGridWidth], CPoints* Points[gNumPoints], int& activePointCount, CPowerUpBase* PowerUps[gNumPowerUps], int& activePowerUpCount, IMesh* cubeMESH);
void AnimatePowerUps(CPowerUpBase* PowerUps[gNumPowerUps], int activePowerUpCount);

void GameShutdown();
void GameUpdate(float updateTime);
bool GameSetup();
void FrontEndShutdown();
void FrontEndUpdate(float updateTime);
bool FrontEndSetup();
void ProgramShutdown();
bool ProgramSetup();

void main()
{
	// Initialise program (TL-Engine etc.), quit program on failure
	if (!ProgramSetup())
	{
		return;
	}

	// Loop to return to the front-end. while (true) would loop forever, but the return
	// statements inside will exit this loop (and the function/program)
	while (true)
	{
		///////////////////////////////////
		// Front End

		// Set up the game (load meshes, create models etc), quit program on failure
		if (!FrontEndSetup())
		{
			ProgramShutdown();
			return;
		}

		// The front-end loop, repeat until user presses 'Return' to play
		while (!myEngine->KeyHit(Key_Return))
		{
			// Draw the scene
			myEngine->DrawScene();

			// Call FrontEndUpdate passing the latest frame time (time since last frame)
			// Allows us to use the variable timing method
			float frameTime = myEngine->Timer();
			FrontEndUpdate(frameTime);

			// Program exit required (user pressed Q, closed window or pressed Alt-F4)
			if (!myEngine->IsRunning() || GetCurrentSelection() == 1 && myEngine->KeyHit(Key_Return))
			{
				ProgramShutdown();
				return;
			}
		}

		PauseUnPauseSoundTrackMenu();

		// Shutdown the front end
		FrontEndShutdown();
		PlaySoundTrackInGame();

		///////////////////////////////////
		// Loading screen

		// Draw loading screen text
		//loadingFont->Draw("Loading - Please Wait", 640, 360, kBlack, kCentre);
		myEngine->DrawScene();


		///////////////////////////////////
		// Game

		// Set up the game (load meshes, create models etc), quit program on failure
		if (!GameSetup())
		{
			ProgramShutdown();
			return;
		}

		// The game loop, repeat until user presses 'Escape'
		while (!myEngine->KeyHit(Key_Escape))
		{
			// Draw the scene
			myEngine->DrawScene();

			// Call GameUpdate passing the latest frame time (time since last frame)
			// Allows us to use the variable timing method
			float frameTime = myEngine->Timer();
			GameUpdate(frameTime);

			// Immediate program exit required (user closed window or pressed Alt-F4)
			if (!myEngine->IsRunning())
			{
				ProgramShutdown();
				return;
			}
		}

		// Shutdown the front end
		GameShutdown();
	}

}

void ReadGrid(ifstream &mapFile, CTile tiles[gGridHeight][gGridWidth])
{
	char ch; //temp holder for data being read in

	if (mapFile.is_open())
	{
		//read in Z inversely (from 9 -> 0)
		for (int z = gGridHeight - 1; z >= 0; z--)
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
void InitialiseTiles_XandZ(CTile tiles[gGridHeight][gGridWidth], IMesh* tileMESH, IMesh* cubeMESH)
{
	//this method initilaises the tiles matrix (models, state models, coordinates and states)
	for (int z = 0; z < gGridHeight; z++)
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
void InitialiseTiles_TerrainAndTexture(CTile tiles[gGridHeight][gGridWidth], CPoints* Points[gNumPoints], int& activePointCount, CPowerUpBase* PowerUps[gNumPowerUps], int& activePowerUpCount, IMesh* cubeMESH)
{
	//loop the tiles matrix
	for (int z = 0; z < gGridHeight; z++)
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
				//random distribution of 
				if (activePowerUpCount < gNumPowerUps)
				{
					if (random() % 2 == 0)
					{
						//positive powerup
						PowerUps[activePowerUpCount] = new CPowerUp(cubeMESH, tiles[z][x].coords);
					}
					else
					{
						//negative powerup
						PowerUps[activePowerUpCount] = new CPowerUp2(cubeMESH, tiles[z][x].coords);
					}
					activePowerUpCount++;
				}
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

/////////////////////////////
// Program setup/shutdown

// One off setup for the entire program. Returns true on success, false on failure
bool ProgramSetup()
{
	// Create a 3D engine (Irrlicht in this case) and open a window for it
	myEngine = New3DEngine(kTLX);
	if (!myEngine)
	{
		return false;
	}
	myEngine->StartWindowed(1280, 720);
	hWnd = (HWND)myEngine->GetWindow(); // Window handle

										// Add folders for meshes and other media (for different locations)	
	myEngine->AddMediaFolder(".\\jpg Files");
	myEngine->AddMediaFolder(".\\png Files");
	myEngine->AddMediaFolder(".\\tga Files");
	myEngine->AddMediaFolder(".\\X Files");

	// Load a loading screen font - will keep this in memory all the time (i.e. don't remove it)
	loadingFont = myEngine->LoadFont("Font2.bmp");
	if (!loadingFont)
	{
		myEngine->Delete();
		return false;
	}

	return true;
}

// Final shutdown for the entire program
void ProgramShutdown()
{
	myEngine->Delete();
}

// Set up the front-end (load meshes & fonts and create models, cameras, lights etc)
// Returns true on success, false on failure
bool FrontEndSetup()
{
	frontEndFont = myEngine->LoadFont("Font1.bmp");
	backgroundMesh = myEngine->LoadMesh("Stars.x");

	// Load resources, returning on failure
	if (!frontEndFont || !backgroundMesh) // change to object
	{
		// Should really release those that were successfully loaded
		return false;
	}

	backgroundModel = backgroundMesh->CreateModel(0.0f, 0.0f, 0.0f);

	// Initialise timer (used for variable timing in front-end and game loops)
	myEngine->Timer();

	cameraMenu = myEngine->CreateCamera(kManual, 0.0f, 70.0f, 0.0f);
	cameraMenu->RotateX(-55.0f);

	LoadMiniSound();

	LoadSoundFile(".\\AudioFiles\\VEH2 Closed Hihats - 005.wav");

	PlaySoundTrackMenu();

	return true;
}

void FrontEndUpdate(float updateTime)
{
	// Text (with shadows)
	//i.e frontEndFont->Draw("Generic Space Game II", 640, 120, kWhite, kCentre);


	frontEndFont->Draw("Play", 200, 118, kGrey, kCentre);
	frontEndFont->Draw("Play", 200, 122, kGrey, kCentre);
	frontEndFont->Draw("Play", 202, 118, kGrey, kCentre);
	frontEndFont->Draw("Play", 202, 122, kGrey, kCentre);
	frontEndFont->Draw("Play", 200, 120, kWhite, kCentre);

	frontEndFont->Draw("Quit", 200, 218, kGrey, kCentre);
	frontEndFont->Draw("Quit", 200, 222, kGrey, kCentre);
	frontEndFont->Draw("Quit", 204, 218, kGrey, kCentre);
	frontEndFont->Draw("Quit", 204, 222, kGrey, kCentre);
	frontEndFont->Draw("Quit", 202, 220, kWhite, kCentre);

	if (myEngine->KeyHit(Key_Up))
	{
		MoveSelectionUp();
	}

	if (myEngine->KeyHit(Key_Down))
	{
		MoveSelectionDown();
	}

	// High lights selected option in menu
	if (GetCurrentSelection() == 0)
	{
		frontEndFont->Draw("Play", 200, 120, kRed, kCentre);
	}
	else
	{
		frontEndFont->Draw("Quit", 202, 220, kRed, kCentre);
	}

#ifdef _MINI_GAME
	if (myEngine->KeyHit(Key_Space))
		PlayMiniSound();

	if (myEngine->KeyHit(Key_Plus))
		IncrementPitch();

	if (myEngine->KeyHit(Key_Minus))
		DecrementPitch();
#endif
}

// Shutdown the front-end, remove everything created in the setup function
void FrontEndShutdown()
{
	StopSoundTrackMenu();
	myEngine->RemoveFont(frontEndFont);
	myEngine->RemoveCamera(cameraMenu);
	myEngine->RemoveMesh(backgroundMesh);
}

bool GameSetup()
{
	// Initialise timer (used for variable timing in front-end and game loops)
	myEngine->Timer();

	myCamera = myEngine->CreateCamera(kManual);
	myCamera->SetPosition(10.0f, 25.0f, 4.0f);
	myCamera->RotateX(90);

	myFont = myEngine->LoadFont("font1.bmp");
	tileMESH = myEngine->LoadMesh("Square.x");
	cubeMESH = myEngine->LoadMesh("state.x");
	backgroundMesh = myEngine->LoadMesh("Stars.x");
	backgroundModel = backgroundMesh->CreateModel(0.0f, 0.0f, 0.0f);

	cHandler = new CCollisionHandler(); // delete
	Player = new CPacDude(cubeMESH);	// delete
	AI = new CGhostDude(cubeMESH, 0);	// delete

	myCamera->AttachToParent(Player->mModel);

	InitialiseTiles_XandZ(tiles, tileMESH, cubeMESH);

	CoordinateFile.open("eMapV2.0.txt");

	ReadGrid(CoordinateFile, tiles);

	CoordinateFile.close();

	InitialiseTiles_TerrainAndTexture(tiles, Points, activePointCount, PowerUps, activePowerUpCount, cubeMESH);

	return true;
}

// Update the game, move models & cameras, draw text etc. Pass a float to specify the
// time passed since the last update (frame) - allows us to use the variable timing method
void GameUpdate(float updateTime)
{
	//save the player's last position
	Player->PreviousPos.x = round(Player->mModel->GetX());
	Player->PreviousPos.z = round(Player->mModel->GetZ());

	string output;
	myFont->Draw("Speed: ", 1010, 210, kWhite);
	output = to_string(Player->mSpeed);
	myFont->Draw(output, 1080, 210, kWhite);

	myFont->Draw("Points: ", 1010, 225, kWhite);
	output = to_string(Player->mPoints);
	myFont->Draw(output, 1080, 225, kWhite);

	/**** Update your scene each frame here ****/
	//if any key is hit
	if (myEngine->AnyKeyHit())
	{
		//handle the players movement
		ListenforPlayerInput(myEngine, Player);
	}
	Player->MoveDude(tiles); //move the player in their direction
	AnimatePowerUps(PowerUps, activePowerUpCount);

	//-------------------both of the following loops are inneficient because we are checking everything every frame

	//loop the number of active points, and run player to point collision //------------------------by making a class that contains a vector of points could help 


	// if ai, point, power up within player radius - do collision c

	if (cHandler->S2SPlayerAI(Player, AI));

	for (int i = 0; i < activePointCount; ++i)
	{
		if (cHandler->S2SPlayerPoints(Player, Points[i]) && Points[i]->mEaten == false)
		// collision code handle in function
		{
			Player->mPoints++;
			Points[i]->mEaten = true;
			PlaySoundFile();
		}
	}

	for (int i = 0; i < activePowerUpCount; ++i)
	{
		if (!PowerUps[i]->mEaten && cHandler->S2SPlayerPowerUp(Player, PowerUps[i]))
		// collision code handle in function
		{
			PowerUps[i]->PowerUpEffect(Player);
			PowerUp_ACTIVE = true;
		}
	}

	// endif

	//timer to deactivate powerup
	if (PowerUp_ACTIVE)
	{
		float timer = myEngine->Timer();

		// old timing didn't work - replaced with timer
		//float fps = 1 / timer;
		//frameCount++;

		if (counter > 0.5f)
		{
			PowerUp_ACTIVE = false;
			counter = 0.0f;
			Player->mVulnverable = true;
			Player->mModel->SetSkin("yellow.png");
			Player->mSpeedMultiplier = 1;
			Player->SetSpeed(Player->mSpeedMultiplier);
		}
		counter += timer;
	}

}

// Shutdown the game, remove everything created in the setup function
void GameShutdown()
{
	// resetting count data
	activePointCount = 0;
	activePowerUpCount = 0;

	// deleting meshs, etc
	myEngine->RemoveFont(myFont);
	myEngine->RemoveCamera(myCamera);
	myEngine->RemoveMesh(tileMESH);
	myEngine->RemoveMesh(cubeMESH);

	// deleting all stack allocated objects
	for (int i = 0; i < activePowerUpCount; ++i)
		delete PowerUps[i];

	for (int i = 0; i < activePointCount; ++i)
		delete Points[i];

	delete Player;
	delete AI;

	StopSoundTrackInGame();
}

void AnimatePowerUps(CPowerUpBase* PowerUps[gNumPowerUps], int activePowerUpCount)
{
	for (int i = 0; i < activePowerUpCount; i++)
	{
		PowerUps[i]->mModel->RotateX(0.5f);
		PowerUps[i]->mModel->RotateY(0.5f);
		PowerUps[i]->mModel->RotateZ(0.5f);
	}
}

int random()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}