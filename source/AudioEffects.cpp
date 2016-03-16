#include "AudioEffects.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include "SFML/Audio.hpp"

#ifdef  _MINI_GAME

sf::SoundBuffer bufferMini;
sf::Sound soundMini;
float pitch = 1.0f;

#endif

//****************
// Globals

// A "buffer" holds sound data, but the creation of a buffer on its own doesn't play a sound. It is the
// equivalent of a mesh in the TL-Engine
sf::SoundBuffer buffer[2];


// A "sound" is an actual sound in the world. A sound must be associated with a buffer to indicate
// which sound data to play. Sources are equivalent to models in the TL-Engine
sf::Sound sound;
sf::Music music[2];

// Each sound source has several properties, see the code for examples. Here we store position and 
// velocity of the sound source above, using a SFML class Vector3f to hold the xyz values
// The velocity is to move the sound around and also for the Doppler effect. In fact SFML does not
// support Doppler, so the velocity is just for our own purposes. Look at the "OpenAL Soft" library
// if you want to do Doppler in your own projects
sf::Vector3f soundPos(0.0, 0.0, 0.0);
sf::Vector3f soundVelocity(0.0, 0.0, 0.0);


// There is always assumed to be a listener in the wold although we don't need a specific listener variable.
// Listeners also have properties (examples in code). Here we store the listener's position
sf::Vector3f listenerPos(0.0, 0.0, 0.0);

// The listener may be at an angle (which may affect the perception of sound). Here we store the 
// orientation of the listener by specifying their facing direction and upward direction.
// These xyz vectors can be extracted from a world or view matrix
// NOTE: SFML uses a right-handed system for 3D coordinates. To convert from the left-handed system
// we normally use, we must negate all Z values (facing direction has -ve Z below). Without this
// change the sounds from the left and right speakers will be the wrong way round
sf::Vector3f listenerForward(0.0, 0.0, -1.0);
sf::Vector3f listenerUp(0.0, 1.0, 0.0);

bool paused[2] = { false };

Audio::Audio()
{
	//"VEH2 Closed Hihats - 005.wav"
}

void LoadSoundFile(const std::string &fileName)
{
	float Timer();

	if (!music[0].openFromFile(".\\AudioFiles\\gameBackground.wav"))
	{
		std::cout << "Error loading sound file" << std::endl;
		while (!_kbhit());
		return;
	}

	if (!music[1].openFromFile(".\\AudioFiles\\gameBackgroundInGame.wav"))
	{
		std::cout << "Error loading sound file" << std::endl;
		while (!_kbhit());
		return;
	}

	if (!buffer[0].loadFromFile(fileName))
	{
		std::cout << "Error loading sound file" << std::endl;
		while (!_kbhit());
		return;
	}

	 //Set the properties of the source. Details of all available properties are in the SFML documentation of the Sound class
	for (int i = 0; i < 2; i++)
	{
		music[i].setVolume(40.0f); // 0 to 100	
		music[i].setLoop(true);
		music[i].setPosition(soundPos);
	}

	// Indicate that our sound source will use the buffer we just loaded
	sound.setBuffer(buffer[0]);

	// Set the properties of the source. Details of all available properties are in the SFML documentation of the Sound class
	sound.setVolume(40.0f); // 0 to 100
	sound.setPitch(4.0f);
	sound.setLoop(false);
	sound.setPosition(soundPos);

	// Note how this is doen with static member functions - there is no listener variable
	sf::Listener::setGlobalVolume(100.0f); // 0 to 100
	sf::Listener::setPosition(listenerPos);
	sf::Listener::setDirection(listenerForward);
	sf::Listener::setUpVector(listenerUp);
}

void PlaySoundFile()
{
	sound.play();
}

void PlaySoundTrackMenu()
{
	music[0].play();
}

void PlaySoundTrackInGame()
{
	music[1].play();
}

void StopSoundTrackMenu()
{
	music[0].stop();
}

void StopSoundTrackInGame()
{
	music[1].stop();
}

void PauseUnPauseSoundTrackMenu()
{
	if (paused[0])
	{
		paused[0] = false;
		music[0].play();
	}
	else
	{
		paused[0] = true;
		music[0].pause();
	}	
}

void PauseUnPauseSoundTrackInGame()
{
	if (paused[1])
	{
		paused[1] = false;
		music[1].play();
	}
	else
	{
		paused[1] = true;
		music[1].pause();
	}
}

float Timer()
{
	static clock_t currTime = clock();
	clock_t prevTime = currTime;
	currTime = clock();
	return float(currTime - prevTime) / CLOCKS_PER_SEC;
}

#ifdef _MINI_GAME
void LoadMiniSound()
{
	if (!bufferMini.loadFromFile(".\\AudioFiles\\synthOneShot.wav"))
	{
		std::cout << "Error loading sound file" << std::endl;
		while (!_kbhit());
		return;
	}

	soundMini.setBuffer(bufferMini);

	// Set the properties of the source. Details of all available properties are in the SFML documentation of the Sound class
	soundMini.setVolume(40.0f); // 0 to 100
	soundMini.setPitch(pitch);
	soundMini.setLoop(false);
	soundMini.setPosition(soundPos);
}

void PlayMiniSound()
{
	soundMini.play();
}

void IncrementPitch()
{
	if (pitch < 4.0f)
	{
		pitch = ChangeSemitone(pitch, 1.0f);
		soundMini.setPitch(pitch);
	}	
}

void DecrementPitch()
{
	if (pitch > 0.117f)
	{
		pitch = ChangeSemitone(pitch, -1.0f);
		soundMini.setPitch(pitch);
	}	
}

float ChangeSemitone(float frequency, float variation)
{
	static float semitone_ratio = pow(2.0f, 1.0f / 12.0f);
	return frequency * pow(semitone_ratio, variation);
}
#endif