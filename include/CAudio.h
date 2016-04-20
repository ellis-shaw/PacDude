#ifndef _AUDIO
#define _AUDIO

#include <string>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <fstream>
#include "SFML/Audio.hpp"

//--------------------------------------------------------------------------------------
//
//	BAudio.h
//
//	Handles audio effects/ music
//  
//	Ideally, when using this object, you will create an instance for each sound.
//  My thinking it should make managing each sound source easier
//
//--------------------------------------------------------------------------------------

class BAudio
{
/////////////////////////////
// Public member functions
public:
	// Constructor - used to load up a single sound file
	// will check if the file exists
	BAudio();

	// Destructor - empty
	virtual ~BAudio() {};

	// play sound file
	virtual void Play() = 0;

	// stop sound file
	virtual void Stop() = 0;

	// pause depending if playing
	virtual void PauseUnPauseFile() = 0;

	// increase volume
	virtual void IncreaseVolume(const int &amount) = 0;

	// decrease volume
	virtual void DecreaseVolume(const int &amount) = 0;

	// increase pitch
	virtual void IncreasePitch() = 0;

	// decrease pitch
	virtual void DecreasePitch() = 0;

	// increase pitch
	virtual void IncreasePitch(const int &amount) = 0;

	// decrease pitch
	virtual void DecreasePitch(const int &amount) = 0;

/////////////////////////////
// Private data members
protected:
	// Check if file is real
	bool FileExists(const std::string &soundFile);

	float ChangeSemitone(float frequency, float variation);
};

#endif