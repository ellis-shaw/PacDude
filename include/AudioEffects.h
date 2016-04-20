#ifndef _AUDIO_EFFECTS
#define _AUDIO_EFFECTS

#define _MINI_GAME

#include <string>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <fstream>
#include "SFML/Audio.hpp"

//--------------------------------------------------------------------------------------
//
//	AudioEffects.h
//
//	Handles audio effects/ music
//  
//	Ideally, when using this object, you will create an instance for each sound.
//  My thinking it should make managing each sound source easier
//
//--------------------------------------------------------------------------------------

class CAudio
{
/////////////////////////////
// Public member functions
public:
	// Constructor - used to load up a single sound file
	// will check if the file exists
	CAudio(const std::string &soundFile);

	// Destructor - empty
	~CAudio();

	// play sound file
	void Play();

	// stop sound file
	void Stop();

	// pause depending if playing
	void PauseUnPauseFile();

/////////////////////////////
// Private data members
private:
	bool paused;

	// SFML variables
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
	sf::Vector3f soundPos;
	sf::Vector3f soundVelocity;
	sf::Vector3f listenerPos;
	sf::Vector3f listenerForward;
	sf::Vector3f listenerUp;

	// Check if file is real
	bool FileExists(const std::string &soundFile);
};

// silly audio game thing. use space bar and the + and -

#ifdef _MINI_GAME

void LoadMiniSound();
void PlayMiniSound();
void IncrementPitch();
void DecrementPitch();
float ChangeSemitone(float frequency, float variation);
#endif

#endif